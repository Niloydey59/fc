#include "DrawUtils.h"
#include <GL/freeglut.h>

void drawBitmapText2D(float x, float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
}

void drawBitmapText3D(const std::string& text, float x, float y, float z) {
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(x, y, z);
    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
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
    GLfloat diffuse[]  = {r, g, b, 1.0f};
    GLfloat specular[] = {0.45f, 0.45f, 0.45f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
