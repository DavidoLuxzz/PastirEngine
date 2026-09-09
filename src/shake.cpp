#include <shake.hpp>
#include <components/display.hpp>
#include <animation.hpp>
#include <random>

namespace shake {

    float strength, freq;

    Animation anim;

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution{-1.0f, 1.0f};
    
} // namespace shake


void shake::set(float strngth, float hz, float duration) {
    strength = strngth;
    anim.init(1000./hz, static_cast<int>(hz*duration));
}

void shake::update(double ms) {
    if (!anim.update(ms)) return;
    if (anim.isFinished()) {
        Display::useTranslate(0.f,0.f);
        return;
    }

    float offx = distribution(generator) * strength;
    float offy = distribution(generator) * strength;

    Display::useTranslate(offx, offy);
}