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

    // Draw dark semi-transparent background bars for readability
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, 0.55f);

    // Top bar
    glBegin(GL_QUADS);
        glVertex2f(0, winH);
        glVertex2f(winW, winH);
        glVertex2f(winW, winH - 60);
        glVertex2f(0, winH - 60);
    glEnd();


    glColor4f(0.0f, 0.0f, 0.0f, 0.55f);
    // Bottom bar
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(winW, 0);
        glVertex2f(winW, 95);
        glVertex2f(0, 95);
    glEnd();
    glDisable(GL_BLEND);

    glColor3f(1.0f, 1.0f, 1.0f);

    std::ostringstream timer;
    timer << std::fixed << std::setprecision(1) << gameTime;

    std::string camName = "Third Person";
    if (cameraMode == 1) camName = "Top View";
    if (cameraMode == 2) camName = "First Person";

    drawBitmapText2D(18, winH - 25, "Football Game - OpenGL FreeGLUT");
    drawBitmapText2D(18, winH - 45,
        "Time: " + timer.str() +
        "    Camera: " + camName);

    // Scoreboard at top center (larger font)
    std::string scoreStr = std::to_string(homeScore) + " - " + std::to_string(awayScore);
    drawBitmapText2D(winW / 2 - 30, winH - 35, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);
    
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
