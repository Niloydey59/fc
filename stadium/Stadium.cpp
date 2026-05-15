#include "Stadium.h"
#include "../math/MathUtils.h"
#include "../renderer/DrawUtils.h"
#include <GL/freeglut.h>
#include <cmath>

// ── Pitch markings constants ─────────────────────────────────
static const float FL = FIELD_HALF_LENGTH;
static const float FW = FIELD_HALF_WIDTH;

static const float PENALTY_BOX_HW = 20.16f;  // half of 40.32 m
static const float PENALTY_BOX_D  = 16.5f;   // depth from goal line

static const float GOAL_BOX_HW    = 9.16f;   // half of 18.32 m
static const float GOAL_BOX_D     = 5.5f;

static const float PENALTY_SPOT_D = 11.0f;
static const float CENTRE_R       = 9.15f;
static const float CORNER_R       = 1.0f;

static const float GOAL_HW        = 3.66f;   // half of 7.32 m
static const float GOAL_H         = 2.44f;
static const float GOAL_D         = 2.0f;

static const float LINE_Y         = 0.02f;   // slightly above grass

// ── Helpers ──────────────────────────────────────────────────
static void circleXZ(float cx, float cz, float r, float y, int segs = 64) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segs; i++) {
        float a = 2.0f * PI * i / segs;
        glVertex3f(cx + r * std::cos(a), y, cz + r * std::sin(a));
    }
    glEnd();
}

static void arcXZ(float cx, float cz, float r, float a1, float a2, float y, int segs = 48) {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segs; i++) {
        float a = a1 + (a2 - a1) * i / segs;
        glVertex3f(cx + r * std::cos(a), y, cz + r * std::sin(a));
    }
    glEnd();
}

// How far grass extends past the field boundary lines
static const float GRASS_EXT = 10.0f;

// ── Grass with alternating stripes ───────────────────────────
static void drawGrass() {
    glDisable(GL_LIGHTING);

    float GW = FW + GRASS_EXT;   // grass half-width
    float GL = FL + GRASS_EXT;   // grass half-length

    // 1. Flat dark-green base for the full outer grass area
    glColor3f(0.15f, 0.45f, 0.15f);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0); // normal vector to surface,used for lighting but not visible here as lighting is off.
        glVertex3f(-GW, 0.0f, -GL);
        glVertex3f( GW, 0.0f, -GL);
        glVertex3f( GW, 0.0f,  GL);
        glVertex3f(-GW, 0.0f,  GL);
    glEnd();

    // 2. Alternating stripes inside the field boundary only
    const int STRIPES = 14;
    float sw = (FL * 2.0f) / STRIPES;

    for (int i = 0; i < STRIPES; i++) {
        float z0 = -FL + i * sw;
        float z1 = z0 + sw;
        if (i % 2 == 0) glColor3f(0.18f, 0.52f, 0.18f);
        else             glColor3f(0.22f, 0.60f, 0.22f);

        glBegin(GL_QUADS);
            glNormal3f(0, 1, 0);
            glVertex3f(-FW, 0.01f, z0);
            glVertex3f( FW, 0.01f, z0);
            glVertex3f( FW, 0.01f, z1);
            glVertex3f(-FW, 0.01f, z1);
        glEnd();
    }

    glEnable(GL_LIGHTING);
}


// ── Field lines ──────────────────────────────────────────────
static void drawFieldLines() {
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    float y = LINE_Y;

    // Outer boundary
    glBegin(GL_LINE_LOOP);
        glVertex3f(-FW, y, -FL);
        glVertex3f( FW, y, -FL);
        glVertex3f( FW, y,  FL);
        glVertex3f(-FW, y,  FL);
    glEnd();

    // Halfway line
    glBegin(GL_LINES);
        glVertex3f(-FW, y, 0.0f);
        glVertex3f( FW, y, 0.0f);
    glEnd();

    // Centre circle & spot
    circleXZ(0.0f, 0.0f, CENTRE_R, y);
    glPointSize(6.0f);
    glBegin(GL_POINTS);
        glVertex3f(0.0f, y, 0.0f);
    glEnd();

    // ─ North end (z = -FL) ─
    float nPenZ  = -FL + PENALTY_BOX_D;
    float nGBoxZ = -FL + GOAL_BOX_D;
    float nSpotZ = -FL + PENALTY_SPOT_D;

    // North penalty box
    glBegin(GL_LINE_LOOP);
        glVertex3f(-PENALTY_BOX_HW, y, -FL);
        glVertex3f(-PENALTY_BOX_HW, y,  nPenZ);
        glVertex3f( PENALTY_BOX_HW, y,  nPenZ);
        glVertex3f( PENALTY_BOX_HW, y, -FL);
    glEnd();

    // North goal box
    glBegin(GL_LINE_LOOP);
        glVertex3f(-GOAL_BOX_HW, y, -FL);
        glVertex3f(-GOAL_BOX_HW, y,  nGBoxZ);
        glVertex3f( GOAL_BOX_HW, y,  nGBoxZ);
        glVertex3f( GOAL_BOX_HW, y, -FL);
    glEnd();

    // North penalty spot
    glBegin(GL_POINTS);
        glVertex3f(0.0f, y, nSpotZ);
    glEnd();

    // North penalty arc (outside the box, toward centre)
    // arc where sin(a)*CENTRE_R = nPenZ - nSpotZ = PENALTY_BOX_D - PENALTY_SPOT_D = 5.5
    float nHalfAng = std::asin((PENALTY_BOX_D - PENALTY_SPOT_D) / CENTRE_R);
    arcXZ(0.0f, nSpotZ, CENTRE_R, nHalfAng, PI - nHalfAng, y);

    // North corner arcs
    arcXZ(-FW, -FL, CORNER_R,  0.0f,      PI * 0.5f, y);
    arcXZ( FW, -FL, CORNER_R,  PI * 0.5f, PI,        y);

    // ─ South end (z = +FL) ─
    float sPenZ  =  FL - PENALTY_BOX_D;
    float sGBoxZ =  FL - GOAL_BOX_D;
    float sSpotZ =  FL - PENALTY_SPOT_D;

    // South penalty box
    glBegin(GL_LINE_LOOP);
        glVertex3f(-PENALTY_BOX_HW, y,  FL);
        glVertex3f(-PENALTY_BOX_HW, y,  sPenZ);
        glVertex3f( PENALTY_BOX_HW, y,  sPenZ);
        glVertex3f( PENALTY_BOX_HW, y,  FL);
    glEnd();

    // South goal box
    glBegin(GL_LINE_LOOP);
        glVertex3f(-GOAL_BOX_HW, y,  FL);
        glVertex3f(-GOAL_BOX_HW, y,  sGBoxZ);
        glVertex3f( GOAL_BOX_HW, y,  sGBoxZ);
        glVertex3f( GOAL_BOX_HW, y,  FL);
    glEnd();

    // South penalty spot
    glBegin(GL_POINTS);
        glVertex3f(0.0f, y, sSpotZ);
    glEnd();

    // South penalty arc (outside the box, toward centre)
    float sHalfAng = std::asin((PENALTY_BOX_D - PENALTY_SPOT_D) / CENTRE_R);
    arcXZ(0.0f, sSpotZ, CENTRE_R, PI + sHalfAng, 2.0f * PI - sHalfAng, y);

    // South corner arcs
    arcXZ(-FW,  FL, CORNER_R, -PI * 0.5f, 0.0f,      y);
    arcXZ( FW,  FL, CORNER_R,  PI,        PI * 1.5f,  y);

    glLineWidth(1.0f);
    glPointSize(1.0f);
    glEnable(GL_LIGHTING);
}

