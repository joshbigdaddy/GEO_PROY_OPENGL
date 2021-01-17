#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GLInclude.h"
#include "camera.h"
#include "shapes.h"

void Display(void);
void Init(void);
void Render(void);
void Lighting(void);
void InitCamera();
void HandleKeyboard(unsigned char key,int x, int y);
void HandleReshape(int,int);
void HandleIdle(void);
void HandleMouseMotion(int x, int y);
void HandleMousePassiveMotion(int x, int y);

double rotateSpeed = 3;
double moveSpeed = 3;
double rotateAngle = 0;
CAMERA camera;
EULER eulerCamera;
int mouseFinal[2];
int mouseInicial[2];

int main(int argc,char **argv)
{
    InitCamera();

	std::cout << "Pulsa H para reiniciar la posicion de la camara\n";
	std::cout << "R para rotar la escena\n";

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Geometria Proyectiva");    
    glutDisplayFunc( Display);
    glutReshapeFunc(HandleReshape);
    glutReshapeWindow(camera.screenwidth,camera.screenheight);
    glutIdleFunc(HandleIdle);
    glutKeyboardFunc(HandleKeyboard);
    glutMotionFunc(HandleMouseMotion);
    glutPassiveMotionFunc(HandleMousePassiveMotion);
    Init();
    Lighting();
    
    glutMainLoop();
    return(0);
}

void Init(void)
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POINT_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_DITHER);
    glDisable(GL_CULL_FACE);
    
    glLineWidth(1.0);
    glPointSize(1.0);
    
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glFrontFace(GL_CW);
    glClearColor(0.0,0.0,0.0,0.0);         /* Background colour */
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

void Display(void)
{
    glDrawBuffer(GL_BACK_LEFT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glDrawBuffer(GL_BACK);
    
	double nearValue = 0.1;
	double farValue = 10000;
    
    double aspectRatio  = camera.screenwidth / (double)camera.screenheight;
    FRUSTUM centerFrustum = makeFrustum(camera.aperture, aspectRatio, nearValue, farValue);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	//gluPerspective(camera.aperture, aspectRatio, nearValue, farValue);
	glFrustum(centerFrustum.left, centerFrustum.right, centerFrustum.bottom, centerFrustum.top, centerFrustum.nearValue, centerFrustum.farValue);
    

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	VECTOR3D target = Add(camera.position, getForward(eulerCamera));
    //gluLookAt(camera.position.x,camera.position.y,camera.position.z, target.x , target.y, target.z, camera.up.x,camera.up.y,camera.up.z);     
	MATRIX4 lookAtMatrix = lookAt(camera.position, target, getUp(eulerCamera));
    glLoadMatrixf(lookAtMatrix.m);

    glViewport(0,0,camera.screenwidth,camera.screenheight);
    
    Render();
    
    glutSwapBuffers();
}


void Render(void)
{
    GLfloat specular[4] = {1.0,1.0,1.0,1.0};
    GLfloat shiny[1] = {5.0};
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    
    glPushMatrix();   
	glRotatef(rotateAngle, 0.0, 1.0, 0.0);
	drawAxis();
	VECTOR3D dotPos = { 4.0, 0.0, 0.0 };		

	drawDot(dotPos, 2.0);	
    drawBox(dotPos,4.0,4.0,4.0);
	drawCircle(dotPos, 4.0);
    drawCircle2(dotPos, 5.0);
    glPopMatrix();
}

void Lighting(void)
{
    GLfloat fullambient[4] = {1.0,1.0,1.0,1.0};
    GLfloat position[4] = {0.0,0.0,0.0,0.0};
    GLfloat ambient[4]  = {0.2,0.2,0.2,1.0};
    GLfloat diffuse[4]  = {1.0,1.0,1.0,1.0};
    GLfloat specular[4] = {0.0,0.0,0.0,1.0};
    
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
    glDisable(GL_LIGHT5);
    glDisable(GL_LIGHT6);
    glDisable(GL_LIGHT7);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,fullambient);
    glLightfv(GL_LIGHT0,GL_POSITION,position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    glEnable(GL_LIGHT0);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
}

void HandleKeyboard(unsigned char key,int x, int y)
{
    switch (key) {
        case ESC:
        case 'Q':
        case 'q':
            exit(0);
            break;
        case 'R':
        case 'r':
            rotateAngle += rotateSpeed;
            break;     
        case 'h':
        case 'H':
            InitCamera();
            break;		
        case 'w':
        case 'W':
            camera.position = Add(camera.position, MultiplyWithScalar(moveSpeed, getForward(eulerCamera)));
            break;
        case 's':
        case 'S':
            camera.position = Substract(camera.position, MultiplyWithScalar(moveSpeed, getForward(eulerCamera)));
            break;
        case 'a':
        case 'A':
            camera.position = Add(camera.position, MultiplyWithScalar(moveSpeed, CrossProduct( getUp(eulerCamera) ,getForward(eulerCamera))));
            break;
        case 'd':
        case 'D':
            camera.position = Substract(camera.position, MultiplyWithScalar(moveSpeed, CrossProduct(getUp(eulerCamera), getForward(eulerCamera))));
            break;
    }
}

void HandleMouseMotion(int x, int y)
{
    mouseFinal[0] = x;
    mouseFinal[1] = y;

    eulerCamera.yaw += (mouseInicial[0] - mouseFinal[0]) * 0.1f;
    eulerCamera.pitch += (mouseInicial[1] - mouseFinal[1]) * -0.1f;
    updateCameraOrientation(eulerCamera);

    mouseInicial[0] = x;
    mouseInicial[1] = y;
}

void HandleMousePassiveMotion(int x, int y)
{
    mouseInicial[0] = x;
    mouseInicial[1] = y;
}


void HandleIdle(void)
{
    glutPostRedisplay();
}

void HandleReshape(int w,int h)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    camera.screenwidth = w;
    camera.screenheight = h;
}


void InitCamera()
{
    camera.screenwidth = 600;
    camera.screenheight = 400;

    camera.aperture = 45;
	rotateAngle = 0.0;

    camera.position.x = 5;
    camera.position.y = 0;
    camera.position.z = -50;
    
    //camera.direction.x = -camera.position.x;
    //camera.direction.y = -camera.position.y;
    //camera.direction.z = -camera.position.z;
    
    //camera.up.x = 0;
    //camera.up.y = 1;
    //camera.up.z = 0;

    eulerCamera.pitch = 0;
    eulerCamera.roll = 0;
    eulerCamera.yaw = 0;
    updateCameraOrientation(eulerCamera);
}

