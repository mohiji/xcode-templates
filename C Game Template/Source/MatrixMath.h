/**
 * MatrixMath.h
 * 3x3 and 4x4 matrices.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#ifndef MatrixMath_h
#define MatrixMath_h

#include "VectorMath.h"

typedef struct Matrix3_s
{
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
}Matrix3;

typedef struct Matrix4_s
{
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;
}Matrix4;

#pragma mark Matrix3

// Reset the matrix to an identity matrix
void Matrix3_setIdentity(Matrix3 *m);

// Set up rotations.  Angles are specified in radians.  All 4 of these
// functions completely reset/initialize the contents of the matrix.
void Matrix3_setupRotateX(Matrix3 *m, float angle);
void Matrix3_setupRotateY(Matrix3 *m, float angle);
void Matrix3_setupRotateZ(Matrix3 *m, float angle);
void Matrix3_setupRotateAxisAngle(Matrix3 *m, const Vector3 *axis, float angle);

void Matrix3_makeTranspose(Matrix3 *dst, const Matrix3 *m);
void Matrix3_concatenate(Matrix3 *dst, const Matrix3 *a, const Matrix3 *b);

#pragma mark Matrix4

void Matrix4_setIdentity(Matrix4 *m);

// Initialize the matrix using a rotation matrix and a translation
void Matrix4_setMatrix(Matrix4 *dst, const Matrix3 *rotate, const Vector3 *translate);

// Wipe out the translation portion of the matrix
void Matrix4_zeroTranslation(Matrix4 *dst);
void Matrix4_setTranslation(Matrix4 *dst, const Vector3 *translate);

// Initialize a matrix to be a translation matrix.  E.g., set it to identity
// first, then set the translation portion.
void Matrix4_setupTranslation(Matrix4 *dst, const Vector3 *translate);

// Set up rotations.  Angle is specified in radians.  Each of these
// will set the translation term to 0.
void Matrix4_setupRotateX(Matrix4 *dst, float angle);
void Matrix4_setupRotateY(Matrix4 *dst, float angle);
void Matrix4_setupRotateZ(Matrix4 *dst, float angle);
void Matrix4_setupRotateAxisAngle(Matrix4 *dst, const Vector3 *axis, float angle);

// Set up as an OpenGL-style perspective projection matrix
// (e.g. glFrustum)
void Matrix4_setupFrustum(Matrix4 *dst, float left, float right, float bottom, float top, float clipNear, float clipFar);

// Get information back out of the thing
void Matrix4_getRotateMatrix(Matrix3 *rotate, const Matrix4 *m);
void Matrix4_getTranslation(Vector3 *translate, const Matrix4 *m);

// Useful properties of the matrix
float Matrix4_determinant(const Matrix4 *m);
void  Matrix4_inverse(Matrix4 *dst, const Matrix4 *m);

void  Matrix4_concatenate(Matrix4 *dst, const Matrix4 *a, const Matrix4 *b);
void  Matrix4_transform(Vector3 *dst, const Matrix4 *m, const Vector3 *v);

#endif /* include guard */
