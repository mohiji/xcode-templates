/**
 * Matrix4.c
 * 4x4 matrices.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#include "MatrixMath.h"
#include <stddef.h>
#include <math.h>
#include <assert.h>

void Matrix4_setIdentity(Matrix4 *m)
{
	assert (m != NULL);
	
	m->m11 = m->m22 = m->m33 = m->m44 = 1.0f;
	m->m12 = m->m13 = m->m14 = 0.0f;
	m->m21 = m->m23 = m->m24 = 0.0f;
	m->m31 = m->m32 = m->m34 = 0.0f;
	m->m41 = m->m42 = m->m43 = 0.0f;
}

// Initialize the matrix using a rotation matrix and a translation
void Matrix4_setMatrix(Matrix4 *dst, const Matrix3 *rotate, const Vector3 *translate)
{
	assert (dst != NULL && rotate != NULL && translate != NULL);
	
	dst->m11 = rotate->m11;
	dst->m12 = rotate->m12;
	dst->m13 = rotate->m13;
	dst->m14 = 0.0f;
	
	dst->m21 = rotate->m21;
	dst->m22 = rotate->m22;
	dst->m23 = rotate->m23;
	dst->m24 = 0.0f;
	
	dst->m31 = rotate->m31;
	dst->m32 = rotate->m32;
	dst->m33 = rotate->m33;
	dst->m34 = 0.0f;
	
	dst->m41 = translate->x;
	dst->m42 = translate->y;
	dst->m43 = translate->z;
	dst->m44 = 1.0f;
}

// Wipe out the translation portion of the matrix
void Matrix4_zeroTranslation(Matrix4 *dst)
{
	assert (dst != NULL);
	
	dst->m41 = dst->m42 = dst->m43 = .0f;
	dst->m44 = 1.0f;
}

void Matrix4_setTranslation(Matrix4 *dst, const Vector3 *translate)
{
	assert (dst != NULL && translate != NULL);
	
	dst->m41 = translate->x;
	dst->m42 = translate->y;
	dst->m43 = translate->z;
	dst->m44 = 1.0f;
}

// Initialize a matrix to be a translation matrix.  E.g., set it to identity
// first, then set the translation portion.
void Matrix4_setupTranslation(Matrix4 *dst, const Vector3 *translate)
{
	Matrix4_setIdentity(dst);
	Matrix4_setTranslation(dst, translate);
}

// Set up rotations.  Angle is specified in radians.  Each of these
// will set the translation term to 0.
void Matrix4_setupRotateX(Matrix4 *dst, float angle)
{
	float s, c;
	s = sinf(angle);
	c = cosf(angle);
	
	Matrix4_setIdentity(dst);
	dst->m22 = c;
	dst->m23 = s;
	dst->m32 = -s;
	dst->m33 = c;
}

void Matrix4_setupRotateY(Matrix4 *dst, float angle)
{
	float s, c;
	s = sinf(angle);
	c = cosf(angle);
	
	Matrix4_setIdentity(dst);
	dst->m11 = c;
	dst->m13 = -s;
	dst->m31 = s;
	dst->m33 = c;
}

void Matrix4_setupRotateZ(Matrix4 *dst, float angle)
{
	float s, c;
	s = sinf(angle);
	c = cosf(angle);
	
	Matrix4_setIdentity(dst);
	dst->m11 =c;
	dst->m12 = s;
	dst->m21 = -s;
	dst->m22 = c;
}

void Matrix4_setupRotateAxisAngle(Matrix4 *dst, const Vector3 *axis, float angle)
{
	assert (dst != NULL && axis != NULL);
	
	float s, c;
	s = sinf(angle);
	c = cosf(angle);
	
	// Pre-compute 1 - cos(radians) and some common subexpressions
	float a = 1.0f - c;
	float ax = a * axis->x;
	float ay = a * axis->y;
	float az = a * axis->z;
	
	dst->m11 = ax * axis->x + c;
	dst->m12 = ax * axis->y + axis->z * s;
	dst->m13 = ax * axis->z - axis->y * s;
	dst->m14 = 0.0f;
	
	dst->m21 = ay * axis->x - axis->z * s;
	dst->m22 = ay * axis->y + c;
	dst->m23 = ay * axis->z + axis->x * s;
	dst->m24 = 0.0f;
	
	dst->m31 = az * axis->x + axis->y * s;
	dst->m32 = az * axis->y - axis->x * s;
	dst->m33 = az * axis->z + c;
	dst->m34 = 0.0f;
	
	dst->m41 = dst->m42 = dst->m43 = 0.0f;
	dst->m44 = 1.0f;
}	

// Set up as an OpenGL-style perspective projection matrix
// (e.g. glFrustum)
void Matrix4_setupFrustum(Matrix4 *dst, float left, float right, float bottom, float top, float clipNear, float clipFar)
{
	assert (dst != NULL);
	
	dst->m11 = (2 * clipNear) / (right - left);
	dst->m12 = 0;
	dst->m13 = (right + left) / (right - left);
	dst->m14 = 0;
	dst->m21 = 0;
	dst->m22 = (2 * clipNear) / (top - bottom);
	dst->m23 = (top + bottom) / (top - bottom);
	dst->m24 = 0;
	dst->m31 = 0;
	dst->m32 = 0;
	dst->m33 = -(clipFar + clipNear) / (clipFar - clipNear);
	dst->m34 = -(2 * clipFar * clipNear) / (clipFar - clipNear);
	dst->m41 = 0;
	dst->m42 = 0;
	dst->m43 = -1;
	dst->m44 = 0;
}

// Get information back out of the thing
void Matrix4_getRotateMatrix(Matrix3 *rotate, const Matrix4 *m)
{
	assert (rotate != NULL && m != NULL);
	
	rotate->m11 = m->m11;
	rotate->m12 = m->m12;
	rotate->m13 = m->m13;
	rotate->m21 = m->m21;
	rotate->m22 = m->m22;
	rotate->m23 = m->m23;
	rotate->m31 = m->m31;
	rotate->m32 = m->m32;
	rotate->m33 = m->m33;
}

void Matrix4_getTranslation(Vector3 *translate, const Matrix4 *m)
{
	assert (translate != NULL && m != NULL);
	
	translate->x = m->m41;
	translate->y = m->m42;
	translate->z = m->m43;
}

/* The determinant() and inverse() functions are borrowed from
 * the Geometric Tools library (http://www.geometrictools.com/)
 */
