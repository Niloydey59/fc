#include "Input.h"
#include "../globals/Globals.h"
#include "../game_manager/GameManager.h"
#include <GL/freeglut.h>
#include <cstdlib>

void keyboardDown(unsigned char key, int x, int y) {
    keys[key] = true;

    switch (key) {
        case 27:
            exit(0);
            break;

        case 'p':
        case 'P':
            if (!gameWon && !gameOver) {
                paused = !paused;
            }
            break;

        case 'c':
        case 'C':
            cameraMode = (cameraMode + 1) % 3;
            break;

        case 'r':
        case 'R':
            resetGame();
            break;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

void specialDown(int key, int x, int y) {
    specialKeys[key] = true;
}

void specialUp(int key, int x, int y) {
    specialKeys[key] = false;
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        leftMouseDown = (state == GLUT_DOWN);
    }

    if (button == GLUT_RIGHT_BUTTON) {
        rightMouseDown = (state == GLUT_DOWN);
    }

    if (button == 3 && state == GLUT_DOWN) {
        cameraDistance -= 1.0f;
        cameraDistance = clampValue(cameraDistance, 6.0f, 35.0f);
    }

    if (button == 4 && state == GLUT_DOWN) {
        cameraDistance += 1.0f;
        cameraDistance = clampValue(cameraDistance, 6.0f, 35.0f);
    }

    lastMouseX = x;
    lastMouseY = y;
}

void mouseMotion(int x, int y) {
    int dx = x - lastMouseX;
    int dy = y - lastMouseY;

    if (leftMouseDown) {
        cameraYawOffset += dx * 0.35f;
        cameraPitch += dy * 0.25f;
        cameraPitch = clampValue(cameraPitch, -5.0f, 70.0f);
    }

    if (rightMouseDown) {
        cameraDistance += dy * 0.05f;
        cameraDistance = clampValue(cameraDistance, 6.0f, 35.0f);
    }

    lastMouseX = x;
    lastMouseY = y;
}
