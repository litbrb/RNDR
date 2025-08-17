#include "windows.h"

extern HDC rndrHDC;

#define drawLine(x1, y1, x2, y2) MoveToEx(rndrHDC, x1, y1, NULL), LineTo(rndrHDC, x2, y2)

void draw();

int setup(const char* title, int width, int height);