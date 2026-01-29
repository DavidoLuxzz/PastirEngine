#pragma once
#ifndef __DISPLAY_HPP
#define __DISPLAY_HPP

#include <allegro5/display.h>
#include <eventqueue.hpp>

/**
 * Display object that uses ALLEGRO_DISPLAY as base
 */
class Display {
private:
    ALLEGRO_DISPLAY* _display = NULL;
    EventQueue _evqueue;
public:
    /**
     * Empty constructor. Need to call create()
     */
    Display() = default;
    /**
     * @short Calls create(w,h)
     */
    Display(int w, int h);
    /**
     * Generally still should use destroy() function in game's cleanup function.
     */
    ~Display();

    /**
     * Creates display.
     * Use al_set_new_display_[option/flags](...) before calling creating to configure.
     * @param width - Width of the display
     * @param height - Height of the display
     * @returns error code
     */
    int create(int width, int height);
    /**
     * Destroys this display object.
     * After this function, the display object could be created again without created a new variable.
     * But consider it a bad practice.
     */
    void destroy();

    /**
     * @returns @code{ALLEGRO_DISPLAY* _display}
     */
    ALLEGRO_DISPLAY* getAllegroDisplay() const;
    /**
     * @returns Pointer to @code{EventQueue _evqueue}
     */
    EventQueue* getEventQueue();
    bool isCreated() const;
};



#endif