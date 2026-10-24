#include <level/Room2Controller.hpp>
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <level/Room.hpp>
#include <game/global.hpp>
#include <game/game.hpp>
#include <allegro5/allegro_audio.h>
#include <audio.hpp>
#include <level/Triggers.hpp>
#include <components/dialogbox.hpp>

#define THIS_ROOM (global::get().rooms[Game::getGame()->roomID])
#define stream ((audio::Stream) triggers::get(1)[Trigger::COMP_SPECIAL])

Room2Controller::Room2Controller() {
    init();
}

void Room2Controller::init() {
    printf("Initialized controller\n");
    gradient[0].color = al_map_rgba(255,255,255, 255);
    gradient[1].color = al_map_rgba(255,255,255, 0);
    gradient[2].color = al_map_rgba(255,255,255, 0);
    gradient[3].color = al_map_rgba(255,255,255, 255);

    for (int i=0; i<4; i++) gradient[i].x = gradientXs[i];
    gradient[0].y = 0.f;
    gradient[1].y = 0.f;
    gradient[2].y = 800.f;
    gradient[3].y = 800.f;
}

void Room2Controller::enter() {
    // nothing spec
    if (playing) audio::playStream(stream,true,0.f,0.f);
}

void Room2Controller::exit() {
    playing = audio::isStreamPlaying(stream);
    audio::stopStream(stream);
}

Room2Controller::~Room2Controller() {
    exit();
    printf("Room2Controller instance disabled\n");
}

void Room2Controller::update(double ms) {
    timer++;

    const float gramofonX = triggers::get(1)[Trigger::COMP_X]; // moze i da se nacentrira, al valjda nema potrebe

    if (audio::isStreamPlaying(stream)) {
        playing = true;
        float dist = (gramofonX - Game::getGame()->player.getWorldPosition().x) / 500.f;
        float pan = fmin(fmax(dist/5.f, -1.f), 1.f);
        al_set_audio_stream_pan(audio::getStream(stream), pan);

        float engineFadeGain = audio::getStreamEngineGain(stream);

        if (dist*dist>1.f) al_set_audio_stream_gain(audio::getStream(stream), engineFadeGain/(dist*dist));
        else al_set_audio_stream_gain(audio::getStream(stream), engineFadeGain);
    }

    if (expand != THIS_ROOM.bounds.size.x){
        if (!dialogbox::isShowing()){
            int dx = (expand-THIS_ROOM.bounds.size.x)<0? -2 : 2;
            THIS_ROOM.bounds.size.x += dx;
        }
    }

    for (int i=0; i<4; i++) gradient[i].x = gradientXs[i] + THIS_ROOM.getTranslate().x;
}

void Room2Controller::drawBackLayer() {
    static constexpr float2 positions[] = {
        {900.f, 350.f},
        {1080.f, 400.f},
        {1110.f, 360.f},
        {1210.f, 390.f},
        {1370.f, 340.f},
        {1420.f, 370.f},
        {1480.f, 350.f},
        {1540.f, 400.f},
        {1610.f, 360.f},
        {1660.f, 390.f},
        {1720.f, 340.f},
        {1820.f, 370.f}
    };
    static constexpr int max_col = 100; // 256 za max 255
    int _col = (timer%(2*max_col)>(max_col-1))? max_col-1-timer%max_col : timer%max_col;

    for (int i=0; i<12; i++) {
        int col = (_col+i*47)%255;
        float2 pos = positions[i] + THIS_ROOM.getTranslate();
        al_draw_filled_ellipse(pos.x, pos.y, 20.f+i*3%7, 10.f, al_map_rgb(col,col,col));
    }
}
void Room2Controller::drawTopLayer() {
    // al_draw_textf(Game::getGame()->font, al_map_rgb(200,200,200), 10.f,10.f,0, "Pan: %.2f", test);
    if (!audio::isStreamPlaying((audio::Stream) triggers::get(1)[Trigger::COMP_SPECIAL])) return;
    al_draw_prim(gradient, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
}

// expand room
void Room2Controller::func0(void* args, int argc) {
    expand = *((int*)args);
}

void Room2Controller::func1(void* args, int argc) {}
void Room2Controller::func2(void* args, int argc) {}
void Room2Controller::func3(void* args, int argc) {}