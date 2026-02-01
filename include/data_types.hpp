#pragma once
#ifndef __DATA_TYPES_HPP
#define __DATA_TYPES_HPP

template<typename T>
struct vec2 {
    T x,y;
};
typedef vec2<float> float2;

// for some reason defined in sprite.cpp
float2 operator+(float2 a, float2 b);


#endif