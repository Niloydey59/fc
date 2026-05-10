#ifndef PHYSICS_H
#define PHYSICS_H

#include "../math/MathUtils.h"

// General-purpose AABB collision check — reusable for any entity.
bool checkAABBCollision(Vec3 p, float radius, Vec3 boxCenter, float sx, float sy, float sz);

#endif // PHYSICS_H
