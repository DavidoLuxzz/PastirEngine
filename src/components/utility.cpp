#include <components/utility.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <colors.h>
#include <asset_manager.hpp>

std::vector<Rectu> util::loadTiles(const char* relativefilepath) {
    std::vector<Rectu> tiles;
    std::string filepath = assman::getasset(relativefilepath);
    if (!std::filesystem::exists(filepath)) {
        fprintf(stderr, "{%sUTILITY%s} File doesn't exists %s\n",TERMINAL_COLOR_RED_BOLD,TERMINAL_COLOR_RESET, filepath.c_str());
        return tiles;
    }
    // printf("{UTILITY} Loading tileset data file path=%s\n", filepath.c_str());

    std::ifstream file(filepath);
    
    std::string line;
    while (std::getline(file, line)) {
        if (!std::isdigit(line[0])){
            std::cout << line << std::endl;
            continue;
        }
        std::istringstream _l(line);
        unsigned int data[4] = {0,0,16,16}; // default
        int index=0;
        std::string token;
        while (std::getline(_l, token, ' ')) {
            data[index++] = std::stoi(token);
            if (index>=4) break;
        }
        Rectu tile = {data[0],data[1],data[2],data[3]};
        tiles.push_back(tile);
    }

    file.close();

    std::cout << "done " << relativefilepath << "\n";

    return tiles;
}