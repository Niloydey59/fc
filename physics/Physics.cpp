#include "Physics.h"
#include "../globals/Globals.h"
#include "../game_manager/GameManager.h"
#include "../stadium/Stadium.h"
#include <GL/freeglut.h>
#include <cmath>


bool checkAABBCollision(Vec3 p, float radius, Vec3 boxCenter, float sx, float sy, float sz) {
    float closestX = clampValue(p.x, boxCenter.x - sx * 0.5f, boxCenter.x + sx * 0.5f);
    float closestY = clampValue(p.y + 0.8f, boxCenter.y - sy * 0.5f, boxCenter.y + sy * 0.5f);
    float closestZ = clampValue(p.z, boxCenter.z - sz * 0.5f, boxCenter.z + sz * 0.5f);

    float dx = p.x - closestX;
    float dy = (p.y + 0.8f) - closestY;
    float dz = p.z - closestZ;

    return (dx * dx + dy * dy + dz * dz) < radius * radius;
}

void updatePlayer(float dt) {
    if (gameWon || gameOver || paused) return;

    float turnSpeed = 120.0f;
    float moveSpeed = 9.0f;

    // Turn the character using left/right arrow keys
    if (specialKeys[GLUT_KEY_LEFT]) {
        playerYaw += turnSpeed * dt;
    }

    if (specialKeys[GLUT_KEY_RIGHT]) {
        playerYaw -= turnSpeed * dt;
    }

    // Convert current character direction to radians
    float yaw = degToRad(playerYaw);

    // Forward direction based on current facing direction
    Vec3 forward = {
        std::sin(yaw),
        0.0f,
        -std::cos(yaw)
    };

    // Right direction based on current facing direction
    Vec3 right = {
        std::cos(yaw),
        0.0f,
        std::sin(yaw)
    };

    float moveX = 0.0f;
    float moveZ = 0.0f;

    // W/S movement: forward/backward according to current facing direction
    if (keys['w'] || keys['W']) {
        moveX += forward.x;
        moveZ += forward.z;
    }

    if (keys['s'] || keys['S']) {
        moveX -= forward.x;
        moveZ -= forward.z;
    }

    // A/D movement: left/right relative to current facing direction
    if (keys['d'] || keys['D']) {
        moveX += right.x;
        moveZ += right.z;
    }

    if (keys['a'] || keys['A']) {
        moveX -= right.x;
        moveZ -= right.z;
    }

    // Normalize diagonal movement so diagonal speed is not faster
    float length = std::sqrt(moveX * moveX + moveZ * moveZ);

    if (length > 0.0f) {
        moveX /= length;
        moveZ /= length;

        playerPos.x += moveX * moveSpeed * dt;
        playerPos.z += moveZ * moveSpeed * dt;
    }

    // Keep player inside field
    playerPos.x = clampValue(playerPos.x, -FIELD_HALF_WIDTH  + 1.2f, FIELD_HALF_WIDTH  - 1.2f);
    playerPos.z = clampValue(playerPos.z, -FIELD_HALF_LENGTH + 1.2f, FIELD_HALF_LENGTH - 1.2f);

    // Jump
    if (keys[' '] && !isJumping) {
        isJumping = true;
        jumpVelocity = 8.0f;
    }

    if (isJumping) {
        playerPos.y += jumpVelocity * dt;
        jumpVelocity -= 18.0f * dt;

        if (playerPos.y <= 0.0f) {
            playerPos.y = 0.0f;
            isJumping = false;
            jumpVelocity = 0.0f;
        }
    }
}
