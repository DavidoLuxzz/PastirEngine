#pragma once
#ifndef __FIGHT_LOADER_HPP
#define __FIGHT_LOADER_HPP

#include <fight/fight.hpp>

namespace fight_loader {
    /**
     * Loads room into memory.
     * Room is accessible via room_loader::getRoom();
     * 
     * @param roomID Room ID
     * 
     * @return 0 if success
     */
    int load(unsigned int fightID);

    /**
     * Swaps the objects vector between the data stored
     * in room_loader's memory and specified room
     * 
     * @param room - specified room object
     */
    void swapData(Fight& room);

} // namespace fight_loader


#endif