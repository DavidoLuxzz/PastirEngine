#include <components/dialogbox.hpp>

#define REGISTER_DIALOG(i,msg) out_dialogs[i].alloc(1)[0] = msg

void dialogbox::_loadDialogs(dialog_t* out_dialogs) {
    // for (int i=0; i<NUM_GAME_DIALOGS; i++) {
    REGISTER_DIALOG(0, "U redu je, znam da sam tata u ovome.\n\nbtw testing");
    REGISTER_DIALOG(1, "Usamnjeni znak nekadasnjeg zivota.\n\nZasto ne bi pustio malo muzike?");
    // }
}