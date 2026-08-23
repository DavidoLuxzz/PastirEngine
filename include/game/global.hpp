#pragma once
#ifndef __GLOBAL_VARS_HPP
#define __GLOBAL_VARS_HPP

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
    };

    vars& get();
} // namespace global


#endif