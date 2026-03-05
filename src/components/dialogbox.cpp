#include <components/dialogbox.hpp>
#include <sprite/sprite.hpp>

namespace dialogbox {
    Sprite view;
    bool showing = false;
    dialog_t dialog(MAX_DIALOG_PAGES);
} // namespace dialogbox


int dialogbox::init() {
    bank::TextureInfo dialogboxTexture = {
        .bankType = bank::TILESET,
        .bankID = bank::tileset::DIALOG_BOX,
        .tileID = 0
    };
    view.setTexture(dialogboxTexture);
    view.setScale(0.8f, 0.5f);
    view.setPosition(6.0f, 0.0f);

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

extern ALLEGRO_FONT* font;

void dialogbox::draw() {
    view.drawWhole();
    Display::useCustomScale(3.0f,3.0f);
    al_draw_multiline_textf(font, al_map_rgb(255,255,255), 20.0f,8.0f, 100.0f,20.0f, 0, "%s", dialog.pages[0].c_str());
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
