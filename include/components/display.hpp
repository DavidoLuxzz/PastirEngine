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
    // static things
    static float PIXEL_SCALE;
    static Display* _currentDisplay;
    // for this object
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
     * @param title - Title of the display
     * @param use_scale - Describes if to use the global static scale defined by Display::setPixelScale(float)
     * @returns error code
     */
    int create(int width, int height, const char* title=NULL, bool use_scale=false);
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
    static void useCustomScale(float sx, float sy);
    /**
     * Use the static scale set up by Display::setPixelScale(float).
     */
    static void useScale();
    static void dontUseScale();

    /**
     * Sets the title for this display
     */
    void setTitle(const char* title);

    const char* getTitle() const;
    int getWidth() const;
    int getHeight() const;

    /**
     * @returns @code{ALLEGRO_DISPLAY* _display}
     */
    ALLEGRO_DISPLAY* getAllegroDisplay() const;
    /**
     * @returns Pointer to @code{EventQueue _evqueue}
     */
    const EventQueue& getEventQueue() const;
    bool isCreated() const;

    /// @brief Sets the global static pixel scale. This value is equal to Map Drawable pixel scale. (<=>)
    static void setPixelScale(float);
    /// @returns The global static pixel scale 
    static float getPixelScale();


    /**
     * Makes the display current. Next display calls
     * will be redirected to the current display.
     * Does:
     *  al_set_target_backbuffer(display)
     * 
     * Note: Display create(2) function will by default set
     *       itself as the current display if the current
     *       display is NULL.
     *       This also applies to constructors with same
     *       parameters, for they call create(2).
     */
    static void makeCurrent(Display*);
    static Display* getCurrentDisplay();
};



#endif