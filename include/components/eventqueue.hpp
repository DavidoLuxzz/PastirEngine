#pragma once
#ifndef __EVENTS_HPP
#define __EVENTS_HPP

#include <allegro5/allegro.h>

class EventQueue {
private:
    ALLEGRO_EVENT_QUEUE* _queue = NULL;
public:
    /**
     * Empty constructor. Need to call create()
     */
    EventQueue() = default;
    /// @brief destructor (does nothing). u bettr call destroy()
    ~EventQueue() = default;

    /**
     * Initializes the event queue
     */
    int create();
    /**
     * Releases event queue
     */
    void destroy();


    /**
     * Pops next event.
     * @returns true if has more events, false if
     */
    bool popNext(ALLEGRO_EVENT* out_event) const;

    /**
     * Returns allegro event queue.
     */
    ALLEGRO_EVENT_QUEUE* getAllegroEventQueue() const;

    /**
     * Registeres event source to queue.
     */
    void registerEventSource(ALLEGRO_EVENT_SOURCE* esrc) const;
    /**
     * Registeres keyboard event source to queue.
     */
    void registerKeyboardEventSource() const;
    /**
     * Registeres display event source to queue.
     */
    void registerDisplayEventSource(ALLEGRO_DISPLAY* disp) const;

    /**
     * Unregisteres event source from queue.
     */
    void unregisterEventSource(ALLEGRO_EVENT_SOURCE* esrc) const;
    /**
     * Unregisteres keyboard event source from queue.
     */
    void unregisterKeyboardEventSource() const;
    /**
     * Unregisteres display event source from queue.
     */
    void unregisterDisplayEventSource(ALLEGRO_DISPLAY* disp) const;
    

};



#endif