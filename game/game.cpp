#include <game.hpp>
#include <iostream>
#include <components/display.hpp>
#include <logger.hpp>
#include <bank.hpp>
#include <asset_manager.hpp>
#include <sprite/Drawable.hpp>
#include <input.hpp>
#include <level/RoomLoader.hpp>
#include <components/utility.hpp>
#include <sprite/Player.hpp>
#include <level/Triggers.hpp>
#include <components/dialogbox.hpp>
#include <event.hpp>
#include <audio.hpp>
#include <allegro5/allegro_font.h>

#define TEST_DRAW_SAMPLES 1

#pragma region game::run

bool ___zPressedThisFrame = false;

int Game::run(){
    // unsigned int frames = 0;
    double lastTime = 0.0;
    while (true) {
        double deltaTime = al_get_time() - lastTime; // seconds?
        lastTime = al_get_time();
        // printf("%f\n", deltaTime);
        /* handle events: */ {
            ALLEGRO_EVENT evt;
            while (display.getEventQueue().popNext(&evt)) {
                if (evt.type==ALLEGRO_EVENT_DISPLAY_CLOSE) return 0;
                if (evt.type==ALLEGRO_EVENT_KEY_DOWN) switch (evt.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: return 0;
                    case ALLEGRO_KEY_SPACE: {
                        dialogbox::show(!dialogbox::isShowing());
                        break;
                    }
                    case ALLEGRO_KEY_F3:
                        f3 = !f3;
                        break;
                    case ALLEGRO_KEY_R: {
                        loadRooms();
                        bank::destroyAll();
                        loadAssets();
                        break;
                    }
                    case ALLEGRO_KEY_Q:
                        player.setInvincible(!player.isInvincible());
                        break;
                    case ALLEGRO_KEY_Z:
                        if (dialogbox::isShowing()) dialogbox::hide();
                        else ___zPressedThisFrame = true;
                        break;
                    default:
                        break;
                }
            }
        } // end handling events

        display.setTitle(  (std::string("DEMO FPS: ")+std::to_string((int)round(1.0/deltaTime))+" Sprites: "+std::to_string(TEST_DRAW_SAMPLES*rooms[roomID].objects.size())).c_str()  );

        // ## UPDATE ## //
        keyboard::fetchKeyboardState();
        if (!(dialogbox::isShowing()||display.isFading())) update(deltaTime);
        display.update(deltaTime*1000.0f);
        if (display.isFading()) {
            // printf("Display fade: %d\n", display.getFadeFrame());
            if (display.getFadeFrame()==display.getFadeCycleCount()/2) {
                immidiatelyChangeRoom();
                game_move(0.0f,0.0f);
            }
        }

        /* DRAWING */
        draw();

        ___zPressedThisFrame = false;
    }

    return 0;
}

#pragma endregion

#pragma region game::draw

void Game::debugText() {
    constexpr float __px_scale = 2.0f;
    Display::useCustomScale(__px_scale, __px_scale);

    Rectf playerHitbox = player.getHitbox();

    al_draw_textf(font, al_map_rgb(255,255,255), 0, 0, 0, "Player pos: %.1f %.1f [%.0fx%.0f]", playerHitbox.min.x,playerHitbox.min.y, playerHitbox.size.x,playerHitbox.size.y);
    al_draw_textf(font, al_map_rgb(255,255,255), 0, 30.0f, 0, "Debug (show hitboxes): %s", f3?"true":"false");

    Display::useScale();
}
#include <allegro5/allegro_primitives.h>
inline void drawRectf(const Rectf rect, ALLEGRO_COLOR color, float2 translate={0,0}) {
    float x = rect.min.x + translate.x;
    float y = rect.min.y + translate.y;
    al_draw_rectangle(x,y, x+rect.size.x,y+rect.size.y, color, 4.0f);
}
void Game::draw() {
    Display::clear(0,0,0);

    // Draw room back layer
    for (int i=0; i<TEST_DRAW_SAMPLES; i++)
        rooms[roomID].drawBackLayer();
    // Draw player
    player.draw();
    // Draw room top layer
    for (int i=0; i<TEST_DRAW_SAMPLES; i++)
        rooms[roomID].drawTopLayer();

    // Show dialogbox (kada treba)
    if (dialogbox::isShowing()) dialogbox::draw();

    // Debug hitboxes
    if (f3) {
        for (const Drawable::DrawableData& drw : rooms[roomID].objects) {
            drawRectf(Drawable::createHitbox(drw), al_map_rgb(255,255,50), rooms[roomID].getTranslate());
        }
        drawRectf(player.getHitbox(), al_map_rgb(50,255,50), rooms[roomID].getTranslate());
        for (int i=0; i<triggers::getThisRoomTriggerCount(); i++) {
            drawRectf(
                Trigger::createHitbox(triggers::get(i), rooms[roomID].getTranslate()),
                al_map_rgb(triggers::get(i)[Trigger::COMP_ACTION]!=event::NONE?255:50,50,50)
            );//, room.getTranslate());
        }
        for (const StaticEntity::EntityData& ent : rooms[roomID].entities) {
            drawRectf(StaticEntity::createHitbox(ent),
                al_map_rgb(50,50,255), rooms[roomID].getTranslate());
        }
        debugText();
    }

    display.drawFade();
    Display::swapBuffers();
}

#pragma endregion

#pragma region game::update

void Game::game_move(float dx, float dy) {
    // Move player
    player.move(dx,dy);

    // Adjust camera
    rooms[roomID].position(player.getWorldPosition());
    player.positionRoom(rooms[roomID].getTranslate());

    // Orientate player
    player.orientate(dx,dy);
}

