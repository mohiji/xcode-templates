/**
 * Matrix3.h
 * 3x3 matrices.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#ifndef Matrix3_h
#define Matrix3_h

#include "Vector3.h"

struct Matrix3
{
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
	
	// The default constructor leaves the matrix un-initialized.
	Matrix3() {}
	Matrix3(const Matrix3 &copy);
	Matrix3(float _11, float _12, float _13,
			float _21, float _22, float _23,
			float _31, float _32, float _33);

	Matrix3& operator= (const Matrix3 &rhs);
	
	// Set the matrix to the Identity matrix
	void setIdentity();
	
	// Set up rotations.  Theta is specified in radians
	void setupRotateX(float theta);
	void setupRotateY(float theta);
	void setupRotateZ(float theta);
	void setupRotateAxisAngle(const Vector3 &axis, float theta);
	
	Matrix3 transpose() const;
	
	// Helper variable for initializing identity matrices
	static const Matrix3 kIdentity;
};

// Vector and matrix multiplication
Vector3 operator* (const Vector3 &v, const Matrix3 &m);
Matrix3 operator* (const Matrix3 &a, const Matrix3 &b);

Vector3& operator*=(Vector3 &v, const Matrix3 &m);
Matrix3& operator*=(Matrix3 &a, const Matrix3 &b);

#endif /* include guard */
