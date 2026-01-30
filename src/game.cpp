#include <game.hpp>
#include <iostream>
#include <display.hpp>
#include <logger.hpp>
#include <texture.hpp>
#include <asset_manager.hpp>


// TODO: Bank<T> class

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 640

Display display;
Texture texture;

int game::run(){
    unsigned int frames = 0;
    double lastTime = 0.0;
    while (true) {
        Display::swapBuffers();

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
    }

    return 0;
}

#define LUKA_ASSERT0(x) if (x) return -1;

int game::init(){
    int __assets_path_err = 0;
    std::string __assets_path;
    //__assets_path = assman::getallegropathstr(ALLEGRO_RESOURCES_PATH, &__assets_path_err);
    __assets_path = "/Users/luka/eclipse-workspace/Pastir-igrica/assets";
    printf("> Setting resources path to %s [errors=%d, %d]\n", __assets_path.c_str(), __assets_path_err, assman::setcwd(__assets_path));
    LUKA_ASSERT0(display.create(WINDOW_WIDTH, WINDOW_HEIGHT, "DEMO"));
    LUKA_ASSERT0(texture.load("block.png", ALLEGRO_VIDEO_BITMAP));

    return 0;
}
void game::clean(){
    logger::info("Cleaning game components...");

    texture.destroy();

    display.destroy();
}
