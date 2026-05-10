#include "Player.h"
#include "../globals/Globals.h"
#include "../stadium/Stadium.h"
#include "../renderer/DrawUtils.h"
#include <GL/freeglut.h>
#include <cmath>

// ── Movement & Physics ───────────────────────────────────────
void updatePlayer(float dt) {
    if (gameWon || gameOver || paused) return;

    const float turnSpeed = 120.0f;
    const float moveSpeed = 9.0f;

    if (specialKeys[GLUT_KEY_LEFT])  playerYaw += turnSpeed * dt;
    if (specialKeys[GLUT_KEY_RIGHT]) playerYaw -= turnSpeed * dt;

    float yaw = degToRad(playerYaw);
    Vec3 forward = { std::sin(yaw), 0.0f, -std::cos(yaw) };
    Vec3 right   = { std::cos(yaw), 0.0f,  std::sin(yaw) };

    float moveX = 0.0f, moveZ = 0.0f;
    if (keys['w'] || keys['W']) { moveX += forward.x; moveZ += forward.z; }
    if (keys['s'] || keys['S']) { moveX -= forward.x; moveZ -= forward.z; }
    if (keys['d'] || keys['D']) { moveX += right.x;   moveZ += right.z;   }
    if (keys['a'] || keys['A']) { moveX -= right.x;   moveZ -= right.z;   }

    float len = std::sqrt(moveX * moveX + moveZ * moveZ);
    if (len > 0.0f) {
        playerPos.x += (moveX / len) * moveSpeed * dt;
        playerPos.z += (moveZ / len) * moveSpeed * dt;
    }

    // Keep inside field
    playerPos.x = clampValue(playerPos.x, -FIELD_HALF_WIDTH  + 1.2f, FIELD_HALF_WIDTH  - 1.2f);
    playerPos.z = clampValue(playerPos.z, -FIELD_HALF_LENGTH + 1.2f, FIELD_HALF_LENGTH - 1.2f);

    // Jump
    if (keys[' '] && !isJumping) { isJumping = true; jumpVelocity = 8.0f; }
    if (isJumping) {
        playerPos.y += jumpVelocity * dt;
        jumpVelocity -= 18.0f * dt;
        if (playerPos.y <= 0.0f) { playerPos.y = 0.0f; isJumping = false; jumpVelocity = 0.0f; }
    }
}

// ── Rendering ────────────────────────────────────────────────
void drawPlayer() {
    glPushMatrix();
    glTranslatef(playerPos.x, playerPos.y, playerPos.z);
    glRotatef(playerYaw, 0, 1, 0);

    // Body
    setMaterial(0.08f, 0.42f, 1.0f, 75.0f);
    glPushMatrix(); glTranslatef(0, 0.95f, 0); drawCubeScaled(1.1f, 1.4f, 0.75f); glPopMatrix();

    // Head
    setMaterial(0.95f, 0.95f, 1.0f, 90.0f);
    glPushMatrix(); glTranslatef(0, 1.85f, 0); glutSolidSphere(0.42, 24, 24); glPopMatrix();

    // Arms
    setMaterial(0.06f, 0.10f, 0.16f, 35.0f);
    glPushMatrix(); glTranslatef(-0.72f, 0.95f, 0); drawCubeScaled(0.25f, 1.0f, 0.25f); glPopMatrix();
    glPushMatrix(); glTranslatef( 0.72f, 0.95f, 0); drawCubeScaled(0.25f, 1.0f, 0.25f); glPopMatrix();

    // Legs
    glPushMatrix(); glTranslatef(-0.3f, 0.18f, 0); drawCubeScaled(0.28f, 0.55f, 0.28f); glPopMatrix();
    glPushMatrix(); glTranslatef( 0.3f, 0.18f, 0); drawCubeScaled(0.28f, 0.55f, 0.28f); glPopMatrix();

    // Eyes
    glDisable(GL_LIGHTING);
    glColor3f(0.1f, 0.9f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.16f, 1.92f, -0.35f);
    glutSolidSphere(0.05, 10, 10);
    glTranslatef(0.32f, 0.0f, 0.0f);
    glutSolidSphere(0.05, 10, 10);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    glPopMatrix();
}
