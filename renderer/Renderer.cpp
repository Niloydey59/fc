#include "Renderer.h"
#include "../globals/Globals.h"
#include "../stadium/Stadium.h"
#include <GL/freeglut.h>
#include <cmath>
#include <sstream>
#include <iomanip>

void drawBitmapText2D(float x, float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}

void drawBitmapText3D(const std::string& text, float x, float y, float z) {
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(x, y, z);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    glEnable(GL_LIGHTING);
}

void drawCubeScaled(float sx, float sy, float sz) {
    glPushMatrix();
    glScalef(sx, sy, sz);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawCylinder(float radius, float height, int slices) {
    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);
    gluCylinder(q, radius, radius, height, slices, 1);
    gluDeleteQuadric(q);
}

void setMaterial(float r, float g, float b, float shininess) {
    GLfloat diffuse[] = {r, g, b, 1.0f};
    GLfloat specular[] = {0.45f, 0.45f, 0.45f, 1.0f};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void drawFloor() {
    setMaterial(0.10f, 0.13f, 0.16f, 20.0f);

    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(-arenaHalfSize, 0, -arenaHalfSize);
        glVertex3f( arenaHalfSize, 0, -arenaHalfSize);
        glVertex3f( arenaHalfSize, 0,  arenaHalfSize);
        glVertex3f(-arenaHalfSize, 0,  arenaHalfSize);
    glEnd();

    glDisable(GL_LIGHTING);
    glColor4f(0.2f, 0.55f, 0.95f, 0.35f);

    glBegin(GL_LINES);
    for (int i = -32; i <= 32; i += 4) {
        glVertex3f((float)i, 0.025f, -arenaHalfSize);
        glVertex3f((float)i, 0.025f,  arenaHalfSize);

        glVertex3f(-arenaHalfSize, 0.025f, (float)i);
        glVertex3f( arenaHalfSize, 0.025f, (float)i);
    }
    glEnd();

    glEnable(GL_LIGHTING);
}

void drawWalls() {
    setMaterial(0.16f, 0.19f, 0.24f, 25.0f);

    float h = 3.2f;
    float t = 0.8f;
    float s = arenaHalfSize;

    glPushMatrix();
    glTranslatef(0, h * 0.5f, -s);
    drawCubeScaled(s * 2.0f + t, h, t);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, h * 0.5f, s);
    drawCubeScaled(s * 2.0f + t, h, t);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-s, h * 0.5f, 0);
    drawCubeScaled(t, h, s * 2.0f + t);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(s, h * 0.5f, 0);
    drawCubeScaled(t, h, s * 2.0f + t);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glColor4f(0.25f, 0.75f, 1.0f, 0.65f);

    glBegin(GL_LINE_LOOP);
        glVertex3f(-s, h + 0.05f, -s);
        glVertex3f( s, h + 0.05f, -s);
        glVertex3f( s, h + 0.05f,  s);
        glVertex3f(-s, h + 0.05f,  s);
    glEnd();

    glEnable(GL_LIGHTING);
}


void drawPlayer() {
    glPushMatrix();

    glTranslatef(playerPos.x, playerPos.y, playerPos.z);
    glRotatef(playerYaw, 0, 1, 0);

    setMaterial(0.08f, 0.42f, 1.0f, 75.0f);

    glPushMatrix();
    glTranslatef(0, 0.95f, 0);
    drawCubeScaled(1.1f, 1.4f, 0.75f);
    glPopMatrix();

    setMaterial(0.95f, 0.95f, 1.0f, 90.0f);

    glPushMatrix();
    glTranslatef(0, 1.85f, 0);
    glutSolidSphere(0.42, 24, 24);
    glPopMatrix();

    setMaterial(0.06f, 0.10f, 0.16f, 35.0f);

    glPushMatrix();
    glTranslatef(-0.72f, 0.95f, 0);
    drawCubeScaled(0.25f, 1.0f, 0.25f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.72f, 0.95f, 0);
    drawCubeScaled(0.25f, 1.0f, 0.25f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3f, 0.18f, 0);
    drawCubeScaled(0.28f, 0.55f, 0.28f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3f, 0.18f, 0);
    drawCubeScaled(0.28f, 0.55f, 0.28f);
    glPopMatrix();

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


// Draw a single floodlight tower at (x, z)
static void drawFloodlight(float x, float z) {
    const float POLE_H  = 18.0f;
    const float ARM_LEN = 3.0f;

    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    // Pole
    setMaterial(0.35f, 0.35f, 0.38f, 30.0f);
    glPushMatrix();
    glRotatef(-90.0f, 1, 0, 0);
    drawCylinder(0.25f, POLE_H, 12);
    glPopMatrix();

    // Move to pole top
    glTranslatef(0.0f, POLE_H, 0.0f);

    // Horizontal arm
    setMaterial(0.35f, 0.35f, 0.38f, 30.0f);
    glPushMatrix();
    drawCubeScaled(ARM_LEN * 2.0f, 0.25f, 0.25f);
    glPopMatrix();

    // Two lamp heads on arm ends
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.95f, 0.75f);
    glPushMatrix();
    glTranslatef(-ARM_LEN, -0.4f, 0.0f);
    glutSolidSphere(0.45f, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef( ARM_LEN, -0.4f, 0.0f);
    glutSolidSphere(0.45f, 10, 10);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    glPopMatrix();
}

void drawLightPoles() {
    // 4 corner floodlight towers just outside the field
    float ox = FIELD_HALF_WIDTH  + 5.0f;
    float oz = FIELD_HALF_LENGTH + 5.0f;

    drawFloodlight(-ox, -oz);
    drawFloodlight( ox, -oz);
    drawFloodlight(-ox,  oz);
    drawFloodlight( ox,  oz);
}

void setupLighting() {
    GLfloat globalAmbient[] = {0.10f, 0.12f, 0.16f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    GLfloat light0Pos[] = {0.0f, 25.0f, -20.0f, 1.0f};
    GLfloat light0Diff[] = {0.85f, 0.90f, 1.0f, 1.0f};
    GLfloat light0Spec[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Spec);

    GLfloat light1Pos[] = {0.0f, 8.0f, 0.0f, 1.0f};
    GLfloat light1Diff[] = {0.0f, 0.55f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Diff);
}

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

    drawBitmapText2D(
        18,
        winH - 45,
        "Lives: " + std::to_string(lives) +
        "    Time: " + timer.str() +
        "    Camera: " + camName
    );

    drawBitmapText2D(
        18,
        68,
        "W/S: forward/backward    A/D: move left/right    Left/Right Arrow: turn"
    );

    drawBitmapText2D(
        18,
        48,
        "Space: jump    C: camera mode    P: pause    R: restart    Esc: exit"
    );

    drawBitmapText2D(
        18,
        28,
        "Mouse Left: rotate camera    Mouse Right/Wheel: zoom    Goal: collect crystals and enter the portal."
    );

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
