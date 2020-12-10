
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

void drawLineLoop(LINE line, COLOUR color) {
	glBegin(GL_LINE_LOOP);
	glColor3f(color.r, color.g, color.b);
	for (auto i = line.P.begin(); i != line.P.end(); i++) {
		glVertex3f((*i).x, (*i).y, (*i).z);
	}
	glEnd();
}

void drawAxis() 
{
	VECTOR3D ori = VECTOR3D{0.0,0.0,0.0};
	std::vector<VECTOR3D> vecx=std::vector<VECTOR3D>();
	vecx.push_back(ori);
	vecx.push_back(xVector);
	std::vector<VECTOR3D> vecy = std::vector<VECTOR3D>();
	vecy.push_back(ori);
	vecy.push_back(yVector);
	std::vector<VECTOR3D> vecz = std::vector<VECTOR3D>();
	vecz.push_back(ori);
	vecz.push_back(zVector);
	drawLine(LINE{ vecx }, COLOUR{ red });
	drawLine(LINE{ vecy }, COLOUR{ green });
	drawLine(LINE{ vecz }, COLOUR{ blue });
}


void drawBox(VECTOR3D center, double lenX, double lenY, double lenZ)
{
	///////////////
	//      |    //
 	//  -center- //
	//      |    //
	///////////////

	double lenx_half = lenX / 2;
	double leny_half = lenY / 2;
	double lenz_half = lenZ / 2;

	// ++ --> +- --> -- --> -+
	VECTOR3D vertex1 = VECTOR3D{ center.x + lenx_half, center.y + leny_half, center.z + lenz_half };
	VECTOR3D vertex2 = VECTOR3D{ center.x + lenx_half, center.y - leny_half, center.z + lenz_half };
	VECTOR3D vertex3 = VECTOR3D{ center.x - lenx_half, center.y - leny_half, center.z + lenz_half };
	VECTOR3D vertex4 = VECTOR3D{ center.x - lenx_half, center.y + leny_half, center.z + lenz_half };

	VECTOR3D vertex5 = VECTOR3D{ center.x + lenx_half, center.y + leny_half, center.z - lenz_half };
	VECTOR3D vertex6 = VECTOR3D{ center.x + lenx_half, center.y - leny_half, center.z - lenz_half };
	VECTOR3D vertex7 = VECTOR3D{ center.x - lenx_half, center.y - leny_half, center.z - lenz_half };
	VECTOR3D vertex8 = VECTOR3D{ center.x - lenx_half, center.y + leny_half, center.z - lenz_half };

	std::vector<VECTOR3D> vector1 = std::vector<VECTOR3D>();
	vector1.push_back(vertex1);
	vector1.push_back(vertex2);
	vector1.push_back(vertex3);
	vector1.push_back(vertex4);
	LINE line1 = LINE{vector1};

	std::vector<VECTOR3D> vector2 = std::vector<VECTOR3D>();
	vector2.push_back(vertex5);
	vector2.push_back(vertex6);
	vector2.push_back(vertex7);
	vector2.push_back(vertex8);
	LINE line2 = LINE{ vector2 };

	std::vector<VECTOR3D> vector3 = std::vector<VECTOR3D>();
	vector3.push_back(vertex1);
	vector3.push_back(vertex2);
	vector3.push_back(vertex6);
	vector3.push_back(vertex5);
	LINE line3 = LINE{ vector3 };

	std::vector<VECTOR3D> vector4 = std::vector<VECTOR3D>();
	vector4.push_back(vertex3);
	vector4.push_back(vertex4);
	vector4.push_back(vertex8);
	vector4.push_back(vertex7);
	LINE line4 = LINE{ vector4 };
	//Diubujamos el primer cuadrado
	drawLineLoop(line1, COLOUR{ red });
	//Dibujamos el segundo cuadrado
	drawLineLoop(line2, COLOUR{ red });

	//Dibujamos el tercero
	drawLineLoop(line3, COLOUR{ red });

	//Dibujamos el cuarto
	drawLineLoop(line4, COLOUR{ red });




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


