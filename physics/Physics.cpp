#include "Physics.h"
#include "../globals/Globals.h"

// General-purpose sphere-vs-AABB collision check.
bool checkAABBCollision(Vec3 p, float radius, Vec3 boxCenter, float sx, float sy, float sz) {
    float closestX = clampValue(p.x, boxCenter.x - sx * 0.5f, boxCenter.x + sx * 0.5f);
    float closestY = clampValue(p.y + 0.8f, boxCenter.y - sy * 0.5f, boxCenter.y + sy * 0.5f);
    float closestZ = clampValue(p.z, boxCenter.z - sz * 0.5f, boxCenter.z + sz * 0.5f);

    float dx = p.x - closestX;
    float dy = (p.y + 0.8f) - closestY;
    float dz = p.z - closestZ;

    return (dx * dx + dy * dy + dz * dz) < radius * radius;
}
