
#include "GLInclude.h"
#include "shapes.h"
#include "math3d.h"

void drawDot(VECTOR3D position, float sradius, COLOUR color)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);

	VECTOR3D p[4], n[4];
	int STEP = 30;
	for (int i = 0; i<360; i += STEP) {
		for (int j = -90; j<90; j += STEP) {

			p[0].x = sradius * cos(j*DTOR) * cos(i*DTOR);
			p[0].y = sradius * sin(j*DTOR);
			p[0].z = sradius * cos(j*DTOR) * sin(i*DTOR);
			n[0] = p[0];

			p[1].x = sradius * cos((j + STEP)*DTOR) * cos(i*DTOR);
			p[1].y = sradius * sin((j + STEP)*DTOR);
			p[1].z = sradius * cos((j + STEP)*DTOR) * sin(i*DTOR);
			n[1] = p[1];

			p[2].x = sradius * cos((j + STEP)*DTOR) * cos((i + STEP)*DTOR);
			p[2].y = sradius * sin((j + STEP)*DTOR);
			p[2].z = sradius * cos((j + STEP)*DTOR) * sin((i + STEP)*DTOR);
			n[2] = p[2];

			p[3].x = sradius * cos(j*DTOR) * cos((i + STEP)*DTOR);
			p[3].y = sradius * sin(j*DTOR);
			p[3].z = sradius * cos(j*DTOR) * sin((i + STEP)*DTOR);
			n[3] = p[3];

			glBegin(GL_POLYGON);
			if (i % (STEP * 4) == 0)
				glColor3f(color.r, color.g, color.b);
			else
				glColor3f(color.r*0.5, color.g*0.5, color.b*0.5);
			for (int k = 0; k<4; k++) {
				glNormal3f(n[k].x, n[k].y, n[k].z);
				glVertex3f(p[k].x, p[k].y, p[k].z);
			}
			glEnd();
		}
	}

	glPopMatrix();
}

void drawLine(LINE line, COLOUR color) {
	glBegin(GL_LINE_STRIP);
	glColor3f(color.r, color.g, color.b);
	for (auto i = line.P.begin(); i != line.P.end(); i++) {
		glVertex3f((*i).x, (*i).y, (*i).z);
	}
	glEnd();
}

void drawAxis() 
{
	std::vector<VECTOR3D> vecx=std::vector<VECTOR3D>();
	vecx.push_back(xVector);
	std::vector<VECTOR3D> vecy = std::vector<VECTOR3D>();
	vecy.push_back(yVector);
	std::vector<VECTOR3D> vecz = std::vector<VECTOR3D>();
	vecz.push_back(zVector);
	drawLine(LINE{ vecx }, COLOUR{ grey });
	drawLine(LINE{ vecy }, COLOUR{ grey });
	drawLine(LINE{ vecz }, COLOUR{ grey });
}


void drawBox(VECTOR3D center, double lenX, double lenY, double lenZ)
{

}

void drawCircle(VECTOR3D position, float sradius)
{	
	int numDiv = 10;
	LINE circle;
	VECTOR3D point;
	double step = 1.0 / numDiv;
	for (int i = 0; i <= numDiv; i++)
	{
		double t = i * step;
		point.x = (1 - t * t) / (1 + t * t);
		point.y = 2.0 * t / (1 + t * t);
		point.z = 0.0;
		circle.P.push_back(point);		
	}
	drawLine(circle);	
}


