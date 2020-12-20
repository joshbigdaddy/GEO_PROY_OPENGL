#ifndef _GEOMETRIA_SHAPES_H_
#define _GEOMETRIA_SHAPES_H_

#include "GLInclude.h"
#include "math3d.h"
#include <vector>

typedef struct {
	std::vector<VECTOR3D> P;
} LINE;

void drawDot(VECTOR3D position, float sradius = 1, COLOUR color = grey);
void drawLine(LINE line, COLOUR color = grey);
void drawAxis();
void drawBox(VECTOR3D center, double lenX, double lenY, double lenZ);
void drawCircle(VECTOR3D position, float sradius = 1);

#endif
