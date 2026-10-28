#pragma once
#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <sprite/sprite.hpp>
#include <sprite/texture.hpp>
#include <animation.hpp>
#include <level/Room.hpp>
#include <inventory.hpp>
#include <list>

class Player : public Sprite {
protected:
    bool invincible = false;
    // int currentDirection = DIR_UP;
    Animation animation;
    bool usingNikes = false;
    
    float speedmul=1.0f;
    float2 spriteScale={1.f,1.f};

    bool crouching = false;
    Animation crouchAnim;

    bool superDashing = false;
    float angle = 0.f;
    float velo = 0.f;

    /**
     * Player world position.
     */
    float2 worldPos;

    // cool effect 25.10.2026: Parlamentarni izbori: >>Studenti su pobedili<<
    bool trailEnabled = false;
    Animation trailAnim;
    static constexpr int TRAIL_INSTANCE_COUNT = 10;
    struct trail {
        float2 pos;
        bank::TextureInfo texInfo;
    };
    std::list<trail> trailPositions;

public:
    /// @brief Speed [pixel(s)/60FPS]
    static constexpr float SPEED = 0.240f;

    Inventory inventory = Inventory(this);

    inline void setInvincible(bool t) {invincible = t;}
    inline bool isInvincible() const {return invincible;}

    // constructors
    Player();
    enum directions {
        DIR_UP,
        DIR_DOWN,
        DIR_LEFT,
        DIR_RIGHT
    };
    #define NUM_ANIMATION_FRAMES 4 // stoji ovde eto jbg posto ce dobiti value 4, pa da sacuvam prostora
    
    /**
     * All player updates go here.
     */
    void update(double ms);

    void setSpeedMul(float mul);
    float getSpeed() const;

    // void setRoom(Room*);

    Rectf getHitbox() const;

    /**
     * Move procedure:
     *  -  player.move(dx,dy)
     *  -  room.position(player.getWorldPosition())
     *  -  player.positionRoom(room.getTranslate())
     */


    /// @brief fixes the players screen position
    /// @param pos the top left corner of room
    void positionRoom(float2 roomPos);
    float2 getScreenPosition() const;
    Rectf getScreenHitbox() const;
    float getScreenFeetY() const;

    void setWorldPosition(float2 pos);
    float2 getWorldPosition() const;
    float getWorldFeetY() const; 
    float2 getWorldCenter() const;

    void setAngle(float);
    float getAngle() const;

    // based on collision checks in current room
    float2 getFixedDisplacement(float, float, int roomID=-1);

    /// @brief By default it takes Game's roomID value
    /// @param roomID specific roomID to compute collision in
    /// @param ms delta time in milliseconds. Used to calculate
    void move(float dx, float dy, float ms, int roomID=-1);
    /**
     * Changes players texture tile according to the current direction.
     * Also contains animation.update().
     */
    void orientate(float dx, float dy);
    void setTileByDirection(directions);

    void setSpriteScale(float2);
    float2 getSpriteScale() const;

    void useNikes(bool);
    bool isUsingNikes() const;

    void enableTrail(bool);
    bool isTrailEnabled() const;

    void setCrouching(bool);
    bool isCrouching() const;

    void activateSuperDash(bool);
    bool isSuperDashing() const;
    
    void drawInstance(float2 screenPos, bank::TextureInfo texInfo, float2 scale, ALLEGRO_COLOR tint, float ang) const;
    void draw() const;
};

#endif