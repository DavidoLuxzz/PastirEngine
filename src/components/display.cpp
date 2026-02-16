#include <components/display.hpp>
#include <logger.hpp>

float Display::PIXEL_SCALE = 1.0f;
Display* Display::_currentDisplay = NULL;


Display::Display(int w, int h, const char* title) {
    create(w,h);
}

int Display::create(int _w, int _h, const char* title, bool use_scale) {
    int w = use_scale?_w*PIXEL_SCALE:_w;
    int h = use_scale?_h*PIXEL_SCALE:_h;
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
    if (!Display::_currentDisplay) {
        Display::makeCurrent(this);
    }
    _evqueue.create();
    _evqueue.registerDisplayEventSource(_display);

    if (use_scale) useScale();

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
const char* Display::getTitle() const {
    return "TODO jbg";
}
int Display::getWidth() const {
    return al_get_display_width(_display);
}
int Display::getHeight() const {
    return al_get_display_height(_display);
}

ALLEGRO_DISPLAY* Display::getAllegroDisplay() const {
    return _display;
}

bool Display::isCreated() const {
    return _display!=NULL;
}

const EventQueue& Display::getEventQueue() const {
    return _evqueue;
}



void Display::useCustomScale(float sx, float sy){
    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    al_scale_transform(&trans, sx, sy);
    al_use_transform(&trans);
}
void Display::useScale() {
    useCustomScale(PIXEL_SCALE, PIXEL_SCALE);
}
void Display::dontUseScale(){
    al_use_transform(NULL);
}

void Display::setPixelScale(float s) {
    PIXEL_SCALE = s;
    useScale();
}
float Display::getPixelScale() {
    return PIXEL_SCALE;
}
#include <cmath>
void Display::setupPixelScale(float scaleOn1080p) {
    int adapter = 0;
    if (_currentDisplay) adapter = al_get_display_adapter(_currentDisplay->getAllegroDisplay());
    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    int width = info.y2-info.y1;
    float scale = round(10 * width/1080.0f) / 10.0f;
    printf("Pixel scale set to %.2f\n", scale * scaleOn1080p);
    Display::setPixelScale(scaleOn1080p * scale);
}
void Display::makeCurrent(Display* disp) {
    _currentDisplay = disp;
    if (disp && disp->getAllegroDisplay()) {
        al_set_target_backbuffer(disp->getAllegroDisplay());
    }
}
Display* Display::getCurrentDisplay() {
    return _currentDisplay;
}