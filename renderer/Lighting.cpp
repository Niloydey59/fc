#include "Lighting.h"
#include <GL/freeglut.h>

void setupLighting() {
    GLfloat globalAmbient[] = {0.10f, 0.12f, 0.16f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    GLfloat light0Pos[]  = {0.0f, 25.0f, -20.0f, 1.0f};
    GLfloat light0Diff[] = {0.85f, 0.90f,  1.0f,  1.0f};
    GLfloat light0Spec[] = {1.0f,  1.0f,   1.0f,  1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0Diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Spec);

    GLfloat light1Pos[]  = {0.0f, 8.0f, 0.0f, 1.0f};
    GLfloat light1Diff[] = {0.0f, 0.55f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1Diff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Diff);
}
