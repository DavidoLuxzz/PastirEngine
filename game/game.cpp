#include <game.hpp>
#include <iostream>
#include <components/display.hpp>
#include <logger.hpp>
#include <bank.hpp>
#include <asset_manager.hpp>
#include <sprite/Drawable.hpp>
#include <input.hpp>
#include <components/RoomLoader.hpp>
#include <components/utility.hpp>
#include <sprite/Player.hpp>

#include <allegro5/allegro_font.h>

Display display;
Room room;
Player player;
ALLEGRO_FONT* font;

#define TEST_DRAW_SAMPLES 1

#pragma region game::run

int game::run(){
    unsigned int frames = 0;
    double lastTime = 0.0;
    while (true) {
        /* handle events: */ {
            ALLEGRO_EVENT evt;
            while (display.getEventQueue().popNext(&evt)) {
                if (evt.type==ALLEGRO_EVENT_DISPLAY_CLOSE) return 0;
                if (evt.type==ALLEGRO_EVENT_KEY_DOWN && evt.keyboard.keycode == ALLEGRO_KEY_ESCAPE) return 0;
            }
        } // end handling events

        frames++;
        if (al_get_time()-lastTime >= 1.0) {
            lastTime = al_get_time();
            display.setTitle(  (std::string("DEMO FPS: ")+std::to_string(frames)+" Sprites: "+std::to_string(TEST_DRAW_SAMPLES*room.objects.size())).c_str()  );
            frames = 0;
        }

        // ## UPDATE ## //
        update();

        /* DRAWING */
        draw();
    }

    return 0;
}

#pragma endregion

#pragma region game::draw

void debugText() {
    const float __px_scale = Display::getPixelScale()/2.0f;
    Display::useCustomScale(__px_scale, __px_scale);

    Rectf drw = Drawable::createHitbox(room.objects[0]);
    Rectf playerHitbox = player.getHitbox();

    al_draw_textf(font, al_map_rgb(255,255,255), 0, 0, 0, "Player pos: %.1f %.1f [%.0fx%.0f]", playerHitbox.min.x,playerHitbox.min.y, playerHitbox.size.x,playerHitbox.size.y);
    al_draw_textf(font, al_map_rgb(255,255,255), 0, 10, 0, "Obj pos: %.1f %.1f [%.0fx%.0f]", drw.min.x,drw.min.y, drw.size.x,drw.size.y);
    bool t = playerHitbox.intersects(drw);
    al_draw_textf(font, al_map_rgb(255,255,255), 0, 20, 0, "Intersects: %s", t?"true":"false");

    Display::useScale();
}

void game::draw() {
    Display::clear(100,0,0);

    for (int i=0; i<TEST_DRAW_SAMPLES; i++)
        room.draw();
    player.draw();

    debugText();
    
    Display::swapBuffers();
}

#pragma endregion

#pragma region game::update

void __game_move(float dx, float dy) {
    player.move(dx,dy);
    // player.setTranslate(player.getTranslate().x+dx, player.getTranslate().y+dy);
    //player.setPosition(player.getWorldPosition().x, player.getWorldPosition().y);
    room.position(player.getWorldPosition());
    player.positionRoom(room.getTranslate());

    player.orientate(dx,dy);
}

void game::update() {
    keyboard::fetchKeyboardState();
    float dx = (keyboard::keyDown(ALLEGRO_KEY_RIGHT)-keyboard::keyDown(ALLEGRO_KEY_LEFT)) * player.getSpeed();
    float dy = (keyboard::keyDown(ALLEGRO_KEY_DOWN)-keyboard::keyDown(ALLEGRO_KEY_UP)) * player.getSpeed();
    // drawable.setPosition(pos.x+dx, pos.y+dy);
    __game_move(dx,dy);
}

#pragma endregion


#pragma region game::init

#define LUKA_ASSERT0(x) if (x) return -1;
#define LUKA_ASSERT1(x) if (x<0) return -1;


int game::loadAssets() {
    /* Bank loading */{
        bank::tileset::init(bank::tileset::NUM_KNOWN_BANKS);
        // TilesetBank tbank;
        bank::tileset::getBank(bank::tileset::MAP_DRAWABLES).loadTexture("drawables.png");
        bank::tileset::getBank(bank::tileset::MAP_DRAWABLES).loadTileRects("drawable_rects.txt");
        // bank::tileset::makeGlobal(tbank, 0);
        bank::tileset::getBank(bank::tileset::PLAYER).loadTexture("player.png");
        bank::tileset::getBank(bank::tileset::PLAYER).loadTileRects("player_rects.txt");
    }
    return 0;
}

int game::init(){
    font = al_create_builtin_font();


    int __assets_path_err = 0;
    std::string __assets_path;
    __assets_path = assman::getallegropathstr(ALLEGRO_RESOURCES_PATH, &__assets_path_err);
    //__assets_path = std::getenv("HOME");
    __assets_path += "assets";
    printf("> Setting resources path to %s [errors=%d, %d]\n", __assets_path.c_str(), __assets_path_err, assman::setcwd(__assets_path));

    Display::setPixelScale(8.0f);

    LUKA_ASSERT0(display.create(WINDOW_WIDTH, WINDOW_HEIGHT, "DEMO", true));
    display.getEventQueue().registerKeyboardEventSource();
    
    LUKA_ASSERT0(loadAssets());

    room_loader::load(0); // .txt
    room_loader::swapData(room);

    player.setTexturesBankType(bank::TILESET);
    player.setTexturesBankID(bank::tileset::PLAYER);
    player.setScale(0.5f);
    player.setCenter(WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f);
    player.setWorldPosition(player.getPosition());
    player.useNikes(true);
    player.setRoom(&room);

    printf("Room %s [%d,%d]\n",room.areaName.c_str(),room.bounds.size.x,room.bounds.size.y);

    // std::cout << "Room memory usage: " << __memsizeToString(room.getMemoryUsage()) << std::endl;

    return 0;
}
#pragma endregion
#pragma region game::clean
void game::clean(){
    logger::info("Cleaning game components...");

    bank::destroyAll();

    display.destroy();
}
#pragma endregion
