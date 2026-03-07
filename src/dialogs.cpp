#include <components/dialogbox.hpp>

void dialogbox::_loadDialogs(dialog_t* out_dialogs) {
    for (int i=0; i<NUM_GAME_DIALOGS; i++) {
        out_dialogs[i].alloc(1)[0] = "Hellow!!";
    }
}