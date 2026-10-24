#pragma once
#ifndef __ROOM_CONTROLLER_HPP
#define __ROOM_CONTROLLER_HPP


class RoomController {
public:

    virtual void init() = 0;
    /// Called everytime entering room
    virtual void enter() = 0;
    virtual void update(double ms) = 0;
    virtual void drawTopLayer() = 0;
    virtual void drawBackLayer() = 0;
    /// Called everytime exiting room
    virtual void exit() = 0;

    virtual void func0(void* args, int argc) = 0;
    virtual void func1(void* args, int argc) = 0;
    virtual void func2(void* args, int argc) = 0;
    virtual void func3(void* args, int argc) = 0;

    virtual ~RoomController() = default;

};

#endif