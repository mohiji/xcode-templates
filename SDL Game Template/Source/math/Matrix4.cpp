/**
 * Matrix4.cpp
 * 4x4 matrices.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#include "Matrix4.h"
#include <cmath>
#include <assert.h>

const Matrix4 Matrix4::kIdentity(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

Matrix4::Matrix4(const Matrix4 &copy)
{
	m11 = copy.m11;
	m12 = copy.m12;
	m13 = copy.m13;
	m14 = copy.m14;
	
	m21 = copy.m21;
	m22 = copy.m22;
	m23 = copy.m23;
	m24 = copy.m24;
	
	m31 = copy.m31;
	m32 = copy.m32;
	m33 = copy.m33;
	m34 = copy.m34;
	
	m41 = copy.m41;
	m42 = copy.m42;
	m43 = copy.m43;
	m44 = copy.m44;
}

Matrix4::Matrix4(float _11, float _12, float _13, float _14,
				 float _21, float _22, float _23, float _24,
				 float _31, float _32, float _33, float _34,
				 float _41, float _42, float _43, float _44)
{
	m11 = _11;
	m12 = _12;
	m13 = _13;
	m14 = _14;
	
	m21 = _21;
	m22 = _22;
	m23 = _23;
	m24 = _24;
	
	m31 = _31;
	m32 = _32;
	m33 = _33;
	m34 = _34;
	
	m41 = _41;
	m42 = _42;
	m43 = _43;
	m44 = _44;
}

Matrix4::Matrix4(const Matrix3 &rotate, const Vector3 &translate)
{
	m11 = rotate.m11;
	m12 = rotate.m12;
	m13 = rotate.m13;
	m14 = 0.0f;
	
	m21 = rotate.m21;
	m22 = rotate.m22;
	m23 = rotate.m23;
	m24 = 0.0f;
	
	m31 = rotate.m31;
	m32 = rotate.m32;
	m33 = rotate.m33;
	m34 = 0.0f;
	
	m41 = translate.x;
	m42 = translate.y;
	m43 = translate.z;
	m44 = 1.0f;
}

Matrix4& Matrix4::operator= (const Matrix4 &copy)
{
	m11 = copy.m11;
	m12 = copy.m12;
	m13 = copy.m13;
	m14 = copy.m14;
	
	m21 = copy.m21;
	m22 = copy.m22;
	m23 = copy.m23;
	m24 = copy.m24;
	
	m31 = copy.m31;
	m32 = copy.m32;
	m33 = copy.m33;
	m34 = copy.m34;
	
	m41 = copy.m41;
	m42 = copy.m42;
	m43 = copy.m43;
	m44 = copy.m44;
	return *this;
}

void Matrix4::setMatrix(const Matrix3 &rotate, const Vector3 &translate)
{
	m11 = rotate.m11;
	m12 = rotate.m12;
	m13 = rotate.m13;
	m14 = 0.0f;
	
	m21 = rotate.m21;
	m22 = rotate.m22;
	m23 = rotate.m23;
	m24 = 0.0f;
	
	m31 = rotate.m31;
	m32 = rotate.m32;
	m33 = rotate.m33;
	m34 = 0.0f;
	
	m41 = translate.x;
	m42 = translate.y;
	m43 = translate.z;
	m44 = 1.0f;
}


void Matrix4::setIdentity()
{
	m11 = m22 = m33 = m44 = 1.0f;
	m12 = m13 = m14 = 0.0f;
	m21 = m23 = m24 = 0.0f;
	m31 = m32 = m34 = 0.0f;
	m41 = m42 = m43 = 0.0f;
}

void Matrix4::zeroTranslation()
{
	m41 = m42 = m43 = 0.0f;
	m44 = 1.0f;
}

void Matrix4::setTranslation(const Vector3 &v)
{
	m41 = v.x;
	m42 = v.y;
	m43 = v.z;
	m44 = 1.0f;
}

void Matrix4::setupTranslation(const Vector3 &v)
{
	setIdentity();
	setTranslation(v);
}

void Matrix4::setupRotateX(float theta)
{
	float s, c;
	s = sinf(theta);
	c = cosf(theta);
	
	setIdentity();
	m22 = c;
	m23 = s;
	m32 = -s;
	m33 = c;	
}

void Matrix4::setupRotateY(float theta)
{
	float s, c;
	s = sinf(theta);
	c = cosf(theta);
	
	setIdentity();
	m11 = c;
	m13 = -s;
	m31 = s;
	m33 = c;
}

void Matrix4::setupRotateZ(float theta)
{
	float s, c;
	s = sinf(theta);
	c = cosf(theta);
	
	setIdentity();
	m11 =c;
	m12 = s;
	m21 = -s;
	m22 = c;
}

void Matrix4::setupRotateAxisAngle(const Vector3 &axis, float theta)
{
	float s, c;
	s = sinf(theta);
	c = cosf(theta);
	
	// Pre-compute 1 - cos(radians) and some common subexpressions
	float a = 1.0f - c;
	float ax = a * axis.x;
	float ay = a * axis.y;
	float az = a * axis.z;
	
	m11 = ax * axis.x + c;
	m12 = ax * axis.y + axis.z * s;
	m13 = ax * axis.z - axis.y * s;
	m14 = 0.0f;
	
	m21 = ay * axis.x - axis.z * s;
	m22 = ay * axis.y + c;
	m23 = ay * axis.z + axis.x * s;
	m24 = 0.0f;
	
	m31 = az * axis.x + axis.y * s;
	m32 = az * axis.y - axis.x * s;
	m33 = az * axis.z + c;
	m34 = 0.0f;
	
	m41 = m42 = m43 = 0.0f;
	m44 = 1.0f;
}

/**
 * Sets the matrix up as an OpenGL style perspective projection
 * matrix.  Essentially the same as calling glFrustum
 */
