#ifndef DRAWUTILS_H
#define DRAWUTILS_H

#include <string>

void drawBitmapText2D(float x, float y, const std::string& text);
void drawBitmapText3D(const std::string& text, float x, float y, float z);
void drawCubeScaled(float sx, float sy, float sz);
void drawCylinder(float radius, float height, int slices = 24);
void setMaterial(float r, float g, float b, float shininess = 35.0f);

#endif // DRAWUTILS_H