float Matrix4_determinant(const Matrix4 *m)
{
	assert (m != NULL);
	
	float fA0 = m->m11 * m->m22 - m->m12 * m->m21;
    float fA1 = m->m11 * m->m23 - m->m13 * m->m21;
    float fA2 = m->m11 * m->m24 - m->m14 * m->m21;
    float fA3 = m->m12 * m->m23 - m->m13 * m->m22;
    float fA4 = m->m12 * m->m24 - m->m14 * m->m22;
    float fA5 = m->m13 * m->m24 - m->m14 * m->m23;
    float fB0 = m->m31 * m->m42 - m->m32 * m->m41;
    float fB1 = m->m31 * m->m43 - m->m33 * m->m41;
    float fB2 = m->m31 * m->m44 - m->m34 * m->m41;
    float fB3 = m->m32 * m->m43 - m->m33 * m->m42;
    float fB4 = m->m32 * m->m44 - m->m34 * m->m42;
    float fB5 = m->m33 * m->m44 - m->m34 * m->m43;
    float fDet = fA0 * fB5 - fA1 * fB4 + fA2 * fB3 + fA3 * fB2 - fA4 * fB1 + fA5 * fB0;
    return fDet;
}

void  Matrix4_inverse(Matrix4 *dst, const Matrix4 *m)
{
	assert (dst != NULL && m != NULL);
	
	float fA0 = m->m11 * m->m22 - m->m12 * m->m21;
    float fA1 = m->m11 * m->m23 - m->m13 * m->m21;
    float fA2 = m->m11 * m->m24 - m->m14 * m->m21;
    float fA3 = m->m12 * m->m23 - m->m13 * m->m22;
    float fA4 = m->m12 * m->m24 - m->m14 * m->m22;
    float fA5 = m->m13 * m->m24 - m->m14 * m->m23;
    float fB0 = m->m31 * m->m42 - m->m32 * m->m41;
    float fB1 = m->m31 * m->m43 - m->m33 * m->m41;
    float fB2 = m->m31 * m->m44 - m->m34 * m->m41;
    float fB3 = m->m32 * m->m43 - m->m33 * m->m42;
    float fB4 = m->m32 * m->m44 - m->m34 * m->m42;
    float fB5 = m->m33 * m->m44 - m->m34 * m->m43;
    float fDet = fA0 * fB5 - fA1 * fB4 + fA2 * fB3 + fA3 * fB2 - fA4 * fB1 + fA5 * fB0;
	
	assert(fabs(fDet) >= 0.000001f);
	
	dst->m11 = + m->m22*fB5 - m->m23*fB4 + m->m24*fB3;
    dst->m21 = - m->m21*fB5 + m->m23*fB2 - m->m24*fB1;
    dst->m31 = + m->m21*fB4 - m->m22*fB2 + m->m24*fB0;
    dst->m41 = - m->m21*fB3 + m->m22*fB1 - m->m23*fB0;
    dst->m12 = - m->m12*fB5 + m->m13*fB4 - m->m14*fB3;
    dst->m22 = + m->m11*fB5 - m->m13*fB2 + m->m14*fB1;
    dst->m32 = - m->m11*fB4 + m->m12*fB2 - m->m14*fB0;
    dst->m42 = + m->m11*fB3 - m->m12*fB1 + m->m13*fB0;
    dst->m13 = + m->m42*fA5 - m->m43*fA4 + m->m44*fA3;
    dst->m23 = - m->m41*fA5 + m->m43*fA2 - m->m44*fA1;
    dst->m33 = + m->m41*fA4 - m->m42*fA2 + m->m44*fA0;
    dst->m43 = - m->m41*fA3 + m->m42*fA1 - m->m43*fA0;
    dst->m14 = - m->m32*fA5 + m->m33*fA4 - m->m34*fA3;
    dst->m24 = + m->m31*fA5 - m->m33*fA2 + m->m34*fA1;
    dst->m34 = - m->m31*fA4 + m->m32*fA2 - m->m34*fA0;
    dst->m44 = + m->m31*fA3 - m->m32*fA1 + m->m33*fA0;
	
	float fInvDet = ((float)1.0)/fDet;
    dst->m11 *= fInvDet;
    dst->m12 *= fInvDet;
    dst->m13 *= fInvDet;
    dst->m14 *= fInvDet;
    dst->m21 *= fInvDet;
    dst->m22 *= fInvDet;
    dst->m23 *= fInvDet;
    dst->m24 *= fInvDet;
    dst->m31 *= fInvDet;
    dst->m32 *= fInvDet;
    dst->m33 *= fInvDet;
    dst->m34 *= fInvDet;
    dst->m41 *= fInvDet;
    dst->m42 *= fInvDet;
    dst->m43 *= fInvDet;
    dst->m44 *= fInvDet;	
}