// ── Goals (white posts + crossbar) ───────────────────────────
static void drawGoal(float goalLineZ, float sign) {
    // sign = +1 → goal opens toward +z (north goal), -1 → south goal
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);

    float backZ = goalLineZ + sign * GOAL_D;

    // Two posts
    glBegin(GL_LINES);
        glVertex3f(-GOAL_HW, 0.0f,   goalLineZ);
        glVertex3f(-GOAL_HW, GOAL_H, goalLineZ);

        glVertex3f( GOAL_HW, 0.0f,   goalLineZ);
        glVertex3f( GOAL_HW, GOAL_H, goalLineZ);
    glEnd();

    // Crossbar
    glBegin(GL_LINES);
        glVertex3f(-GOAL_HW, GOAL_H, goalLineZ);
        glVertex3f( GOAL_HW, GOAL_H, goalLineZ);
    glEnd();

    // Back posts
    glBegin(GL_LINES);
        glVertex3f(-GOAL_HW, 0.0f,   backZ);
        glVertex3f(-GOAL_HW, GOAL_H, backZ);
        glVertex3f( GOAL_HW, 0.0f,   backZ);
        glVertex3f( GOAL_HW, GOAL_H, backZ);
    glEnd();

    // Top back bar
    glBegin(GL_LINES);
        glVertex3f(-GOAL_HW, GOAL_H, backZ);
        glVertex3f( GOAL_HW, GOAL_H, backZ);
    glEnd();

    // Side bars (top)
    glBegin(GL_LINES);
        glVertex3f(-GOAL_HW, GOAL_H, goalLineZ);
        glVertex3f(-GOAL_HW, GOAL_H, backZ);
        glVertex3f( GOAL_HW, GOAL_H, goalLineZ);
        glVertex3f( GOAL_HW, GOAL_H, backZ);
    glEnd();

    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
}

static void drawFloodlight(float x, float z) {
    const float POLE_H  = 18.0f;
    const float ARM_LEN = 3.0f;

    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    setMaterial(0.35f, 0.35f, 0.38f, 30.0f);
    glPushMatrix();
    glRotatef(-90.0f, 1, 0, 0);
    drawCylinder(0.25f, POLE_H, 12);
    glPopMatrix();

    glTranslatef(0.0f, POLE_H, 0.0f);

    setMaterial(0.35f, 0.35f, 0.38f, 30.0f);
    glPushMatrix();
    drawCubeScaled(ARM_LEN * 2.0f, 0.25f, 0.25f);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix(); glTranslatef(-ARM_LEN, -0.4f, 0.0f); glutSolidSphere(0.45f, 10, 10); glPopMatrix();
    glPushMatrix(); glTranslatef( ARM_LEN, -0.4f, 0.0f); glutSolidSphere(0.45f, 10, 10); glPopMatrix();
    glEnable(GL_LIGHTING);

    glPopMatrix();
}

void drawLightPoles() {
    float ox = FIELD_HALF_WIDTH  + 5.0f;
    float oz = FIELD_HALF_LENGTH + 5.0f;
    drawFloodlight(-ox, -oz);
    drawFloodlight( ox, -oz);
    drawFloodlight(-ox,  oz);
    drawFloodlight( ox,  oz);
}

// ── Public entry points ──────────────────────────────────────
void drawStadium() {
    drawGrass();
    drawFieldLines();
    drawGoal(-FL, +1.0f);
    drawGoal( FL, -1.0f);
    drawLightPoles();
}


