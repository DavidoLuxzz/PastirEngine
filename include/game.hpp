#pragma once
#ifndef __GAME_HPP
#define __GAME_HPP


#define WINDOW_WIDTH  200 // in game pixels
#define WINDOW_HEIGHT 160 // in game pixels
/// @brief Used in rooms
#define DEFAULT_PIXEL_SCALE 4.0f

namespace game {
    
    /**
     * Initializes game components and variables.
     * @returns error code
     */
    int init();
    /// @brief clean before exit
    void clean();
    /**
     * Main game run function
     * @returns exit code
     */
    int run();


    // used localy
    void update();

} // namespace game

#endif