void Matrix4_concatenate(Matrix4 *dst, const Matrix4 *a, const Matrix4 *b)
{
	assert (dst != NULL && a != NULL && b != NULL);
	
	dst->m11 = a->m11 * b->m11 + a->m12 * b->m21 + a->m13 * b->m31 + a->m14 * b->m41;
	dst->m12 = a->m11 * b->m12 + a->m12 * b->m22 + a->m13 * b->m32 + a->m14 * b->m42;
	dst->m13 = a->m11 * b->m13 + a->m12 * b->m23 + a->m13 * b->m33 + a->m14 * b->m43;
	dst->m14 = a->m11 * b->m14 + a->m12 * b->m24 + a->m13 * b->m34 + a->m14 * b->m44;
	
	dst->m21 = a->m21 * b->m11 + a->m22 * b->m21 + a->m23 * b->m31 + a->m24 * b->m41;
	dst->m22 = a->m21 * b->m12 + a->m22 * b->m22 + a->m23 * b->m32 + a->m24 * b->m42;
	dst->m23 = a->m21 * b->m13 + a->m22 * b->m23 + a->m23 * b->m33 + a->m24 * b->m43;
	dst->m24 = a->m21 * b->m14 + a->m22 * b->m24 + a->m23 * b->m34 + a->m24 * b->m44;
	
	dst->m31 = a->m31 * b->m11 + a->m32 * b->m21 + a->m33 * b->m31 + a->m34 * b->m41;
	dst->m32 = a->m31 * b->m12 + a->m32 * b->m22 + a->m33 * b->m32 + a->m34 * b->m42;
	dst->m33 = a->m31 * b->m13 + a->m32 * b->m23 + a->m33 * b->m33 + a->m34 * b->m43;
	dst->m34 = a->m31 * b->m14 + a->m32 * b->m24 + a->m33 * b->m34 + a->m34 * b->m44;
	
	dst->m41 = a->m41 * b->m11 + a->m42 * b->m21 + a->m43 * b->m31 + a->m44 * b->m41;
	dst->m42 = a->m41 * b->m12 + a->m42 * b->m22 + a->m43 * b->m32 + a->m44 * b->m42;
	dst->m43 = a->m41 * b->m13 + a->m42 * b->m23 + a->m43 * b->m33 + a->m44 * b->m43;
	dst->m44 = a->m41 * b->m14 + a->m42 * b->m24 + a->m43 * b->m34 + a->m44 * b->m44;
}

void Matrix4_transform(Vector3 *dst, const Matrix4 *m, const Vector3 *v)
{
	assert (dst != NULL && m != NULL && v != NULL);
	
	dst->x = v->x * m->m11 + v->y * m->m21 + v->z * m->m31 + m->m41;
	dst->y = v->x * m->m12 + v->y * m->m22 + v->z * m->m32 + m->m42;
	dst->z = v->x * m->m13 + v->y * m->m23 + v->z * m->m33 + m->m43;
}
