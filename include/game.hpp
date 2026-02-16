#pragma once
#ifndef __GAME_HPP
#define __GAME_HPP


#define WINDOW_WIDTH  200 // in game pixels
#define WINDOW_HEIGHT 160 // in game pixels
/// @brief Used in rooms
#define DEFAULT_PIXEL_SCALE 4.0f

#define TRIGGERS_FILE "triggers.txt"
#define ENTITIES_FILE "ent.txt"

namespace game {

    /**
     * Initializes game components and variables.
     * Calls loadAssets().
     * @returns error code
     */
    int init();
    /// @returns error code 
    int loadAssets();
    /// @returns error code
    int loadRooms();
    /// @brief clean before exit
    void clean();
    /**
     * Main game run function
     * @returns exit code
     */
    int run();
    void draw();


    /// @brief used localy
    /// @param ms time passed since last update (should equal to 1/FPS)
    void update(float ms);

} // namespace game

#endif