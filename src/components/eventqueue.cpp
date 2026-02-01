#include <components/eventqueue.hpp>
#include <logger.hpp>

// initalization
int EventQueue::create() {
    if (_queue) {
        logger::warn("Tried to init already initialized EventQueue => nothing will happen");
        return 0;
    }
    _queue = al_create_event_queue();
    return _queue==NULL;
}
void EventQueue::destroy() {
    al_destroy_event_queue(_queue);
    _queue = NULL;
}

// register
void EventQueue::registerEventSource(ALLEGRO_EVENT_SOURCE* esrc){
    if (!esrc)
        logger::warn("registering NULL event source");
    al_register_event_source(_queue, esrc);
}
void EventQueue::registerDisplayEventSource(ALLEGRO_DISPLAY* disp){
    registerEventSource(al_get_display_event_source(disp));
}
void EventQueue::registerKeyboardEventSource(){
    registerEventSource(al_get_keyboard_event_source());
}

// unregister
void EventQueue::unregisterEventSource(ALLEGRO_EVENT_SOURCE* esrc){
    al_unregister_event_source(_queue, esrc);
}
void EventQueue::unregisterDisplayEventSource(ALLEGRO_DISPLAY* disp){
    unregisterEventSource(al_get_display_event_source(disp));
}
void EventQueue::unregisterKeyboardEventSource(){
    unregisterEventSource(al_get_keyboard_event_source());
}


// basic getters
ALLEGRO_EVENT_QUEUE* EventQueue::getAllegroEventQueue() {
    return _queue;
}

bool EventQueue::popNext(ALLEGRO_EVENT* out_evt) {
    if (!_queue) {
        logger::err("Event queue not initialized"); return 0;
    }
    return al_get_next_event(_queue, out_evt);
}