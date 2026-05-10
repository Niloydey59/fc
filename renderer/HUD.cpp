#include "HUD.h"
#include "DrawUtils.h"
#include "../globals/Globals.h"
#include <GL/freeglut.h>
#include <sstream>
#include <iomanip>

void drawHUD() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, winW, 0, winH);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0f, 1.0f, 1.0f);

    std::ostringstream timer;
    timer << std::fixed << std::setprecision(1) << gameTime;

    std::string camName = "Third Person";
    if (cameraMode == 1) camName = "Top View";
    if (cameraMode == 2) camName = "First Person";

    drawBitmapText2D(18, winH - 25, "Football Game - OpenGL FreeGLUT");
    drawBitmapText2D(18, winH - 45,
        "Lives: " + std::to_string(lives) +
        "    Time: " + timer.str() +
        "    Camera: " + camName);
    drawBitmapText2D(18, 68, "W/S: forward/back    A/D: strafe    Arrows: turn");
    drawBitmapText2D(18, 48, "Space: jump    C: camera    P: pause    R: restart    Esc: exit");
    drawBitmapText2D(18, 28, "Mouse Left: rotate camera    Mouse Right/Wheel: zoom");

    if (paused && !gameWon && !gameOver) {
        glColor3f(1.0f, 0.9f, 0.25f);
        drawBitmapText2D(winW / 2 - 55, winH / 2, "PAUSED");
    }
    if (gameWon) {
        glColor3f(0.1f, 1.0f, 0.45f);
        drawBitmapText2D(winW / 2 - 90, winH / 2 + 15, "LEVEL COMPLETE");
        drawBitmapText2D(winW / 2 - 135, winH / 2 - 10, "Press R to play again.");
    }
    if (gameOver) {
        glColor3f(1.0f, 0.2f, 0.2f);
        drawBitmapText2D(winW / 2 - 60, winH / 2 + 15, "GAME OVER");
        drawBitmapText2D(winW / 2 - 135, winH / 2 - 10, "Press R to restart.");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
