#pragma once
#ifndef __ANIMATION_HPP
#define __ANIMATION_HPP

#include <functional>

typedef void (*AnimationTickFunc)(int frame);

class Animation {
private:
    AnimationTickFunc tickFunc = nullptr;
    double _time = 0.0; // time since last tick
public:
    Animation() = default;
    ~Animation() = default;

    /// @brief Initialize
    /// @param rate_ms Animation tick rate in milliseconds
    /// @param cycleCount Cycle count. INF = -1
    void init(double rate_ms, int cycleCount=-1);

    void setTickFunction(AnimationTickFunc func);
    AnimationTickFunc getTickFunction() const;

    bool isFinished() const;

    /**
     * If enough time is passed, it calls tick()
     * @return Returns true if enough time is passed.
     */
    bool update(double ms);
    /// @brief Calls tick function
    void tick();

    int frame=0, cycleCount=-1;
    double rate=0.0;
};


#endif