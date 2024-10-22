#include "math3d.h"

VECTOR3D Add(VECTOR3D a, VECTOR3D b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

VECTOR3D Substract(VECTOR3D a, VECTOR3D b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

VECTOR3D MultiplyWithScalar(float scalar, VECTOR3D a) {
	return { a.x * scalar, a.y * scalar, a.z * scalar };
}

double Magnitude(VECTOR3D a) {
	return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

VECTOR3D Normalized(VECTOR3D a) {
	return	VECTOR3D{ a.x / Magnitude(a), a.y / Magnitude(a), a.z / Magnitude(a) };
}

VECTOR3D CrossProduct(VECTOR3D a, VECTOR3D b) {
	return VECTOR3D{ (a.y * b.z) - (a.z * b.y),
					 (a.z * b.x) - (a.x * b.z),
					 (a.x * b.y) - (a.y * b.x) };
}

double DotProduct(VECTOR3D a, VECTOR3D b) {
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

MATRIX3 Transpose(MATRIX3 m) {
	return MATRIX3{ VECTOR3D{m.column0.x,m.column1.x,m.column2.x},
					VECTOR3D{m.column0.y,m.column1.y,m.column2.y},
					VECTOR3D{m.column0.z,m.column1.z,m.column2.z} };
}

VECTOR3D Transform(MATRIX3 m, VECTOR3D a) {
	MATRIX3 mt = Transpose(m);
	return VECTOR3D{ DotProduct(mt.column0,a),DotProduct(mt.column1,a) ,DotProduct(mt.column2,a) };
}

MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t) {

	A = Transpose(A);

	VECTOR3D vec = Transform(A, t);


	MATRIX4 mat = MATRIX4{ {
		(float)A.column0.x,(float)A.column0.y,(float)A.column0.z,0.0f,
		(float)A.column1.x,(float)A.column1.y,(float)A.column1.z,0.0f,
		(float)A.column2.x,(float)A.column2.y,(float)A.column2.z,0.0f,
		(float)-vec.x,(float)-vec.y,(float)-vec.z,1.0f
	} };

	return mat;

}

QUATERNION QuaternionFromAngleAxis(float angle, VECTOR3D axis) {
	return QUATERNION{ axis.x * sin(angle * DTOR / 2), axis.y * sin(angle * DTOR / 2), axis.z * sin(angle * DTOR / 2), cos(angle * DTOR / 2) };
}

QUATERNION MultiplyQuaternions(QUATERNION a, QUATERNION b) {
	double Sa = a.r;
	double Sb = b.r;
	VECTOR3D Va = { a.i, a.j, a.k };
	VECTOR3D Vb = { b.i, b.j, b.k };

	double r = Sa * Sb - DotProduct(Va, Vb);
	VECTOR3D i = Add(Add(MultiplyWithScalar(Sa, Vb), MultiplyWithScalar(Sb, Va)), CrossProduct(Va, Vb));

	return { r, i.x, i.y, i.z };
}

QUATERNION Conjugate(QUATERNION a) {
	return QUATERNION{ a.r, -a.i, -a.j, -a.k };
}

double MagnitudeQuaternion(QUATERNION a) {
	return sqrt(pow(a.r, 2) + pow(a.i, 2) + pow(a.j, 2) + pow(a.k, 2));
}

QUATERNION MultiplyQuaternionWithScalar(float scalar, QUATERNION a) {
	return QUATERNION { a.r * scalar, a.i * scalar, a.j * scalar, a.k * scalar };
}

QUATERNION Inverse(QUATERNION a) {
	double Sa = a.r;
	VECTOR3D Va = { a.i, a.j, a.k };
	return MultiplyQuaternionWithScalar(1 / MagnitudeQuaternion(a), { Sa , Va.x, Va.y, Va.z });
}

VECTOR3D RotateWithQuaternion(VECTOR3D a, QUATERNION q) {
	QUATERNION p = QUATERNION{ 0, a.x, a.y, a.z };
	QUATERNION qI = Inverse(q);
	QUATERNION res = MultiplyQuaternions(MultiplyQuaternions(q, p), qI);
	return VECTOR3D{ res.i, res.j, res.k };
}
