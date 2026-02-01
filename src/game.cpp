#include <game.hpp>
#include <iostream>
#include <components/display.hpp>
#include <logger.hpp>
#include <bank.hpp>
#include <asset_manager.hpp>
#include <sprite/Drawable.hpp>
#include <input.hpp>

// TODO: Bank<T> class

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 640
#define PIXEL_SCALE 4.0f

Display display;
Drawable drawable;


#pragma region game::run

int game::run(){
    unsigned int frames = 0;
    double lastTime = 0.0;
    while (true) {
        /* handle events: */ {
            ALLEGRO_EVENT evt;
            while (display.getEventQueue()->popNext(&evt)) {
                if (evt.type==ALLEGRO_EVENT_DISPLAY_CLOSE) return 0;
                if (evt.type==ALLEGRO_EVENT_KEY_DOWN && evt.keyboard.keycode == ALLEGRO_KEY_ESCAPE) return 0;
            }
        } // end handling events

        frames++;
        if (al_get_time()-lastTime >= 1.0) {
            lastTime = al_get_time();
            display.setTitle(  (std::string("DEMO FPS: ")+std::to_string(frames)).c_str()  );
            frames = 0;
        }

        // ## UPDATE ## //
        update();

        /* DRAWING */ {
            Display::clear(100,0,0);
            drawable.draw();
            Display::swapBuffers();
        }
    }

    return 0;
}

#pragma endregion

#pragma region game::update

void game::update() {
    keyboard::fetchKeyboardState();
    float dx = (keyboard::keyDown(ALLEGRO_KEY_RIGHT)-keyboard::keyDown(ALLEGRO_KEY_LEFT)) * 2.0f;
    float dy = (keyboard::keyDown(ALLEGRO_KEY_DOWN)-keyboard::keyDown(ALLEGRO_KEY_UP)) * 2.0f;
    float2 pos = drawable.getPosition();
    // drawable.setPosition(pos.x+dx, pos.y+dy);
    drawable.move(dx,dy);
}

#pragma endregion


#pragma region game::init

#define LUKA_ASSERT0(x) if (x) return -1;
#define LUKA_ASSERT1(x) if (x<0) return -1;

int game::init(){
    int __assets_path_err = 0;
    std::string __assets_path;
    //__assets_path = assman::getallegropathstr(ALLEGRO_RESOURCES_PATH, &__assets_path_err);
    __assets_path = "/Users/luka/eclipse-workspace/Pastir-igrica/assets";
    printf("> Setting resources path to %s [errors=%d, %d]\n", __assets_path.c_str(), __assets_path_err, assman::setcwd(__assets_path));


    LUKA_ASSERT0(display.create(WINDOW_WIDTH, WINDOW_HEIGHT, "DEMO"));
    display.useScale(PIXEL_SCALE, PIXEL_SCALE);
    bank::init(1);
    TextureBank textureBank;
    LUKA_ASSERT0(textureBank.init(Drawable::DRAWABLE_TEXTURE_COUNT));
    LUKA_ASSERT0(textureBank.loadTextures(NULL, Drawable::TEXTURES, 0, Drawable::DRAWABLE_TEXTURE_COUNT, ".png",  ALLEGRO_VIDEO_BITMAP));
    bank::makeGlobal(textureBank, BANK_MAP_DRAWABLE_TEXTUREBANK);

    drawable.init(Drawable::TEXTURE_GRASS, 100.0f, 100.0f);

    return 0;
}
#pragma endregion
#pragma region game::clean
void game::clean(){
    logger::info("Cleaning game components...");

    bank::destroyAll();
    bank::free();

    display.destroy();
}
#pragma endregion