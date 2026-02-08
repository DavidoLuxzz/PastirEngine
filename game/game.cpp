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

Display display;
Drawable drawable;
Room room;

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

        /* DRAWING */ {
            Display::clear(100,0,0);
            for (int i=0; i<TEST_DRAW_SAMPLES; i++)
                room.draw();
            Display::swapBuffers();
        }
    }

    return 0;
}

#pragma endregion

#pragma region game::update

void game::update() {
    keyboard::fetchKeyboardState();
    static const float speed = 1.0f;
    float dx = (keyboard::keyDown(ALLEGRO_KEY_RIGHT)-keyboard::keyDown(ALLEGRO_KEY_LEFT)) * speed;
    float dy = (keyboard::keyDown(ALLEGRO_KEY_DOWN)-keyboard::keyDown(ALLEGRO_KEY_UP)) * speed;
    // drawable.setPosition(pos.x+dx, pos.y+dy);
    room.move(-dx,-dy);
}

#pragma endregion


#pragma region game::init

#define LUKA_ASSERT0(x) if (x) return -1;
#define LUKA_ASSERT1(x) if (x<0) return -1;

int game::init(){
    int __assets_path_err = 0;
    std::string __assets_path;
    //__assets_path = assman::getallegropathstr(ALLEGRO_RESOURCES_PATH, &__assets_path_err);
    __assets_path = std::getenv("HOME");
    __assets_path += "/eclipse-workspace/Pastir-igrica/assets";
    printf("> Setting resources path to %s [errors=%d, %d]\n", __assets_path.c_str(), __assets_path_err, assman::setcwd(__assets_path));

    Display::setPixelScale(4.0f);

    LUKA_ASSERT0(display.create(WINDOW_WIDTH, WINDOW_HEIGHT, "DEMO", true));
    display.getEventQueue().registerKeyboardEventSource();
    /* Bank loading */{
        bank::tileset::init(1);
        TilesetBank tbank;
        tbank.loadTexture("drawables.png");
        tbank.loadTileRects("drawableTiles.txt");
        bank::tileset::makeGlobal(tbank, 0);
    }

    drawable.init(Drawable::TEXTURE_GRASS, 100.0f, 100.0f);


    room_loader::load(0); // .txt
    room_loader::swapData(room);

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
