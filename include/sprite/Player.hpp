#pragma once
#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <sprite/sprite.hpp>
#include <sprite/texture.hpp>
#include <animation.hpp>
#include <components/Room.hpp>

class Player : public Sprite {
protected:
    // int currentDirection = DIR_UP;
    Animation animation;
    bool usingNikes = false;
    
    float speedmul=1.0f;

    /**
     * Player world position.
     */
    float2 worldPos;

    /* pointer to a [solid drawable pointers] list */ // DrawableData** solids;
    Room* room=NULL;
public:
    /// @brief Speed [pixel(s)/60FPS]
    static constexpr float SPEED = 60.0f;

    // constructors
    Player();
    enum directions {
        DIR_UP,
        DIR_DOWN,
        DIR_LEFT,
        DIR_RIGHT,
        NUM_ANIMATION_FRAMES // stoji ovde eto jbg posto ce dobiti value 4, pa da sacuvam prostora
    };

    void setSpeedMul(float mul);
    float getSpeed() const;

    void setRoom(Room*);

    Rectf getHitbox() const;

    /**
     * Move procedure:
     *  -  player.move(dx,dy)
     *  -  room.position(player.getWorldPosition())
     *  -  player.setScreenPosition(room)
     */


    /// @brief fixes the players screen position
    /// @param pos the top left corner of room
    void positionRoom(float2 roomPos);
    float2 getScreenPosition() const;

    void setWorldPosition(float2 pos);
    float2 getWorldPosition() const;

    // based on collision checks in current room
    float2 getFixedDisplacement(float, float);

    void move(float dx, float dy);
    /**
     * Changes players texture tile according to the current direction.
     */
    void orientate(float dx, float dy);
    void setTileByDirection(directions);

    void useNikes(bool);

    void draw();
};

#endif