#include "math3d.h"

VECTOR3D Add(VECTOR3D a, VECTOR3D b) {
	return	VECTOR3D{ a.x + b.x, a.y + b.y, a.z + b.z };
}
VECTOR3D Substract(VECTOR3D a, VECTOR3D b) {
	return	VECTOR3D{ a.x - b.x, a.y - b.y, a.z - b.z };
}
VECTOR3D MultiplyWithScalar(float scalar, VECTOR3D a) {
	return	VECTOR3D{ a.x * scalar, a.y * scalar, a.z * scalar };

}
double Magnitude(VECTOR3D a) {
	return sqrt(pow(a.x,2)+ pow(a.y, 2)+ pow(a.z, 2));
}
VECTOR3D Normalized(VECTOR3D a) {
	return	VECTOR3D{ a.x / Magnitude(a), a.y / Magnitude(a), a.z / Magnitude(a) };
}
VECTOR3D CrossProduct(VECTOR3D a, VECTOR3D b) {
	return VECTOR3D{(a.y * b.z) - (a.z * b.y),
					(a.z * b.x) - (a.x * b.z),
					(a.x * b.y) - (a.y * b.x) };
}
double DotProduct(VECTOR3D a, VECTOR3D b) {
	return ( (a.x*b.x)+ (a.y * b.y)+ (a.z * b.z));
}
MATRIX3 Transpose(MATRIX3 m) {

		/*m.column0;
		m.column1;
		m.column2;*/

	return MATRIX3{
		VECTOR3D{m.column0.x,m.column0.x,m.column0.x},
		VECTOR3D{m.column0.y,m.column1.y,m.column2.y},
		VECTOR3D{m.column0.z,m.column1.z,m.column2.z}
	};

}
VECTOR3D Transform(MATRIX3 m, VECTOR3D a) {
	MATRIX3 mt = Transpose(m);
	return VECTOR3D{DotProduct(mt.column0,a),DotProduct(mt.column1,a) ,DotProduct(mt.column2,a) };
}
//MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t) {}

//QUATERNION QuaternionFromAngleAxis(float angle, VECTOR3D axis){}
//QUATERNION Multiply(QUATERNION a, QUATERNION b) {}
//QUATERNION Conjugate(QUATERNION a) {}
//VECTOR3D RotateWithQuaternion(VECTOR3D a, QUATERNION q) {}

