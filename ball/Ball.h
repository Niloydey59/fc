#ifndef BALL_H
#define BALL_H

#include "../math/MathUtils.h"

struct Ball {
    Vec3  pos;
    float radius;
    bool  attached;   // true = stuck to front of player
};

extern Ball ball;

void initBall();
void updateBall();
void drawBall();

#endif // BALL_H
