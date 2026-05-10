#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include "../entities/Entities.h"

extern int winW;
extern int winH;

extern bool keys[256];
extern bool specialKeys[256];

extern bool leftMouseDown;
extern bool rightMouseDown;
extern int lastMouseX;
extern int lastMouseY;

extern float arenaHalfSize;

extern Vec3 playerPos;

extern float playerYaw;
extern float playerRadius;

extern bool isJumping;
extern float jumpVelocity;

extern int lives;

extern float gameTime;
extern float globalTime;

extern bool paused;
extern bool gameWon;
extern bool gameOver;

extern int cameraMode;
extern float cameraYawOffset;
extern float cameraPitch;
extern float cameraDistance;

#endif // GLOBALS_H
