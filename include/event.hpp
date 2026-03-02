#pragma once
#ifndef __EVENT_HPP
#define __EVENT_HPP

namespace event {
    enum {
        NONE,
        CHANGE_ROOM,
        DIALOG_INTERRUPT,
        TEXTURE_CHANGE,
        DIALOG_INTERRUPT_THEN_SUDDEN_DISAPPEAR,
        GIVE_ITEM,
        GIVE_ITEM_THEN_DISAPPEAR
    };
} // namespace event




#endif