void Game::immidiatelyChangeRoom() {
    roomID = requestRoomID;
    triggers::prepare(roomID);
    player.setRoom(&rooms[roomID]);
    player.setWorldPosition(requestPlayerCoords);
}

void Game::update(float ms) {
    // if (requestRoomID != roomID) immidiatelyChangeRoom();
    float dx = (keyboard::keyDown(ALLEGRO_KEY_RIGHT) - keyboard::keyDown(ALLEGRO_KEY_LEFT))
                * player.getSpeed() * ms;
    float dy = (keyboard::keyDown(ALLEGRO_KEY_DOWN)  - keyboard::keyDown(ALLEGRO_KEY_UP))
                * player.getSpeed() * ms;

    float speedmul = (keyboard::keyDown(ALLEGRO_KEY_C)&&player.isUsingNikes())? 1.5f:1.0f;

    for (const Drawable::DrawableData& data : rooms[roomID].objects) {
        if (data[Drawable::COMP_TEXTURE_ID] == Drawable::TEXTURE_COBWEB) {
            if (Drawable::createHitbox(data).intersects(player.getHitbox())) {
                speedmul *= 0.5f;
                break;
            }
        }
    }

    player.setSpeedMul(speedmul);
    game_move(dx,dy);

    // triggers::check_update();
}

#pragma endregion


#pragma region game::init

#define LUKA_ASSERT0(x) if (x) return -1;
#define LUKA_ASSERT1(x) if (x<0) return -1;


void setupAssman() {
    int __assets_path_err = 0;
    std::string __assets_path;
    __assets_path = assman::getallegropathstr(ALLEGRO_RESOURCES_PATH, &__assets_path_err);
    //__assets_path = std::getenv("HOME");
    __assets_path += "assets";
    printf("> Setting resources path to %s [errors=%d, %d]\n", __assets_path.c_str(), __assets_path_err, assman::setcwd(__assets_path));
}


int initDisplay() {
    Display::setupPixelScale(1.0f);
    LUKA_ASSERT0(game::getGame()->display.create(WINDOW_WIDTH, WINDOW_HEIGHT, "DEMO", true));
    game::getGame()->display.getEventQueue().registerKeyboardEventSource();

    // int dpi = al_get_monitor_dpi(al_get_display_adapter(display.getAllegroDisplay()));
    return 0;
}

int Game::loadAssets() {
    /* Bank loading */{
        bank::tileset::init(bank::tileset::NUM_KNOWN_BANKS);
        // Map drawables
        bank::tileset::getBank(bank::tileset::MAP_DRAWABLES).loadTexture("drawables.png");
        bank::tileset::getBank(bank::tileset::MAP_DRAWABLES).loadTileRects("drawable_rects.txt");
        // Player tilesheet
        bank::tileset::getBank(bank::tileset::PLAYER).loadTexture("player.png");
        bank::tileset::getBank(bank::tileset::PLAYER).loadTileRects("player_rects.txt");
        // Dialog box
        bank::tileset::getBank(bank::tileset::DIALOG_BOX).loadTexture("dialog_box.png");
        bank::tileset::getBank(bank::tileset::DIALOG_BOX).registerTile({{0,0},{236,128}});

        // Entities
        bank::tileset::getBank(bank::tileset::ENTITY0).loadTexture("nike_shoes.png");
        bank::tileset::getBank(bank::tileset::ENTITY0).registerTile({{0,0},{100,65}});
    }
    return 0;
}
int Game::loadRooms() {
    for (int i=0; i<NUM_ROOMS; i++) {
        LUKA_ASSERT0(room_loader::load(i)); // .txt
        room_loader::swapData(rooms[i]);
    }

    if (triggers::load()) {
        printf("Problem loading triggers\n");
    }
    triggers::prepare(roomID);
    // std::cout << triggers::get(0)[Trigger::COMP_X] << std::endl;
    return 0;
}

void initPlayer() {
    Game* game = game::getGame();
    Player& player = game->player;
    player.setTexturesBankType(bank::TILESET);
    player.setTexturesBankID(bank::tileset::PLAYER);
    // player.setScale(0.5f);
    player.setScale(3.f);
    //player.setCenter(WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f);
    //player.setWorldPosition(player.getPosition());
    player.setWorldPosition({24.0f,24.0f});
    // player.setWorldPosition({0.0f,0.0f});
    player.setRoom(&game->rooms[game->roomID]);
    game->game_move(0.0f,0.0f); // init step, positioning
}

int Game::init(){
    font = al_create_builtin_font();

    setupAssman();
    initDisplay();
    
    LUKA_ASSERT0(loadAssets());
    LUKA_ASSERT0(loadRooms());
    initPlayer();
    LUKA_ASSERT0(dialogbox::init());
    LUKA_ASSERT0(audio::init());

    audio::playStream(audio::Stream::AUDIO_07);
    dialogbox::setVoice(audio::Sound::VOICE01);

    // dialogbox::setText("Hallo!!");
    // dialogbox::show();

    return 0;
}

#pragma endregion
#pragma region game::clean
void Game::clean(){
    logger::info("Cleaning game components...");

    bank::destroyAll();
    display.destroy();
}
#pragma endregion


bool Game::isZPressed() {
    return keyboard::keyDown(ALLEGRO_KEY_Z);
}
bool Game::isZPressedThisFrame() {
    return ___zPressedThisFrame;
}






namespace game { Game* game; }

void game::makeCurrent(Game* _gm) {
    game = _gm;
}
Game* game::getGame() {
    return game;
}