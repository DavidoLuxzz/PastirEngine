#include <level/Triggers.hpp>
#include <asset_manager.hpp>
#include <fstream>
#include <iostream>
#include <colors.h>
#include <sstream>


Trigger::Trigger(TriggerData& _data) {
    data = _data;
}



typedef std::vector<Trigger::TriggerData> TrData;

namespace triggers {
    TrData __triggers;
} // namespace triggers





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

#include <game.hpp>
int triggers::load() {
    std::string filepath = assman::getasset(TRIGGERS_FILE);
    fprintf(stderr, "<TRLOADER> Loading triggers. path=%s\n", filepath.c_str());
    if (!std::filesystem::exists(filepath)) {
        fprintf(stderr, "<%sTRLOADER%s> Triggers file doesn't exists path=%s\n",TERMINAL_COLOR_RED_BOLD,TERMINAL_COLOR_RESET, filepath.c_str());
        return -1;
    }

    __tr_loader_getAll(filepath, __triggers);

    return 0;
}


const Trigger::TriggerData& triggers::get(unsigned int room) {
    return __triggers[room];
}