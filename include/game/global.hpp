#pragma once
#ifndef __GLOBAL_VARS_HPP
#define __GLOBAL_VARS_HPP

class Room;


namespace global {
    enum ScreenType {
        GAME,
        MAIN_MENU,
        FIGHT,

        NUM_SCREEN_TYPES
    };

    struct vars {
        bool running;
        ScreenType currentScreen;
        bool f3;

        #define NUM_ROOMS 4
        Room* rooms;
    };

    vars& get();
} // namespace global


#endif