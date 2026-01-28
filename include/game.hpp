#pragma once
#ifndef __GAME_HPP
#define __GAME_HPP

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

} // namespace game

#endif