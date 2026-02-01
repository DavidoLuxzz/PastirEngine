#include <components/display.hpp>
#include <logger.hpp>


Display::Display(int w, int h, const char* title) {
    create(w,h);
}

int Display::create(int w, int h, const char* title) {
    al_set_new_display_flags(ALLEGRO_WINDOWED || ALLEGRO_OPENGL || ALLEGRO_OPENGL_FORWARD_COMPATIBLE);
    al_set_new_display_option(ALLEGRO_VSYNC, true, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_OPENGL_MAJOR_VERSION, 4, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_OPENGL_MINOR_VERSION, 1, ALLEGRO_SUGGEST);
    al_set_new_window_title(title);
    _display = al_create_display(w,h);
    if (!_display){
        logger::err("display zeza");
        return -1;
    }
    _evqueue.create();
    _evqueue.registerDisplayEventSource(_display);
    _evqueue.registerKeyboardEventSource();

    // post initialization
    // if (!al_get_new_display_option(ALLEGRO_VSYNC, NULL)) logger::info("VSync is off");
    int opt_vsync = al_get_new_display_option(ALLEGRO_VSYNC, NULL);
    int opt_gl_major = al_get_new_display_option(ALLEGRO_OPENGL_MAJOR_VERSION, NULL);
    int opt_gl_minor = al_get_new_display_option(ALLEGRO_OPENGL_MINOR_VERSION, NULL);

    printf("Allegro %s with OpenGL %d.%d; VSync=%d\n", ALLEGRO_VERSION_STR, opt_gl_major,opt_gl_minor,opt_vsync);



    return 0;
}
void Display::destroy() {
    al_destroy_display(_display);
    _display = NULL;
}

void Display::clear(int r, int g, int b){
    al_clear_to_color(al_map_rgb(r,g,b));
}
void Display::swapBuffers(){
    al_flip_display();
}

void Display::setTitle(const char* title){
    al_set_window_title(_display, title);
}


ALLEGRO_DISPLAY* Display::getAllegroDisplay() const {
    return _display;
}

bool Display::isCreated() const {
    return _display!=NULL;
}

EventQueue* Display::getEventQueue() {
    return &_evqueue;
}



void Display::useScale(float sx, float sy){
    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    al_scale_transform(&trans, sx, sy);
    al_use_transform(&trans);
}
void Display::dontUseScale(){
    al_use_transform(NULL);
}