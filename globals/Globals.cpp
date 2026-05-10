#include "Globals.h"

int winW = 1280;
int winH = 720;

bool keys[256] = {false};
bool specialKeys[256] = {false};

bool leftMouseDown = false;
bool rightMouseDown = false;
int lastMouseX = 0;
int lastMouseY = 0;

float arenaHalfSize = 32.0f;

Vec3 playerPos = {0.0f, 0.0f, -25.0f};

float playerYaw = 0.0f;
float playerRadius = 0.75f;

bool isJumping = false;
float jumpVelocity = 0.0f;

int lives = 3;

int homeScore = 0;
int awayScore = 0;
float gameTime = 0.0f;
float globalTime = 0.0f;

bool paused = false;
bool gameWon = false;
bool gameOver = false;

int cameraMode = 0; // 0 = third person, 1 = top view, 2 = first person
float cameraYawOffset = 0.0f;
float cameraPitch = 22.0f;
float cameraDistance = 15.0f;
