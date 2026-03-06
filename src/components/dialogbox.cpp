#include <components/dialogbox.hpp>
#include <sprite/sprite.hpp>

namespace dialogbox {
    Sprite view;
    bool showing = false;
    dialog_t dialog(MAX_DIALOG_PAGES);
    constexpr float scale = 3.0f/4.0f;
} // namespace dialogbox


int dialogbox::init() {
    bank::TextureInfo dialogboxTexture = {
        .bankType = bank::TILESET,
        .bankID = bank::tileset::DIALOG_BOX,
        .tileID = 0
    };
    view.setTexture(dialogboxTexture);
    view.setScale(0.8f / scale, 0.5f / scale);
    view.setPosition(6.0f/scale, 0.0f);

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

    al_draw_multiline_textf(game::getGame()->font, al_map_rgb(255,255,255), view.getPosition().x+20.0f,view.getPosition().y+10.0f, 100.0f,20.0f, 0, "%s", dialog.pages[0].c_str());

    Display::useScale();
}



void dialogbox::setDialog(const dialog_t& d) {
    for (int i=0; i<d.numPages; i++) {
        dialog.pages[i] = d.pages[i];
    }
    dialog.numPages = d.numPages;
}
void dialogbox::setText(const std::string s) {    
    dialog.pages[0] = s;
    dialog.numPages = 1;
}
