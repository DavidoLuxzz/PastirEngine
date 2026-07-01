#pragma once
#ifndef __static_entity_hpp
#define __static_entity_hpp

#include <sprite/sprite.hpp>
#include <level/Triggers.hpp>
#include <array>

class StaticEntity : public Sprite {
public:
    enum data_components {
        COMP_X,
        COMP_Y,
        COMP_ROOM,
        COMP_TEXTURE,
        COMP_TRIGGER_ID,
        COMP_SCALEX,
        COMP_SCALEY,
        // unused (neka dzedze ovde, dobice neki znacaj nekad)
        COMP_SPEC3,

        COMPONENT_COUNT
    };

    typedef std::array<int, COMPONENT_COUNT> EntityData;
    #define DEFAULT_ENTITY_DATA {0,0,0,0,0,0,0,0}

    StaticEntity();
    StaticEntity(const EntityData&);
    Trigger::TriggerData data;



    Rectf getHitbox() const;
    
    // static components
    static void drawData(const EntityData& data, float2 translate={0.0f, 0.0f});

    static Rectf createHitbox(const EntityData& data, float2 translate={0.f, 0.f});
};


#endif