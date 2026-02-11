#include <data_types.hpp>

float2 operator+(float2 a, float2 b) {
    return {a.x+b.x, a.y+b.y};
}
float2 operator-(float2 a, float2 b) {
    return {a.x-b.x, a.y-b.y};
}

template <typename T>
inline bool Rect<T>::contains(const vec2<T>& a) const {
    return (min.x<=a.x && min.y<=a.y) && (a.x<=(min.x+size.x) && a.y<=(min.y+size.y));
}
template <typename T>
inline bool Rect<T>::contains(T x, T y) const {
    return (min.x<=x && min.y<=y) && (x<=(min.x+size.x) && y<=(min.y+size.y));
}