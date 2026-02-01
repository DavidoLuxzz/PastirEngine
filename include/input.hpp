#pragma once
#ifndef __INPUT_HPP
#define __INPUT_HPP

namespace keyboard {
    /**
     * Fetches the keyboard state into the local ALLEGRO_KEYBOARD_STATE object.
     * The next keyDown(<key>) calls will use the fetched state
     */
    void fetchKeyboardState();
    /**
     * Checks if the specified key is currently pressed in current keyboard state.
     * 
     * @param key keycode
     * 
     * @return true if the key is down, false if not
     */
    bool keyDown(int key);

    /**
     * Checks if the specified key is currently pressed.
     * Fetches the keyboard state in stack (not into local variable).
     * Generally you should not use this except if only checking one key per tick update.
     * 
     * For multiple key checks use:
     * @code keyboard::fetchKeyboardState();
     * @code if (keyboard::keyDown(<key1>)) ...
     * @code if (keyboard::keyDown(<key2>)) ...
     * 
     * @param key keycode
     * 
     * @return true if the key is down, false if not
     */
    bool singleKeyDown(int key);
} // namespace keyboard


#endif