#include "GameManager.h"
#include "../globals/Globals.h"
#include "../player/Player.h"
#include "../ball/Ball.h"
#include <GL/freeglut.h>

void initLevel() {
    // Populate level entities here (ball, AI players, etc.)
}

void resetGame() {
    playerPos = playerStartPos;
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

    initBall();
    initLevel();
}

void respawnPlayer() {
    playerPos = playerStartPos;
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
    updateBall();

    if (specialKeys[GLUT_KEY_UP]) {
        cameraPitch += 45.0f * dt;
    }

    if (specialKeys[GLUT_KEY_DOWN]) {
        cameraPitch -= 45.0f * dt;
    }

    cameraPitch = clampValue(cameraPitch, -5.0f, 70.0f);
}
