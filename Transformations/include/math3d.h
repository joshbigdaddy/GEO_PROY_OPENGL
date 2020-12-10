#ifndef _GEOMETRIA_VECTOR3D_h
#define _GEOMETRIA_VECTOR3D_h
#include <math.h>

#define ABS(x) (x < 0 ? -(x) : (x))
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
#define TRUE  1
#define FALSE 0
#define ESC 27
#define PI 3.141592653589793238462643
#define DTOR            0.0174532925    // degrees to radians
#define RTOD            57.2957795      // radians to degrees

typedef struct {
    double x,y,z;
} VECTOR3D;


typedef struct {
    double r,g,b;
} COLOUR;

typedef struct {
    VECTOR3D column0;
    VECTOR3D column1;
    VECTOR3D column2;
} MATRIX3;


typedef struct {
    float m[16];
} MATRIX4;

typedef struct {
	double r;
	double i;
	double j;
	double k;
} QUATERNION;

static const COLOUR grey = {0.7,0.7,0.7};
static const COLOUR red = {1,0,0};
static const COLOUR green = {0,1,0};
static const COLOUR blue = {0,0,1};
static const COLOUR darkred = {0.6,0,0};
static const COLOUR darkgreen = {0,0.6,0};
static const VECTOR3D xVector = { 1.0, 0.0, 0.0 };
static const VECTOR3D yVector = { 0.0, 1.0, 0.0 };
static const VECTOR3D zVector = { 0.0, 0.0, 1.0 };

// Funciones sobre vectores
//TO DO
VECTOR3D Add(VECTOR3D a, VECTOR3D b);  
VECTOR3D Substract(VECTOR3D a, VECTOR3D b);
VECTOR3D MultiplyWithScalar(float scalar, VECTOR3D a);
double Magnitude(VECTOR3D a);
VECTOR3D Normalized(VECTOR3D a);
VECTOR3D CrossProduct(VECTOR3D a, VECTOR3D b);
double DotProduct(VECTOR3D a, VECTOR3D b);

// Funciones con matrices
//TO DO
MATRIX3 Transpose(MATRIX3 m);
VECTOR3D Transform (MATRIX3 m, VECTOR3D a);
//MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t);

// Funciones sobre quaterniones
//TO DO
//QUATERNION QuaternionFromAngleAxis(float angle, VECTOR3D axis){}
//QUATERNION Multiply(QUATERNION a, QUATERNION b) {}
//QUATERNION Conjugate(QUATERNION a) {}
//VECTOR3D RotateWithQuaternion(VECTOR3D a, QUATERNION q) {}

#endif
