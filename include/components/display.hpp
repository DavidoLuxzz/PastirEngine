#pragma once
#ifndef __DISPLAY_HPP
#define __DISPLAY_HPP

#include <allegro5/display.h>
#include <components/eventqueue.hpp>

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
    Display(int w, int h, const char* title=NULL);
    /**
     * Generally still should use destroy() function in game's cleanup function.
     */
    ~Display() = default;

    /**
     * Creates display.
     * Use al_set_new_display_[option/flags](...) before calling creating to configure.
     * @param width - Width of the display
     * @param height - Height of the display
     * @returns error code
     */
    int create(int width, int height, const char* title=NULL);
    /**
     * Destroys this display object.
     * After this function, the display object could be created again without created a new variable.
     * But consider it a bad practice.
     */
    void destroy();

    /**
     * Clears current selected backbuffer to the color
     */
    static void clear(int r, int g, int b);
    /**
     * Does al_flip_display(), but the function name comes from GLFW-ish style
     */
    static void swapBuffers();

    /**
     * Scales everything
     */
    static void useScale(float sx, float sy);
    static void dontUseScale();

    /**
     * Sets the title for this display
     */
    void setTitle(const char* title);

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