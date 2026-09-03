#pragma once
#ifndef __ANIMATION_HPP
#define __ANIMATION_HPP

#include <functional>

typedef void (*AnimationTickFunc)(int frame);

class Animation {
private:
    AnimationTickFunc tickFunc = nullptr;
    double _lastTime = 0.0;
public:
    Animation() = default;
    ~Animation() = default;

    /// @brief Initialize
    /// @param rate Animation tick rate in seconds
    /// @param cycleCount Cycle count. INF = -1
    void init(double rate, int cycleCount=-1);

    void setTickFunction(AnimationTickFunc func);
    AnimationTickFunc getTickFunction() const;

    bool isFinished() const;

    /**
     * If enough time is passed, it calls tick()
     * @return Returns true if enough time is passed.
     */
    bool update();
    /// @brief Calls tick function
    void tick();

    int frame, cycleCount;
    double rate;
};


#endif