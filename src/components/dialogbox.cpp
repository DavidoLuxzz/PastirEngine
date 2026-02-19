#include <components/dialogbox.hpp>
#include <sprite/sprite.hpp>

namespace dialogbox {
    Sprite view;
    bool showing = false;
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

void dialogbox::draw() {
    view.drawWhole();
}