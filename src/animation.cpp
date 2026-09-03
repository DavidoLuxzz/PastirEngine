#include <animation.hpp>

void Animation::init(double _rate, int _cycleCount) {
    rate = _rate;
    cycleCount = _cycleCount;
}

void Animation::setTickFunction(AnimationTickFunc f) {
    tickFunc = f;
}
AnimationTickFunc Animation::getTickFunction() const {
    return tickFunc;
}

bool Animation::isFinished() const { return (cycleCount>0 && frame>cycleCount); }

void Animation::tick() {
    if (isFinished()) return;
    if (tickFunc) tickFunc(frame);
    frame++;
}

#include <allegro5/timer.h>
bool Animation::update() {
    if (cycleCount>0 && frame>cycleCount) return false;
    double time = al_get_time();
    if ((time-_lastTime)>=rate) {
        _lastTime = time;
        tick();
        return true;
    }
    return false;
}