void Matrix4::setupFrustum(float left, float right, float bottom, float top, float clipNear, float clipFar)
{
	m11 = (2 * clipNear) / (right - left);
	m12 = 0;
	m13 = (right + left) / (right - left);
	m14 = 0;
	m21 = 0;
	m22 = (2 * clipNear) / (top - bottom);
	m23 = (top + bottom) / (top - bottom);
	m24 = 0;
	m31 = 0;
	m32 = 0;
	m33 = -(clipFar + clipNear) / (clipFar - clipNear);
	m34 = -(2 * clipFar * clipNear) / (clipFar - clipNear);
	m41 = 0;
	m42 = 0;
	m43 = -1;
	m44 = 0;
}

Matrix3 Matrix4::getRotateMatrix() const
{
	return Matrix3(m11, m12, m13,
				   m21, m22, m23,
				   m31, m32, m33);
}

Vector3 Matrix4::getTranslation() const
{
	return Vector3(m41, m42, m43);
}

/* The determinant() and inverse() functions are borrowed from
 * the Geometric Tools library (http://www.geometrictools.com/)
 */
float Matrix4::determinant() const
{	
	float fA0 = m11*m22 - m12*m21;
    float fA1 = m11*m23 - m13*m21;
    float fA2 = m11*m24 - m14*m21;
    float fA3 = m12*m23 - m13*m22;
    float fA4 = m12*m24 - m14*m22;
    float fA5 = m13*m24 - m14*m23;
    float fB0 = m31*m42 - m32*m41;
    float fB1 = m31*m43 - m33*m41;
    float fB2 = m31*m44 - m34*m41;
    float fB3 = m32*m43 - m33*m42;
    float fB4 = m32*m44 - m34*m42;
    float fB5 = m33*m44 - m34*m43;
    float fDet = fA0*fB5-fA1*fB4+fA2*fB3+fA3*fB2-fA4*fB1+fA5*fB0;
    return fDet;
}

