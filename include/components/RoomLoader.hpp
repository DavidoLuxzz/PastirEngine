#pragma once
#ifndef __ROOM_LOADER_HPP
#define __ROOM_LOADER_HPP

#include <components/Room.hpp>

namespace room_loader {
    /**
     * Loads room into memory.
     * Room is accessible via room_loader::getRoom();
     * 
     * @param roomID Room ID
     * 
     * @return 0 if success
     */
    int load(unsigned int roomID);

    /**
     * Swaps the objects vector between the data stored
     * in room_loader's memory and specified room
     * 
     * @param room - specified room object
     */
    void swapData(Room& room);
    

} // namespace room_loader



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
#define TRIGGER_DEFAULT_DATA {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    TriggerData data;

    Trigger() = default;
    Trigger(TriggerData& data);
};


namespace trigger_loader {
    std::vector<Trigger::TriggerData> loadAll();
} // namespace trigger_loader



#endif