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

void Animation::tick() {
    if (cycleCount>0 && frame>cycleCount) return;
    if (tickFunc) tickFunc(frame);
    frame++;
}

#include <allegro5/timer.h>
void Animation::update() {
    if (cycleCount>0 && frame>cycleCount) return;
    double time = al_get_time();
    if ((time-_lastTime)>=rate) {
        _lastTime = time;
        tick();
    }
}