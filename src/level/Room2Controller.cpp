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
#define player Game::getGame()->player

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
    if (playing) audio::fadeStream(stream,1.f);
    Game::getGame()->player.enableTrail(true);
}

void Room2Controller::exit() {
    playing = audio::isStreamPlaying(stream);
    audio::stopStream(stream);
    Game::getGame()->player.enableTrail(false);
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
    const float2 roomTranslate = THIS_ROOM.getTranslate();
    static constexpr Rectf mirrorBounds = {
        {100.f,10.f},
        {200.f,80.f}
    };
    static constexpr float wallHeight = 120.f;
    
    // draw mirrored player
    float2 screenPos = player.getWorldPosition() + roomTranslate; screenPos.y = -screenPos.y;
    bank::TextureInfo texInfo = player.getTexture();
    // 
    texInfo.tileID ^= (texInfo.tileID>>1)^1;
    player.drawInstance(screenPos, texInfo, player.getScale(), al_map_rgb(180,190,200), player.getAngle());

    /* gornji zid */
    al_draw_filled_rectangle(0.f,0.f, mirrorBounds.min.x+roomTranslate.x,wallHeight, al_map_rgb(10,10,10));
    al_draw_filled_rectangle(mirrorBounds.min.x+mirrorBounds.size.x+roomTranslate.x,0.f, 10000.f,wallHeight, al_map_rgb(10,10,10));
    al_draw_filled_rectangle(0.f,0.f, 10000.f,mirrorBounds.min.y, al_map_rgb(10,10,10));
    al_draw_filled_rectangle(0.f,mirrorBounds.min.y+mirrorBounds.size.y, 10000.f,wallHeight, al_map_rgb(10,10,10));

    // al_draw_filled_rectangle(   mirrorBounds.min.x+roomTranslate.x,
    //                             mirrorBounds.min.y+roomTranslate.y,
    //                             mirrorBounds.min.x+mirrorBounds.size.x+roomTranslate.x,
    //                             mirrorBounds.min.y+mirrorBounds.size.y+roomTranslate.y,
    //                             al_map_rgb(0,0,0));
    al_draw_rounded_rectangle(  mirrorBounds.min.x+roomTranslate.x,
                                mirrorBounds.min.y+roomTranslate.y,
                                mirrorBounds.min.x+mirrorBounds.size.x+roomTranslate.x,
                                mirrorBounds.min.y+mirrorBounds.size.y+roomTranslate.y,
                                2.f,2.f,
                                al_map_rgb(100,100,100), 8.f);

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
        float2 pos = positions[i] + roomTranslate;
        al_draw_filled_ellipse(pos.x, pos.y, 20.f+i*3%7, 10.f, al_map_rgb(col,col,col));
    }
}
void Room2Controller::drawTopLayer() {
    // al_draw_textf(Game::getGame()->font, al_map_rgb(200,200,200), 10.f,10.f,0, "Pan: %.2f", test);
    if (audio::isStreamPlaying((audio::Stream) triggers::get(1)[Trigger::COMP_SPECIAL]))
        al_draw_prim(gradient, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);

    float2 trans = THIS_ROOM.getTranslate() - player.getWorldPosition()/10.f;
    static constexpr float2 xw[25] = {
        {600.f,100.f},
        {900.f,150.f},
        {1170.f,170.f},
        {1500.f,80.f},
        {1830.f,40.f},
        {2000.f,100.f},
        {2400.f,120.f},
        {2600.f,90.f},
        {2900.f,150.f},
        {3170.f,170.f},
        {3500.f,80.f},
        {3830.f,70.f},
        {4000.f,100.f},
        {4400.f,100.f},
        {4700.f,50.f},
        {4970.f,100.f},
        {5200.f,130.f},
        {5370.f,150.f},
        {5600.f,80.f},
        {5830.f,140.f},
        {6000.f,100.f},
        {6400.f,100.f},
        {6620.f,77.f},
        {6870.f,90.f},
        {7100.f,100.f}
    };

    for (int i=0; i<25; i++)
        al_draw_filled_rectangle(xw[i].x+2*trans.x,0.f, xw[i].x+2*trans.x+xw[i].y, 10000.f, al_map_rgba(4,4,4,220+(int)xw[i].y%37));
}

// expand room
void Room2Controller::func0(void* args, int argc) {
    expand = *((int*)args);
}

void Room2Controller::func1(void* args, int argc) {}
void Room2Controller::func2(void* args, int argc) {}
void Room2Controller::func3(void* args, int argc) {}