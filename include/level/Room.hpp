#pragma once
#ifndef __ROOM_HPP
#define __ROOM_HPP

#include <vector>
#include <sprite/Drawable.hpp>
#include <sprite/StaticEntity.hpp>

class Room {
    // layering
    std::vector<int> entityTopIDs;
    std::vector<int> drawableTopIDs;
    // --------
    float2 translate = {0,0};
public:
    std::vector<Drawable::DrawableData> objects;
    std::vector<StaticEntity::EntityData> entities;
    Rectu bounds;
    std::string areaName;

    /// @brief Draw pre player.draw()
    void drawBackLayer();
    /// @brief Draw posle player.draw()
    void drawTopLayer();

    void position(float2 playerPos);

    void setTranslate(float tx, float ty);
    float2 getTranslate() const;
    void move(float dx, float dy, void* player=NULL);

    uint64_t getMemoryUsage() const;
};

std::string __memsizeToString(uint64_t a);


#endif