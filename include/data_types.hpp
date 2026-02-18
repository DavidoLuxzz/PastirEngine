#pragma once
#ifndef __DATA_TYPES_HPP
#define __DATA_TYPES_HPP

struct float2 {
    float x,y;
};
struct uint2 {
    unsigned int x,y;
};

struct float3 {
    float x,y,z;
};

// defined in misc/
float2 operator+(float2 a, float2 b);
float2 operator-(float2 a, float2 b);
float2 operator*(float2 a, float scale);
float2& operator+=(float2& a, float2 b);
float2& operator-=(float2& a, float2 b);
float2& operator*=(float2& a, float scale);

#define between(x, a1,a2) ((a1)>=(x) && (x)>=(a2)) || ((a2)>=(x) && (x)>=(a1))

struct Rectf {
    union {
        float2 min;
        uint2 umin;
    };
    union {
        float2 size;
        uint2 usize;
    };

    inline bool contains(const float2& a) const {
        return (min.x<=a.x && min.y<=a.y) && (a.x<=(min.x+size.x) && a.y<=(min.y+size.y));
    }
    inline bool contains(float x, float y) const {
        return (min.x<x && min.y<y) && (x<(min.x+size.x) && y<(min.y+size.y));
    }
    inline bool intersects(const Rectf& rect) const {
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

struct Rectu {
    uint2 min;
    uint2 size;
};


#endif