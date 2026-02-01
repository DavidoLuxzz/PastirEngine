#include <input.hpp>
#include <allegro5/keyboard.h>

namespace keyboard {
    ALLEGRO_KEYBOARD_STATE _kbState;
} // namespace keyboard

void keyboard::fetchKeyboardState() {
    al_get_keyboard_state(&_kbState);
}
bool keyboard::keyDown(int keycode) {
    return al_key_down(&_kbState, keycode);
}

bool keyboard::singleKeyDown(int keycode) {
    ALLEGRO_KEYBOARD_STATE state;
    al_get_keyboard_state(&state);
    return al_key_down(&state, keycode);
}