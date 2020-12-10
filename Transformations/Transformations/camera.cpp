#include "camera.h"

// TODO
// devuelve los valores de distancia de los planos a partir del fov vertical
FRUSTUM makeFrustum(double fovY, double aspectRatio, double nearValue, double farValue)
{
	const double DEG2RAD = PI / 180;
	double tangent = 0; // tangent of half fovY
	double height = 0; // half height of near plane
	double width = 0; // half width of near plane

	FRUSTUM ret;
	ret.bottom = fovY;
	ret.farValue = farValue;
	ret.nearValue = nearValue;
	ret.left;
	ret.right;
	ret.top;
	// TODO : rellenar valores de ret
	return ret;
}

//MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D target, VECTOR3D upVector) {};