#pragma once
#ifndef __ROOM_HPP
#define __ROOM_HPP

#include <vector>
#include <sprite/Drawable.hpp>

class Room {
    float2 translate = {0,0};
public:
    std::vector<Drawable::DrawableData> objects;
    Rectu bounds;
    std::string areaName;

    void draw();

    void setTranslate(float tx, float ty);
    float2 getTranslate() const;
    void move(float dx, float dy, void* player=NULL);

    uint64_t getMemoryUsage() const;
};

std::string __memsizeToString(uint64_t a);


#endif