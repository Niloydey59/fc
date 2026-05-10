#ifndef PHYSICS_H
#define PHYSICS_H

#include "../math/MathUtils.h"

bool checkAABBCollision(Vec3 p, float radius, Vec3 boxCenter, float sx, float sy, float sz);

void updatePlayer(float dt);

#endif // PHYSICS_H
