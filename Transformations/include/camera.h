#ifndef _GEOMETRIA_CAMERA_H_
#define _GEOMETRIA_CAMERA_H_

#include "math3d.h"

typedef struct {
    VECTOR3D position;
    VECTOR3D direction;
    VECTOR3D up;
    
    double aperture;    // in degrees
    int screenwidth,screenheight;
    
} CAMERA;


typedef struct {
    double left;
    double right;
    double bottom;
    double top;
    double nearValue;
    double farValue;
} FRUSTUM;

typedef struct {
	float yaw;	// Rotation around the Y axis. 
	float pitch; // Rotation around the X axis. 
	float roll;	// Rotation around the Z axis. 
	QUATERNION orientation; // Cached quaternion equivalent of this	euler object.
} EULER;

//TO DO
FRUSTUM makeFrustum(double fovY, double aspectRatio, double nearValue, double farValue);
MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D target, VECTOR3D upVector);
#endif
