#include <data_types.hpp>

float2 operator+(float2 a, float2 b) {
    return {a.x+b.x, a.y+b.y};
}
float2 operator-(float2 a, float2 b) {
    return {a.x-b.x, a.y-b.y};
}
float2 operator*(float2 a, float scale) {
    return {a.x*scale, a.y*scale};
}

float2& operator+=(float2& a, float2 b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}
float2& operator-=(float2& a, float2 b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}
float2& operator*=(float2& a, float scale) {
    a.x *= scale;
    a.y *= scale;
    return a;
}

