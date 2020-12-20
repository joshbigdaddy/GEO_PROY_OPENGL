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
	return MATRIX3{ VECTOR3D{m.column0.x,m.column0.x,m.column0.x},
					VECTOR3D{m.column0.y,m.column1.y,m.column2.y},
					VECTOR3D{m.column0.z,m.column1.z,m.column2.z} };
}

VECTOR3D Transform(MATRIX3 m, VECTOR3D a) {
	MATRIX3 mt = Transpose(m);
	return VECTOR3D{ DotProduct(mt.column0,a),DotProduct(mt.column1,a) ,DotProduct(mt.column2,a) };
}

QUATERNION QuaternionFromAngleAxis(float angle, VECTOR3D axis) {
	return QUATERNION{ axis.x * sin(angle / 2), axis.y * sin(angle / 2), axis.z * sin(angle / 2), cos(angle / 2) };
}

QUATERNION MultiplyQuaternions(QUATERNION a, QUATERNION b) {
	float Sa = a.r;
	float Sb = b.r;
	VECTOR3D Va = { a.i, a.j, a.k };
	VECTOR3D Vb = { b.i, b.j, b.k };

	double r = Sa * Sb - DotProduct(Va, Vb);
	VECTOR3D i = Add(Add(MultiplyWithScalar(Sa, Vb), MultiplyWithScalar(Sb, Va)), CrossProduct(Va, Vb));

	return { r, i.x, i.y, i.z };
}

QUATERNION Conjugate(QUATERNION a) {
	return QUATERNION{ a.r, -a.i, -a.j, -a.k };
}

MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t) {

	double a = -DotProduct(A.column0,t );
    double b = -DotProduct(A.column1,t );
	double c = -DotProduct(A.column2,t );

	MATRIX3 At = Transpose(A);

	float matt[] = { 
		At.column0.x,At.column1.x,At.column2.x,a,
		At.column0.y,At.column1.y,At.column2.y,b,
		At.column0.z,At.column1.y,At.column2.y,c,
		0,0,0,1
	};
	MATRIX4 mat=MATRIX4{ *matt };
	return mat;

}

double MagnitudeQuaternion(QUATERNION a) {
	return sqrt(pow(a.r, 2) + pow(a.i, 2) + pow(a.j, 2) + pow(a.k, 2));
}

QUATERNION MultiplyQuaternionWithScalar(float scalar, QUATERNION a) {
	return { a.r * scalar, a.i * scalar, a.j * scalar, a.k * scalar };
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
