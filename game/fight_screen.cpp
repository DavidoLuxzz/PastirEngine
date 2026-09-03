#include <game/fight_screen.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <components/display.hpp>
#include <game/global.hpp>
#include <game/game.hpp>
#include <components/dialogbox.hpp>
#include <input.hpp>
#include <algorithm>

#define THIS_ROOM global::get().rooms[roomID]
#define player (Game::getGame()->player)

#pragma region events
void FightScreen::handleEvents() {
    ALLEGRO_EVENT evt;
    while (Display::getCurrentDisplay()->getEventQueue().popNext(&evt)) {
        if (evt.type==ALLEGRO_EVENT_DISPLAY_CLOSE) {
            global::get().running = false;
            return;
        }
        if (evt.type==ALLEGRO_EVENT_KEY_DOWN) switch (evt.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE: {
                global::get().running = false; // quit (debug)
                global::get().currentScreen = global::GAME;
                return;
            };
            case ALLEGRO_KEY_G:
                global::get().f3 ^= true;
                break;
            case ALLEGRO_KEY_SPACE: {
                Rectf hitbox = player.getHitbox();
                blasts.push_back(Blast(Blast::HORIZONTAL, hitbox.min.y+hitbox.size.y/2, 100.0f, 50, 0.04f));
                blasts.push_back(Blast(Blast::VERTICAL, hitbox.min.x+hitbox.size.x/2, 100.0f, 50, 0.04f));
                break;
            }
            default:
                break;
        }
    }
}

#pragma region update
void FightScreen::update(float ms){
    Display* display = Display::getCurrentDisplay();
    keyboard::fetchKeyboardState();
    if (!(dialogbox::isShowing()||display->isFading())){
        float dx = (keyboard::keyDown(ALLEGRO_KEY_RIGHT) - keyboard::keyDown(ALLEGRO_KEY_LEFT))
                    * player.getSpeed() * ms;
        float dy = (keyboard::keyDown(ALLEGRO_KEY_DOWN)  - keyboard::keyDown(ALLEGRO_KEY_UP))
                    * player.getSpeed() * ms;

        float speedmul = (keyboard::keyDown(ALLEGRO_KEY_C)&&player.isUsingNikes())? 1.5f:1.0f;

        player.setSpeedMul(speedmul);
        game_move(dx,dy);
    }
    display->update(ms);

    // Blasts (horizontal dead zones)
    std::erase_if(blasts, [](Blast& b) { return b.isFinished(); });

    for (Blast& blast : blasts) {
        blast.update();
    }
}
#pragma region draw

int3 textRGB = {255,255,255};
#include <cmath>
void FightScreen::draw(){
    Display::clear(0,0,0);

    // Draw room back layer
    THIS_ROOM.drawBackLayer();

    // Draw player
    float2 shadowPos = {
        player.getScreenPosition().x+player.getScreenHitbox().size.x/2.0f,
        player.getScreenFeetY()-8.0f
    };
    al_draw_filled_ellipse(shadowPos.x,shadowPos.y,40.f,10.f, al_map_rgba(0,0,0,20));
    player.draw();

    // Draw blasts
    for (Blast& b : blasts)
        b.draw(THIS_ROOM.getTranslate());

    // Draw room top layer
    THIS_ROOM.drawTopLayer();

    // Show dialogbox (kada treba)
    if (dialogbox::isShowing()) dialogbox::draw();

    // Debug hitboxes
    if (global::get().f3) {
        // Solid drawables and room hitboxes
        for (const Drawable::DrawableData& drw : THIS_ROOM.objects) {
            if (drw[Drawable::COMP_SOLID])
                Game::drawRectf(Drawable::createHitbox(drw), al_map_rgb(255,255,50), THIS_ROOM.getTranslate());
        }
        // Player hitbox
        Game::drawRectf(player.getHitbox(), al_map_rgb(50,255,50), THIS_ROOM.getTranslate());
        // Trigger hitboxes
        for (int i=0; i<triggers::getThisRoomTriggerCount(); i++) {
            Game::drawRectf(
                Trigger::createHitbox(triggers::get(i), THIS_ROOM.getTranslate()),
                al_map_rgb(50,50,triggers::get(i)[Trigger::COMP_ACTION]!=0?255:50)
            );//, room.getTranslate());
        }
        // Entity hitboxes
        for (const StaticEntity::EntityData& ent : THIS_ROOM.entities) {
            Game::drawRectf(StaticEntity::createHitbox(ent),
                al_map_rgb(50,50,255), THIS_ROOM.getTranslate());
        }
        // Blast hitboxes
        for (const Blast& b : blasts) {
            Game::drawRectf(b.getHitbox(), al_map_rgb(255,50,50), THIS_ROOM.getTranslate());
        }
        // Debug text
        Game::getGame()->debugText();
    }

    Display::getCurrentDisplay()->drawFade();

    Display::useCustomScale(4.f);
    al_draw_text(Game::getGame()->font, al_map_rgb(textRGB.r,textRGB.g,textRGB.b), 55.f,20.f, 0, "THIS IS A FIGHT SCREEN");
    Display::useScale();
    Display::swapBuffers();

    textRGB.r = (textRGB.r+1)%256;
    textRGB.g = (textRGB.g-1)%256;
    textRGB.b = (textRGB.b+2)%256;
}

#pragma region game_move

void FightScreen::game_move(float dx, float dy) {
    // Move player
    player.move(dx,dy, roomID);

    // Adjust camera
    THIS_ROOM.position(player.getWorldPosition());
    player.positionRoom(THIS_ROOM.getTranslate());

    // Orientate player
    player.orientate(dx,dy);
}