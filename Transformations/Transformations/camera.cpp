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

	VECTOR3D zaxis = Normalized(Substract(eyePosition, target));
	VECTOR3D xaxis = Normalized(CrossProduct(zaxis, upVector));
	VECTOR3D yaxis = CrossProduct (xaxis, zaxis);

	xaxis = MultiplyWithScalar(-1, xaxis);

	MATRIX3 mat = MATRIX3{	xaxis.x, xaxis.y, xaxis.z,
							yaxis.x, yaxis.y, yaxis.z,
							zaxis.x, zaxis.y, zaxis.z };

	MATRIX4 lookAtMat = InverseOrthogonalMatrix(mat, eyePosition);

	return lookAtMat;
}

void updateCameraOrientation(EULER& euler) {
	QUATERNION pitch = QuaternionFromAngleAxis(euler.pitch, zVector);
	QUATERNION yaw = QuaternionFromAngleAxis(euler.yaw, yVector);
	QUATERNION roll = QuaternionFromAngleAxis(euler.roll, xVector);

	euler.orientation = pitch;
	euler.orientation = MultiplyQuaternions(euler.orientation, yaw);
	euler.orientation = MultiplyQuaternions(euler.orientation, roll);
}

VECTOR3D getForward(EULER euler) {
	return Normalized(RotateWithQuaternion( MultiplyWithScalar(-1, zVector), euler.orientation));
}

VECTOR3D getUp(EULER euler) {
	return Normalized(RotateWithQuaternion(yVector, euler.orientation));
}
