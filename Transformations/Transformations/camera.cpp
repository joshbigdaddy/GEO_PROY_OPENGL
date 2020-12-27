#include "camera.h"

// devuelve los valores de distancia de los planos a partir del fov vertical
FRUSTUM makeFrustum(double fovY, double aspectRatio, double nearValue, double farValue)
{
	const double DEG2RAD = PI / 180;
	double tangent = tan(fovY / 2 * DEG2RAD); // tangent of half fovY
	double height = nearValue * tangent; // half height of near plane
	double width = height * aspectRatio; // half width of near plane

	FRUSTUM ret;
	ret.left = -width;
	ret.right = width;
	ret.bottom = -height;
	ret.top = height;
	ret.nearValue = nearValue;
	ret.farValue = farValue;
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