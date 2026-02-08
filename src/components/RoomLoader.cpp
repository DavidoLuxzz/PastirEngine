#include <components/RoomLoader.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <components/Room.hpp>
#include <colors.h>

namespace room_loader {
    Room room;
} // namespace room_loader


void __lvl_loader_nonobject(const std::string& line) {
    if (line.starts_with("box ")) {
        std::istringstream _l(line);
        int index=0;
        std::string token;
        std::getline(_l, token, ' '); // skip first
        
        std::getline(_l, token, ' ');
        room_loader::room.bounds.size.x = std::stoi(token);
        std::getline(_l, token, ' ');
        room_loader::room.bounds.size.y = std::stoi(token);
    } else if (line.starts_with("area ")) {
        int index = 3;
        while (line[++index]==' ');
        room_loader::room.areaName = line.substr(index);
        index = room_loader::room.areaName.size();
        while (room_loader::room.areaName[--index]==' ');
        room_loader::room.areaName = room_loader::room.areaName.substr(0,index+1);
    }
}

int __lvl_loader_load(const std::string& filepath) {
    std::ifstream file(filepath);

    room_loader::room.objects.clear();
    
    std::string line;
    while (std::getline(file, line)) {
        if (!std::isdigit(line[0])){
            std::cout << line << std::endl;
            __lvl_loader_nonobject(line);
            continue;
        }
        std::istringstream _l(line);
        Drawable::DrawableData data = DRAWABLE_DEFAULT_DATA; int index=0;
        std::string token;
        while (std::getline(_l, token, ' ')) {
            data[index++] = std::stoi(token);
            if (index>=Drawable::COMPONENT_COUNT) break;
        }
        room_loader::room.objects.push_back(data);
    }

    file.close();

    return 0;
}



int room_loader::load(unsigned int roomID) {
    std::string filepath(std::getenv("HOME"));
    filepath += ("/eclipse-workspace/Pastir-editor/");
    filepath += std::to_string(roomID);
    filepath += ".txt";
    if (!std::filesystem::exists(filepath)) {
        fprintf(stderr, "<%sLVLLOADER%s> Room %u doesn't exists. path=%s\n",TERMINAL_COLOR_RED_BOLD,TERMINAL_COLOR_RESET, roomID, filepath.c_str());
        return -1;
    }
    // printf("<LVLLOADER> Loading room %u path=%s\n", roomID, filepath.c_str());
    return __lvl_loader_load(filepath);
}



void room_loader::swapData(Room& _room) {
    _room.objects.swap(room.objects);
    _room.areaName = room.areaName;
    _room.bounds = room.bounds;
}