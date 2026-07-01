#pragma once
#ifndef __EVENT_HPP
#define __EVENT_HPP

namespace event {
    /** Trigger events */
    enum {
        NONE, // 0
        CHANGE_ROOM, // 1
        DIALOG_INTERRUPT, // 2
        TEXTURE_CHANGE, // 3 (todo rename u PROPERTY_CHANGE)
        DIALOG_INTERRUPT_THEN_DISAPPEAR, // 4
        GIVE_ITEM, // 5
        GIVE_ITEM_THEN_DISAPPEAR // 6
    };
} // namespace event




#endif