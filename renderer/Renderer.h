#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include "../entities/Entities.h"

void drawBitmapText2D(float x, float y, const std::string& text);
void drawBitmapText3D(const std::string& text, float x, float y, float z);
void drawCubeScaled(float sx, float sy, float sz);
void drawCylinder(float radius, float height, int slices = 24);
void setMaterial(float r, float g, float b, float shininess = 35.0f);

void setupLighting();
void drawFloor();
void drawWalls();
void drawTree(const Decoration& t);
void drawDecorations();
void drawPlayer();
void drawLightPoles();
void drawHUD();

#endif // RENDERER_H
