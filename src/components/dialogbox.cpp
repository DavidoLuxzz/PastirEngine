#include <components/dialogbox.hpp>
#include <sprite/sprite.hpp>

namespace dialogbox {
    Sprite view;
    bool showing = false;
    int currentDialog = 0;
    constexpr float scale = 3.0f/4.0f;
    dialog_t GAME_DIALOGS[NUM_GAME_DIALOGS];
} // namespace dialogbox


int dialogbox::init() {
    // load sprite (view)
    bank::TextureInfo dialogboxTexture = {
        .bankType = bank::TILESET,
        .bankID = bank::tileset::DIALOG_BOX,
        .tileID = 0
    };
    view.setTexture(dialogboxTexture);
    view.setScale(0.8f / scale, 0.5f / scale);
    view.setPosition(6.0f/scale, 0.0f);

    // init dialogs
    _loadDialogs(GAME_DIALOGS);
    return 0;
}

void dialogbox::show(bool t) {
    showing = t;
}
void dialogbox::hide() {
    showing = false;
}
bool dialogbox::isShowing() {
    return showing;
}

#include <allegro5/allegro_font.h>
#include <components/display.hpp>

#include <game.hpp>

void dialogbox::draw() {
    Display::useCustomScale(Display::getPixelScale() * scale);

    // view.setPosition(view.getPosition() + float2{0.0f, 0.1f});
    view.drawWhole();

    al_draw_multiline_textf(game::getGame()->font, al_map_rgb(255,255,255), view.getPosition().x+20.0f,view.getPosition().y+10.0f, 100.0f,20.0f, 0, "%s", GAME_DIALOGS[currentDialog].pages[0].c_str());

    Display::useScale();
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
