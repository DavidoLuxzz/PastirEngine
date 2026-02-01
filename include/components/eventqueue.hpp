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
    bool popNext(ALLEGRO_EVENT* out_event);

    /**
     * Returns allegro event queue.
     */
    ALLEGRO_EVENT_QUEUE* getAllegroEventQueue();

    /**
     * Registeres event source to queue.
     */
    void registerEventSource(ALLEGRO_EVENT_SOURCE* esrc);
    /**
     * Registeres keyboard event source to queue.
     */
    void registerKeyboardEventSource();
    /**
     * Registeres display event source to queue.
     */
    void registerDisplayEventSource(ALLEGRO_DISPLAY* disp);

    /**
     * Unregisteres event source from queue.
     */
    void unregisterEventSource(ALLEGRO_EVENT_SOURCE* esrc);
    /**
     * Unregisteres keyboard event source from queue.
     */
    void unregisterKeyboardEventSource();
    /**
     * Unregisteres display event source from queue.
     */
    void unregisterDisplayEventSource(ALLEGRO_DISPLAY* disp);
    

};



#endif