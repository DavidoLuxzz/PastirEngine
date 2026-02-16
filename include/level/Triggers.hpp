#pragma once
#ifndef __TRIGGERS_HPP
#define __TRIGGERS_HPP

#include <vector>

#include <array>

/**
 * Trigger class
 */
class Trigger {
public:
    // room  action  needsZ  specialValue  rmAfInt  x  y  width  height  (special2)  (special3
    enum data_components {
        COMP_ROOM,
        COMP_ACTION,
        COMP_NEEDS_Z,
        COMP_SPECIAL_VALUE,
        COMP_RMAFINT,
        COMP_X,
        COMP_Y,
        COMP_WIDTH,
        COMP_HEIGHT,
        COMP_SPECIAL2,
        COMP_SPECIAL3,

        COMPONENT_COUNT
    };

    typedef std::array<int, data_components::COMPONENT_COUNT> TriggerData;
#define TRIGGER_DEFAULT_DATA {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    TriggerData data;

    Trigger() = default;
    Trigger(TriggerData& data);
};

// typedef std::vector<Trigger::TriggerData> TriggerRooms;

namespace triggers {
    /**
     * Loads all triggers.
     * @return error code
     */
    int load();
    /**
     * Get certain trigger from room
     * @returns Trigger Data
     */
    const Trigger::TriggerData& get(unsigned int trID);
    /**
     * Creates a list with pointers to all the triggers from room.
     */
    void prepare(unsigned int room);

    unsigned int getThisRoomTriggerCount();
} // namespace triggers


#endif