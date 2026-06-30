#include <data_types.hpp>
#include <cmath>

float2 operator+(float2 a, float2 b) {
    return {a.x+b.x, a.y+b.y};
}
float2 operator-(float2 a, float2 b) {
    return {a.x-b.x, a.y-b.y};
}
float2 operator*(float2 a, float scale) {
    return {a.x*scale, a.y*scale};
}
float2 operator*(float2 a, float2 b) {
    return {a.x*b.x, a.y*b.y};
}
float2 operator/(float2 a, float scale) {
    return {a.x/scale, a.y/scale};
}
float2 operator/(float2 a, float2 b) {
    return {a.x/b.x, a.y/b.y};
}

float2 operator-(float2 a) {
    return {-a.x, -a.y};
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
float2& operator*=(float2& a, const float2& b) {
    a.x *= b.x;
    a.y *= b.y;
    return a;
}
float2& operator/=(float2& a, float scale) {
    a.x /= scale;
    a.y /= scale;
    return a;
}
float2& operator/=(float2& a, const float2& b) {
    a.x /= b.x;
    a.y /= b.y;
    return a;
}


float2 normalized(const float2 a) {
    float c = hypotf(a.x, a.y);
    if (c==0.0f) return a*0.0f;
    return a/c;
}
void normalize(float2& a) {
    float c = hypotf(a.x,a.y);
    if (c==0.0f) a *= 0.0f;
    else a /= hypotf(a.x,a.y);
}