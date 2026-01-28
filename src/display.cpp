#include <display.hpp>
#include <logger.hpp>

Display::Display() {}
Display::~Display() {
    destroy();
}

Display::Display(int w, int h) {
    create(w,h);
}

int Display::create(int w, int h) {
    al_set_new_display_flags(ALLEGRO_WINDOWED || ALLEGRO_OPENGL || ALLEGRO_OPENGL_FORWARD_COMPATIBLE);
    al_set_new_display_option(ALLEGRO_VSYNC, true, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_OPENGL_MAJOR_VERSION, 4, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_OPENGL_MINOR_VERSION, 1, ALLEGRO_SUGGEST);
    _display = al_create_display(w,h);
    if (!_display){
        logger::err("display zeza");
        return -1;
    }
    return 0;
}
void Display::destroy() {
    al_destroy_display(_display);
}

ALLEGRO_DISPLAY* Display::getAllegroDisplay(){
    return _display;
}

bool Display::isCreated(){
    return _display!=NULL;
}