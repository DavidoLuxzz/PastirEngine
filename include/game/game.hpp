#pragma once
#ifndef __GAME_HPP
#define __GAME_HPP

#include <components/display.hpp>
#include <level/Room.hpp>
#include <sprite/Player.hpp>
#include <sprite/StaticEntity.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define WINDOW_WIDTH  1152 // in game pixels
#define WINDOW_HEIGHT 768 // in game pixels
/// @brief Used in rooms
#define DEFAULT_PIXEL_SCALE 1.0f

#define TRIGGERS_FILE "triggers.txt"
#define ENTITIES_FILE "ent.txt"

/**
 * U ovoj klasi su sve komponente vezane *samo* za gameplay.
 * Znaci u ovoj klasi *nema* komponenata za npr. main menu.
 */
class Game {
public:
    
    #define NUM_ROOMS 4
    Room rooms[NUM_ROOMS];
    int roomID = 0, requestRoomID = 0; // requestRoomID - kada change room
    float2 requestPlayerCoords; // za sad samo kada change room
    Player player;
    ALLEGRO_FONT* font;
    bool ___zPressedThisFrame = false;
    StaticEntity ent;
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

    void draw();

    void game_move(float dx, float dy);

    void debugText();

    bool isZPressed();
    bool isZPressedThisFrame(); // is z pressed that frame

    void immidiatelyChangeRoom();


    /// @brief used localy
    /// @param ms time passed since last update (should equal to 1/FPS)
    void updateMovement(float ms);
    void update(float ms);
    void handleEvents();


    static inline void drawRectf(const Rectf rect, ALLEGRO_COLOR color, float2 translate={0,0}) {
        float x = rect.min.x + translate.x;
        float y = rect.min.y + translate.y;
        al_draw_rectangle(x,y, x+rect.size.x,y+rect.size.y, color, 4.0f);
    }

    static void makeCurrent(Game*);
    static Game* getGame();

}; // class Game

#endif