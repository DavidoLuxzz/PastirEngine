#pragma once
#ifndef __SHAKE_HPP
#define __SHAKE_HPP

namespace shake {
    
    /**
     * @param strength - shake strength (max offset by axis)
     * @param freq - shake frequency in Hz
     * @param duration - shake duration in seconds
     */
    void set(float strength, float freq, float duration=-1.f);
    void update(double ms);

} // namespace shake


#endif