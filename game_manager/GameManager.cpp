#include "GameManager.h"
#include "../globals/Globals.h"
#include "../physics/Physics.h"
#include <GL/freeglut.h>

void initLevel() {
    trees.clear();

    for (int i = 0; i < 34; i++) {
        float x = (i % 2 == 0) ? -38.0f : 38.0f;
        float z = -30.0f + i * 2.0f;
        trees.push_back({{x, 0.0f, z}, 0.9f + (i % 4) * 0.15f});
    }

    for (int i = 0; i < 22; i++) {
        float z = (i % 2 == 0) ? -38.0f : 38.0f;
        float x = -28.0f + i * 2.8f;
        trees.push_back({{x, 0.0f, z}, 0.8f + (i % 3) * 0.2f});
    }
}

void resetGame() {
    playerPos = {0.0f, 0.0f, 0.0f};
    playerYaw = 0.0f;

    isJumping = false;
    jumpVelocity = 0.0f;

    lives = 3;
    gameTime = 0.0f;
    globalTime = 0.0f;

    paused = false;
    gameWon = false;
    gameOver = false;

    cameraMode = 0;
    cameraYawOffset = 0.0f;
    cameraPitch = 22.0f;
    cameraDistance = 15.0f;

    initLevel();
}

void respawnPlayer() {
    playerPos = {0.0f, 0.0f, 0.0f};
    isJumping = false;
    jumpVelocity = 0.0f;
}

void updateGame(float dt) {
    if (!paused && !gameWon && !gameOver) {
        gameTime += dt;
        globalTime += dt;
    } else {
        globalTime += dt * 0.35f;
    }

    updatePlayer(dt);

    if (specialKeys[GLUT_KEY_UP]) {
        cameraPitch += 45.0f * dt;
    }

    if (specialKeys[GLUT_KEY_DOWN]) {
        cameraPitch -= 45.0f * dt;
    }

    cameraPitch = clampValue(cameraPitch, -5.0f, 70.0f);
}
