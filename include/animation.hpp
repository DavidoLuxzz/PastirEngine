#pragma once
#ifndef __ANIMATION_HPP
#define __ANIMATION_HPP

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

    /**
     * If enough time is passed, it calls tick()
     */
    void update();
    /// @brief Calls tick function
    void tick();

    int frame, cycleCount;
    double rate;
};


#endif