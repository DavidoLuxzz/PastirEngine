#include <shake.hpp>
#include <components/display.hpp>
#include <animation.hpp>

namespace shake {

    float strength, freq;

    Animation anim;
    
} // namespace shake


void shake::set(float strngth, float hz) {
    strength = strngth;
    anim.init(1000./hz);
}

int ___x=0;

void shake::update(double ms) {
    if (!anim.update(ms)) return;

    ___x++;

    if (___x&1) {
        Display::useTranslate(0.f,0.f);
        return;
    }

    // Display::useTranslate(100.f * (anim.frame%2), 100.f * (anim.frame%3));
    Display::useTranslate((___x%4==0)? -10.f:10.f,(___x%4!=0)? -10.f:10.f);
}