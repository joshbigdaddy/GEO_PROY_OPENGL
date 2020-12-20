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

MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D target, VECTOR3D upVector) {

	VECTOR3D forward = Substract( eyePosition , target);
	VECTOR3D side = CrossProduct( upVector , forward);
	VECTOR3D up = CrossProduct (forward , side);
	forward = Normalized(forward);
	side = Normalized(side);
	up = Normalized(up);

	MATRIX3 mat = MATRIX3{forward.x,side.x,up.x,
		forward.y,side.y,up.y,
		forward.z,side.z,up.z};

	return InverseOrthogonalMatrix(mat, eyePosition);
};