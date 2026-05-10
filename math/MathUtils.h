#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <cmath>
#include <algorithm>

const float PI = 3.14159265358979323846f;

struct Vec3 {
    float x, y, z;
};

inline float degToRad(float d) {
    return d * PI / 180.0f;
}

inline float clampValue(float v, float lo, float hi) {
    return std::max(lo, std::min(v, hi));
}

inline float distance2D(Vec3 a, Vec3 b) {
    float dx = a.x - b.x;
    float dz = a.z - b.z;
    return std::sqrt(dx * dx + dz * dz);
}

#endif // MATHUTILS_H
