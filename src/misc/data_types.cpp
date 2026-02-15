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