#include <GL/freeglut.h>
#include <cstdlib>
#include <ctime>

#include "globals/Globals.h"
#include "renderer/Renderer.h"
#include "game_manager/GameManager.h"
#include "camera/Camera.h"
#include "input/Input.h"
#include "stadium/Stadium.h"
#include "ball/Ball.h"
#include "player/Player.h"

void display() {
    glClearColor(0.02f, 0.025f, 0.045f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (double)winW / (double)winH, 0.1, 500.0);

    updateCamera();
    setupLighting();

    drawStadium();
    drawPlayer();
    drawBall();
    drawHUD();

    glutSwapBuffers();
}

void idle() {
    static int previousTime = glutGet(GLUT_ELAPSED_TIME);
    int currentTime = glutGet(GLUT_ELAPSED_TIME);

    float dt = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;

    if (dt > 0.05f) {
        dt = 0.05f;
    }

    updateGame(dt);

    glutPostRedisplay();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;

    winW = w;
    winH = h;

    glViewport(0, 0, w, h);
}

void initOpenGL() {
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glShadeModel(GL_SMOOTH);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat fogColor[] = {0.02f, 0.025f, 0.045f, 1.0f};

    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.012f);
    glFogi(GL_FOG_MODE, GL_EXP2);
}

int main(int argc, char** argv) {
    srand((unsigned int)time(nullptr));

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(winW, winH);

    glutCreateWindow("Crystal Runner 3D - OpenGL FreeGLUT Game");

    initOpenGL();
    resetGame();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);

    glutSpecialFunc(specialDown);
    glutSpecialUpFunc(specialUp);

    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);

    glutMainLoop();

    return 0;
}
