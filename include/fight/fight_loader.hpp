#pragma once
#ifndef __FIGHT_LOADER_HPP
#define __FIGHT_LOADER_HPP

#include <fight/fight.hpp>

namespace fight_loader {
    /**
     * Loads fight into memory.
     * 
     * @param fightID - Fight ID
     * 
     * @return 0 if success
     */
    int load(unsigned int fightID);

    /**
     * Swaps the fight data and information
     * with the specified Fight object
     * 
     * @param fight - specified Fight object
     */
    void swapData(Fight& fight);

} // namespace fight_loader


#endif