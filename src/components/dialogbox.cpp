#include <components/dialogbox.hpp>
#include <sprite/sprite.hpp>
#include <allegro5/allegro_font.h>
#include <components/display.hpp>
#include <game/game.hpp>
#include <audio.hpp>

namespace dialogbox {
    Sprite view;
    bool showing = false;
    int currentDialog = 0;
    constexpr float scale = 3.0f/4.0f;
    dialog_t GAME_DIALOGS[NUM_GAME_DIALOGS];
    Animation animation;
    audio::Sound voice = audio::Sound::SOUND_NONE;
} // namespace dialogbox

void __dialogbox_tick(int frame) {
    if (dialogbox::voice>=audio::Sound::SOUND_COUNT) return;
    if (isalnum(dialogbox::GAME_DIALOGS[dialogbox::currentDialog].pages[0][frame])) {
        audio::playSound(dialogbox::voice, 3.0f);
    }
}

int dialogbox::init() {
    // load sprite (view)
    bank::TextureInfo dialogboxTexture = {
        .bankType = bank::TILESET,
        .bankID = bank::tileset::DIALOG_BOX,
        .tileID = 0
    };
    view.setTexture(dialogboxTexture);
    view.setScale(0.8f / scale, 0.5f / scale);
    view.setPosition(6.0f/scale, 2.0f);

    // init dialogs
    _loadDialogs(GAME_DIALOGS);

    // init animation
    animation.init(0.05);
    animation.setTickFunction(__dialogbox_tick);
    return 0;
}

void dialogbox::show(bool t) {
    showing = t;
    animation.cycleCount = GAME_DIALOGS[currentDialog].pages[0].length();
    animation.frame = 0;
}
void dialogbox::hide() {
    showing = false;
}
bool dialogbox::isShowing() {
    return showing;
}
void dialogbox::setVoice(int sound) {
    voice = static_cast<audio::Sound>(sound);
}

void dialogbox::_update() {
    if (showing) {
        animation.update();
    }
}

void dialogbox::draw() {
    if (!showing) return;
    Display::useCustomScale(Display::getPixelScale() * scale);

    const float winHeight = Display::getCurrentDisplay()->getHeight() / Display::getPixelScale() / scale;
    if (Game::getGame()->player.getScreenPosition().y * Display::getPixelScale() * scale < winHeight) {
        view.setPosition(view.getPosition().x, winHeight - view.getTile().size.y*scale);
    } else view.setPosition(view.getPosition().x, 2.0f);
    
    view.drawWhole();

    // printf("Animation frame: %d\n", animation.frame);

    constexpr static float max_line_width = (float)WINDOW_WIDTH / scale - 40.0f;

    al_draw_multiline_textf(
        Game::getGame()->font,
        al_map_rgb(255,255,255),
        view.getPosition().x+20.0f, view.getPosition().y+10.0f,
        max_line_width, 20.0f,
        0, "%s",
        GAME_DIALOGS[currentDialog].pages[0].substr(0,animation.frame).c_str()
    );

    Display::useScale();

    _update();
}



void dialogbox::setDialog(int id) {
    currentDialog = id;
}
const dialogbox::dialog_t& dialogbox::getDialog(int id) {
    return GAME_DIALOGS[id];
}
void dialogbox::setText(const std::string s) {    
    GAME_DIALOGS[MODIFIABLE_DIALOG_ID].pages[0] = s;
    GAME_DIALOGS[MODIFIABLE_DIALOG_ID].numPages = 1;
    currentDialog = MODIFIABLE_DIALOG_ID;
}
