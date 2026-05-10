#ifndef INPUT_H
#define INPUT_H

void keyboardDown(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void specialDown(int key, int x, int y);
void specialUp(int key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void mouseMotion(int x, int y);

#endif // INPUT_H
