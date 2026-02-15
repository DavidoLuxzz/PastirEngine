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

// defined in misc/
float2 operator+(float2 a, float2 b);
float2 operator-(float2 a, float2 b);
float2 operator*(float2 a, float scale);

template <typename T>
inline bool between(T x, T a1, T a2) {
    return (a1>=x && x>=a2) || (a2>=x && x>=a1);
}

template<typename T>
struct Rect {
    vec2<T> min;
    vec2<T> size;

    inline bool contains(const vec2<T>& a) const {
        return (min.x<=a.x && min.y<=a.y) && (a.x<=(min.x+size.x) && a.y<=(min.y+size.y));
    }
    inline bool contains(T x, T y) const {
        return (min.x<x && min.y<y) && (x<(min.x+size.x) && y<(min.y+size.y));
    }
    inline bool intersects(const Rect<T>& rect) const {
        bool onX=false, onY=false;
        // 1D (x)
        onX = (
            between(rect.min.x,  min.x, min.x+size.x) || 
            between(rect.min.x+rect.size.x,  min.x, min.x+size.x) ||
            between(min.x,  rect.min.x, rect.min.x+rect.size.x) || 
            between(min.x+size.x,  rect.min.x, rect.min.x+rect.size.x)
        );
        // 1D (y)
        onY = (
            between(rect.min.y,  min.y, min.y+size.y) || 
            between(rect.min.y+rect.size.y,  min.y, min.y+size.y) ||
            between(min.y,  rect.min.y, rect.min.y+rect.size.y) || 
            between(min.y+size.y,  rect.min.y, rect.min.y+rect.size.y)
        );
        return onX && onY;
    }
};
typedef Rect<float> Rectf;
typedef Rect<int> Recti;
typedef Rect<unsigned int> Rectu;




#endif