Matrix4 Matrix4::inverse() const
{
	float fA0 = m11*m22 - m12*m21;
    float fA1 = m11*m23 - m13*m21;
    float fA2 = m11*m24 - m14*m21;
    float fA3 = m12*m23 - m13*m22;
    float fA4 = m12*m24 - m14*m22;
    float fA5 = m13*m24 - m14*m23;
    float fB0 = m31*m42 - m32*m41;
    float fB1 = m31*m43 - m33*m41;
    float fB2 = m31*m44 - m34*m41;
    float fB3 = m32*m43 - m33*m42;
    float fB4 = m32*m44 - m34*m42;
    float fB5 = m33*m44 - m34*m43;
    float fDet = fA0*fB5-fA1*fB4+fA2*fB3+fA3*fB2-fA4*fB1+fA5*fB0;
    
	assert(fabs(fDet) >= 0.000001f);
	
    Matrix4 kInv;
    kInv.m11 = + m22*fB5 - m23*fB4 + m24*fB3;
    kInv.m21 = - m21*fB5 + m23*fB2 - m24*fB1;
    kInv.m31 = + m21*fB4 - m22*fB2 + m24*fB0;
    kInv.m41 = - m21*fB3 + m22*fB1 - m23*fB0;
    kInv.m12 = - m12*fB5 + m13*fB4 - m14*fB3;
    kInv.m22 = + m11*fB5 - m13*fB2 + m14*fB1;
    kInv.m32 = - m11*fB4 + m12*fB2 - m14*fB0;
    kInv.m42 = + m11*fB3 - m12*fB1 + m13*fB0;
    kInv.m13 = + m42*fA5 - m43*fA4 + m44*fA3;
    kInv.m23 = - m41*fA5 + m43*fA2 - m44*fA1;
    kInv.m33 = + m41*fA4 - m42*fA2 + m44*fA0;
    kInv.m43 = - m41*fA3 + m42*fA1 - m43*fA0;
    kInv.m14 = - m32*fA5 + m33*fA4 - m34*fA3;
    kInv.m24 = + m31*fA5 - m33*fA2 + m34*fA1;
    kInv.m34 = - m31*fA4 + m32*fA2 - m34*fA0;
    kInv.m44 = + m31*fA3 - m32*fA1 + m33*fA0;
	
    float fInvDet = ((float)1.0)/fDet;
    kInv.m11 *= fInvDet;
    kInv.m12 *= fInvDet;
    kInv.m13 *= fInvDet;
    kInv.m14 *= fInvDet;
    kInv.m21 *= fInvDet;
    kInv.m22 *= fInvDet;
    kInv.m23 *= fInvDet;
    kInv.m24 *= fInvDet;
    kInv.m31 *= fInvDet;
    kInv.m32 *= fInvDet;
    kInv.m33 *= fInvDet;
    kInv.m34 *= fInvDet;
    kInv.m41 *= fInvDet;
    kInv.m42 *= fInvDet;
    kInv.m43 *= fInvDet;
    kInv.m44 *= fInvDet;
	
    return kInv;
}

void Matrix4::printMatrix(const char *description) const
{
	puts(description);
	printf("   %.4f   %.4f   %.4f   %.4f\n", m11, m12, m13, m14);
	printf("   %.4f   %.4f   %.4f   %.4f\n", m21, m22, m23, m24);
	printf("   %.4f   %.4f   %.4f   %.4f\n", m31, m32, m33, m34);
	printf("   %.4f   %.4f   %.4f   %.4f\n", m41, m42, m43, m44);
	
}

/* Non-member operators */
Vector3 operator* (const Vector3 &v, const Matrix4 &m)
{
	return Vector3(v.x * m.m11 + v.y * m.m21 + v.z * m.m31 + m.m41,
				   v.x * m.m12 + v.y * m.m22 + v.z * m.m32 + m.m42,
				   v.x * m.m13 + v.y * m.m23 + v.z * m.m33 + m.m43);	
}

Vector3& operator*=(Vector3 &v, const Matrix4 &m)
{
	v = v * m;
	return v;
}

Matrix4 operator* (const Matrix4 &a, const Matrix4 &b)
{
	Matrix4 r;
	r.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41;
	r.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42;
	r.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43;
	r.m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44;
	
	r.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41;
	r.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42;
	r.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43;
	r.m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44;
	
	r.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41;
	r.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42;
	r.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43;
	r.m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44;
	
	r.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41;
	r.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42;
	r.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43;
	r.m44 = a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44;
	
	return r;
}

Matrix4& operator*=(Matrix4 &a, const Matrix4 &b)
{
	a = a * b;
	return a;
}
