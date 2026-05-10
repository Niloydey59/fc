#include "Ball.h"
#include "../globals/Globals.h"
#include <GL/freeglut.h>
#include <cmath>

Ball ball;

void initBall() {
    ball.pos      = {0.0f, 0.0f, 0.0f};  // center of field
    ball.radius   = 0.4f;
    ball.attached = false;
}

void updateBall() {
    if (ball.attached) {
        // Keep ball just in front of the player on the ground
        float yaw  = degToRad(playerYaw);
        float fwdX = std::sin(yaw);
        float fwdZ = -std::cos(yaw);
        float offset = playerRadius + ball.radius + 0.05f;

        ball.pos.x = playerPos.x + fwdX * offset;
        ball.pos.y = ball.radius;   // resting on ground
        ball.pos.z = playerPos.z + fwdZ * offset;

    } else {
        // Check if player has walked into the ball
        float dx   = playerPos.x - ball.pos.x;
        float dz   = playerPos.z - ball.pos.z;
        float dist = std::sqrt(dx * dx + dz * dz);

        if (dist < playerRadius + ball.radius) {
            ball.attached = true;
        }
    }
}

void drawBall() {
    glPushMatrix();
    glTranslatef(ball.pos.x, ball.pos.y, ball.pos.z);

    // White base
    GLfloat diff[]  = {0.92f, 0.92f, 0.92f, 1.0f};
    GLfloat spec[]  = {0.7f,  0.7f,  0.7f,  1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 80.0f);
    glutSolidSphere(ball.radius, 24, 24);

    glPopMatrix();
}
