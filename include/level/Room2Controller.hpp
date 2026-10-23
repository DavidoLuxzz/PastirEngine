#pragma once
#ifndef __ROOM2_CONTROLLER_HPP
#define __ROOM2_CONTROLLER_HPP
#include <level/RoomController.hpp>
#include <allegro5/allegro_primitives.h>

class Room2Controller : public RoomController {
    int timer = 0;
    unsigned int expand = 3200;
    ALLEGRO_VERTEX gradient[4];
    const float gradientXs[4] = {0.f,300.f,300.f,0.f};
public:

    Room2Controller();

    void init() override;
    void update(double) override;
    void drawTopLayer() override;
    void drawBackLayer() override;

    /** Expand room */
    void func0(void* args, int argc) override;
    void func1(void* args, int argc) override;
    void func2(void* args, int argc) override;
    void func3(void* args, int argc) override;

    ~Room2Controller() override;
};



#endif