#include "Camera.h"
#include "../globals/Globals.h"
#include <GL/freeglut.h>
#include <cmath>

void updateCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (cameraMode == 0) { // third person
        float yaw = degToRad(playerYaw + cameraYawOffset);
        float pitch = degToRad(cameraPitch);

        float cx = playerPos.x + cameraDistance * std::cos(pitch) * std::sin(yaw);
        float cy = playerPos.y + 3.0f + cameraDistance * std::sin(pitch);
        float cz = playerPos.z + cameraDistance * std::cos(pitch) * std::cos(yaw);

        gluLookAt(
            cx, cy, cz,
            playerPos.x, playerPos.y + 1.2f, playerPos.z,
            0, 1, 0
        );
    }
    else if (cameraMode == 1) { // top view
        gluLookAt(
            playerPos.x, 48.0f, playerPos.z + 1.0f,
            playerPos.x, 0.0f, playerPos.z,
            0, 0, -1
        );
    }
    else { // first person(2)
        float yaw = degToRad(playerYaw);

        float eyeX = playerPos.x;
        float eyeY = playerPos.y + 1.55f;
        float eyeZ = playerPos.z;

        float lookX = eyeX + (-std::sin(yaw)) * 12.0f;
        float lookY = eyeY + std::sin(degToRad(cameraPitch)) * 12.0f;
        float lookZ = eyeZ + (-std::cos(yaw)) * 12.0f;

        gluLookAt(
            eyeX, eyeY, eyeZ,
            lookX, lookY, lookZ,
            0, 1, 0
        );
    }
}
