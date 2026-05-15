#ifndef BALL_H
#define BALL_H

#include "../math/MathUtils.h"

struct Ball {
    Vec3  pos;
    Vec3  vel;
    float radius;
    bool  attached;   // true = stuck to front of player
};

extern Ball ball;

void initBall();
void updateBall(float dt);
void drawBall();

#endif // BALL_H
