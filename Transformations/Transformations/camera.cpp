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

	VECTOR3D zaxis = Normalized(Substract(target, eyePosition));
	VECTOR3D xaxis = Normalized(CrossProduct(zaxis, upVector));
	VECTOR3D yaxis = CrossProduct (xaxis, zaxis);

	zaxis = MultiplyWithScalar(-1,zaxis);

	MATRIX3 mat = MATRIX3{	xaxis.x, xaxis.y, xaxis.z,
							yaxis.x, yaxis.y, yaxis.z,
							zaxis.x, zaxis.y, zaxis.z };

	MATRIX4 lookAtMat = InverseOrthogonalMatrix(mat, eyePosition);

	return lookAtMat;
}

void updateCameraOrientation(EULER& euler) {

}


