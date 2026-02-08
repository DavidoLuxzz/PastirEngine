#pragma once
#ifndef __DATA_TYPES_HPP
#define __DATA_TYPES_HPP

template<typename T>
struct vec2 {
    T x,y;
};
typedef vec2<float> float2;
typedef vec2<int> int2;
typedef vec2<unsigned int> uint2;

template<typename T>
struct vec3 {
    T x,y,z;
};
typedef vec3<float> float3;
typedef vec3<int> int3;
typedef vec3<unsigned int> uint3;

// for some reason defined in sprite.cpp
float2 operator+(float2 a, float2 b);


template<typename T>
struct Rect {
    vec2<T> min;
    vec2<T> size;
    // for some reason defined in RoomLoader.cpp
    T& operator[](int index);
};
typedef Rect<float> Rectf;
typedef Rect<int> Recti;
typedef Rect<unsigned int> Rectu;


#endif