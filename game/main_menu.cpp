#include <game/main_menu.hpp>
#include <allegro5/allegro.h>
#include <components/display.hpp>
#include <game/global.hpp>

void MainMenu::handleEvents() {
    ALLEGRO_EVENT evt;
    while (Display::getCurrentDisplay()->getEventQueue().popNext(&evt)) {
        if (evt.type==ALLEGRO_EVENT_DISPLAY_CLOSE) {
            global::get().running = false;
            return;
        }
        if (evt.type==ALLEGRO_EVENT_KEY_DOWN) switch (evt.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE: {
                global::get().currentScreen = global::GAME;
                return;
            };
            case ALLEGRO_KEY_G:
                global::get().f3 ^= true;
                break;
            default:
                break;
        }
    }
}

void MainMenu::update(){}
void MainMenu::draw(){}