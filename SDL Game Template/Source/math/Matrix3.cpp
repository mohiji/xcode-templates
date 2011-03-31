/**
 * Matrix3.cpp
 * 3x3 matrices.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#include "Matrix3.h"
#include <cmath>

const Matrix3 Matrix3::kIdentity(1, 0, 0, 0, 1, 0, 0, 0, 1);

Matrix3::Matrix3(const Matrix3 &copy)
{
	m11 = copy.m11;
	m12 = copy.m12;
	m13 = copy.m13;
	m21 = copy.m21;
	m22 = copy.m22;
	m23 = copy.m23;
	m31 = copy.m31;
	m32 = copy.m32;
	m33 = copy.m33;
}

Matrix3::Matrix3(float _11, float _12, float _13,
				 float _21, float _22, float _23,
				 float _31, float _32, float _33)
{
	m11 = _11;
	m12 = _12;
	m13 = _13;
	m21 = _21;
	m22 = _22;
	m23 = _23;
	m31 = _31;
	m32 = _32;
	m33 = _33;
}

Matrix3& Matrix3::operator= (const Matrix3 &copy)
{
	m11 = copy.m11;
	m12 = copy.m12;
	m13 = copy.m13;
	m21 = copy.m21;
	m22 = copy.m22;
	m23 = copy.m23;
	m31 = copy.m31;
	m32 = copy.m32;
	m33 = copy.m33;
	return *this;
}

void Matrix3::setIdentity()
{
	m11 = m22 = m33 = 1.0f;
	m12 = m13 = 0.0f;
	m21 = m23 = 0.0f;
	m31 = m32 = 0.0f;
}

void Matrix3::setupRotateX(float theta)
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

void Matrix3::setupRotateY(float theta)
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

void Matrix3::setupRotateZ(float theta)
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

void Matrix3::setupRotateAxisAngle(const Vector3 &axis, float theta)
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
	
	m21 = ay * axis.x - axis.z * s;
	m22 = ay * axis.y + c;
	m23 = ay * axis.z + axis.x * s;
	
	m31 = az * axis.x + axis.y * s;
	m32 = az * axis.y - axis.x * s;
	m33 = az * axis.z + c;
}

Matrix3 Matrix3::transpose() const
{
	return Matrix3(m11, m21, m31,
				   m12, m22, m32,
				   m13, m23, m33);
}

/* Vector and matrix transformations */
Vector3 operator* (const Vector3 &v, const Matrix3 &m)
{
	return Vector3(v.x * m.m11 + v.y * m.m21 + v.z * m.m31,
				   v.x * m.m12 + v.y * m.m22 + v.z * m.m32,
				   v.x * m.m13 + v.y * m.m23 + v.z * m.m33);
}

Vector3& operator*=(Vector3 &v, const Matrix3 &m)
{
	v = v * m;
	return v;
}

Matrix3 operator* (const Matrix3 &a, const Matrix3 &b)
{
	Matrix3 r;
	r.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
	r.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
	r.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;
	
	r.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
	r.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
	r.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;
	
	r.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
	r.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
	r.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
	
	return r;
}

Matrix3& operator*=(Matrix3 &a, const Matrix3 &b)
{
	a = a * b;
	return a;
}
