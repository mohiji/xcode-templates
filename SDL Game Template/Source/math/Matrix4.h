/**
 * Matrix4.h
 * 4x4 matrices.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#ifndef Matrix4_h
#define Matrix4_h

#include "Vector3.h"
#include "Matrix3.h"

struct Matrix4
{
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;
	
	// The default constructor leaves the matrix un-initialized.
	Matrix4() {}
	Matrix4(const Matrix4 &copy);
	Matrix4(float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44);
	Matrix4(const Matrix3 &rotate, const Vector3 &translate);
	
	Matrix4& operator= (const Matrix4 &rhs);
	
	// Set the matrix using a rotation matrix and a translation
	void setMatrix(const Matrix3 &rotate, const Vector3 &translate);
	
	// Set the matrix to the Identity matrix
	void setIdentity();
	
	// Set the matrix' translation portion to 0.
	void zeroTranslation();
	
	// Set the translation portion of the matrix
	void setTranslation(const Vector3 &v);
	
	// Set the translation portion of the matrix to v, and set the
	// rest to identity.
	void setupTranslation(const Vector3 &v);
	
	// Set up rotations.  Theta is specified in radians.  Each of these
	// will set the translation term to 0.
	void setupRotateX(float theta);
	void setupRotateY(float theta);
	void setupRotateZ(float theta);
	void setupRotateAxisAngle(const Vector3 &axis, float theta);
	
	// Set up as an OpenGL-style perspective projection matrix
	// (e.g. glFrustum)
	void setupFrustum(float left, float right, float bottom, float top, float clipNear, float clipFar);
	
	// Get information back out of the thing
	Matrix3 getRotateMatrix() const;
	Vector3 getTranslation() const;
	
	// Useful properties of the matrix
	float determinant() const;
	Matrix4 inverse() const;
	
	// Handy for debugging
	void printMatrix(const char *description) const;
	
	// Helper variable for initializing identity matrices
	static const Matrix4 kIdentity;
};

// Vector and matrix multiplication
Vector3 operator* (const Vector3 &v, const Matrix4 &m);
Matrix4 operator* (const Matrix4 &a, const Matrix4 &b);

Vector3& operator*=(Vector3 &v, const Matrix4 &m);
Matrix4& operator*=(Matrix4 &a, const Matrix4 &b);

#endif /* include guard */
