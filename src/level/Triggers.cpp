#include <level/Triggers.hpp>
#include <asset_manager.hpp>
#include <fstream>
#include <iostream>
#include <colors.h>
#include <sstream>
#include <game.hpp>
#include <event.hpp>
#include <components/dialogbox.hpp>

Trigger::Trigger(TriggerData& _data) {
    data = _data;
}

float2 Trigger::worldCoordinates(int x, int y) {
    return {x/DEFAULT_PIXEL_SCALE, y/DEFAULT_PIXEL_SCALE};
}

Rectf Trigger::createHitbox(const TriggerData& data, float2 translate) {
    const float2 coords = Trigger::worldCoordinates(data[COMP_X], data[COMP_Y]) + translate;
    const float2 size = Trigger::worldCoordinates(data[COMP_WIDTH], data[COMP_HEIGHT]);
    return {
        coords,
        size
    };
}

bool Trigger::isDisabled(const TriggerData& data) {
    return data[COMP_ACTION]==event::NONE;
}

void changeRoom(const Trigger::TriggerData& data) {
    Game* game = Game::getGame();
    
    game->requestRoomID = data[Trigger::COMP_SPECIAL];
    game->requestPlayerCoords = {(float)data[Trigger::COMP_SPECIAL2]/DEFAULT_PIXEL_SCALE, (float)data[Trigger::COMP_SPECIAL3]/DEFAULT_PIXEL_SCALE};

    Display::getCurrentDisplay()->startFade();
}
#define THIS_ROOM Game::getGame()->rooms[Game::getGame()->roomID]
void Trigger::execute(const TriggerData& data) {
    switch (data[COMP_ACTION]) {
    case event::CHANGE_ROOM: {
        changeRoom(data);
        break;
    }
    case event::DIALOG_INTERRUPT: {
        dialogbox::show();
        break;
    }
    case event::DIALOG_INTERRUPT_THEN_DISAPPEAR: {
        dialogbox::show();
        if (data[COMP_SOURCE]==1) // 1=entity
            THIS_ROOM.entities.erase(THIS_ROOM.entities.begin()+data[COMP_ENTITY_ID]);
        break;
    }
    case event::GIVE_ITEM_THEN_DISAPPEAR: {
        Game::getGame()->player.inventory.add((Item)data[COMP_SPECIAL]);
        if (data[COMP_SOURCE]==1) // 1=entity
            THIS_ROOM.entities.erase(THIS_ROOM.entities.begin()+data[COMP_ENTITY_ID]);
        break;
    }
    case event::TEXTURE_CHANGE: {
        int targetID = data[COMP_SPECIAL];
        int newTexture = data[COMP_SPECIAL2];
        int solid = data[COMP_SPECIAL3];
        THIS_ROOM.objects[targetID][Drawable::COMP_TEXTURE_ID] = newTexture;
        THIS_ROOM.objects[targetID][Drawable::COMP_SOLID] = solid;
        // printf("Changing texture object=%d to %d. Setting solidity to: %s\n", targetID, newTexture, solid?"yes":"no");
        break;
    }
    
    default:
        break;
    }
}








typedef std::vector<Trigger::TriggerData> TrData;

namespace triggers {
    TrData __triggers;
    std::vector<unsigned int> __thisRoomTriggers;
} // namespace triggers

void triggers::prepare(unsigned int room) {
    __thisRoomTriggers.clear();
    for (unsigned int i=0; i<__triggers.size(); i++) {
        if (__triggers[i][Trigger::COMP_ROOM] == room)
            __thisRoomTriggers.push_back(i);
    }
}

const Trigger::TriggerData& triggers::get(unsigned int triggerID) {
    return __triggers[__thisRoomTriggers[triggerID]];
}

unsigned int triggers::getThisRoomTriggerCount() {
    return __thisRoomTriggers.size();
}


void __tr_loader_getAll(const std::string& filepath, TrData& contents) {
    std::ifstream file(filepath);
    
    std::string line;
    while (std::getline(file, line)) {
        if (!std::isdigit(line[0]))
            continue;
        std::istringstream _l(line);
        Trigger::TriggerData data = TRIGGER_DEFAULT_DATA; int index=0;
        std::string token;
        while (std::getline(_l, token, ' ')) {
            data[index++] = std::stoi(token);
            if (index>=Trigger::COMPONENT_COUNT) break;
        }
        contents.push_back(data);
        //printf("Loaded trigger: %d %d 16x16\n", data[Trigger::COMP_X], data[Trigger::COMP_Y]);
        //break;
    }

    file.close();
}

#include <algorithm>
bool __tr_loader_sort_comp(const Trigger::TriggerData& a, const Trigger::TriggerData& b) {
    return a[Trigger::COMP_ROOM]<b[Trigger::COMP_ROOM];
}

void __tr_loader_sortByRoom(TrData& contents) {
    std::sort(contents.begin(), contents.end(), __tr_loader_sort_comp);
}

void __tr_loader_loadRoomTriggerCounts(const TrData& contents, std::vector<unsigned int>& trcounts) {
    trcounts.clear();
    trcounts.resize(contents.back()[Trigger::COMP_ROOM] + 1);
    unsigned int current = contents[0][Trigger::COMP_ROOM];
    unsigned int count = 0;
    unsigned int index = 0;
    for (const Trigger::TriggerData& data : contents) {
        if (data[Trigger::COMP_ROOM]!=current) {
            trcounts[index++] = count;
            current = data[Trigger::COMP_ROOM];
            count = 0;
        } else count++;
    }

    for (unsigned int i : trcounts) {
        std::cout << ">>>>> " << i << std::endl;
    }
}

#include <game.hpp>
int triggers::load() {
    std::string filepath = assman::getasset(TRIGGERS_FILE);
    // fprintf(stderr, "<TRLOADER> Loading triggers. path=%s\n", filepath.c_str());
    if (!std::filesystem::exists(filepath)) {
        fprintf(stderr, "<%sTRLOADER%s> Triggers file doesn't exists path=%s\n",TERMINAL_COLOR_RED_BOLD,TERMINAL_COLOR_RESET, filepath.c_str());
        return -1;
    }

    __tr_loader_getAll(filepath, __triggers);
    // __tr_loader_sortByRoom(__triggers);
    // __tr_loader_loadRoomTriggerCounts(__triggers, __roomTrCounts);

    return 0;
}

void triggers::check_update() {
    Game* game = Game::getGame();
    bool zDown = game->isZPressedThisFrame();
    for (unsigned int i=0; i<triggers::getThisRoomTriggerCount(); i++) {
        const Trigger::TriggerData& data = triggers::get(i);
        if (data[Trigger::COMP_ACTION] == event::NONE) continue;
        if (data[Trigger::COMP_NEEDS_Z] && !zDown) continue;

        Rectf trHitbox = Trigger::createHitbox(data);
        if (game->player.getHitbox().intersects(trHitbox)) {
            // printf("Trigger! action=%d\n", data[Trigger::COMP_ACTION]);
            Trigger::execute(data);
            if (data[Trigger::COMP_ACTION] == event::CHANGE_ROOM)
                break;
            if (data[Trigger::COMP_RMAFINT]) // remove after execution/intersection
                disable(i);
        }
    }
}

void triggers::disable(unsigned int trID) {
    __triggers[__thisRoomTriggers[trID]][Trigger::COMP_ACTION] = event::NONE;
}