#pragma once
#ifndef __ROOM_LOADER_HPP
#define __ROOM_LOADER_HPP

#include <level/Room.hpp>

namespace room_loader {
    /**
     * Loads room into memory.
     * Room is accessible via room_loader::getRoom();
     * 
     * @param roomID Room ID
     * 
     * @return 0 if success
     */
    int load(unsigned int roomID);

    /**
     * Swaps the objects vector between the data stored
     * in room_loader's memory and specified room
     * 
     * @param room - specified room object
     */
    void swapData(Room& room);
    

} // namespace room_loader

#endif