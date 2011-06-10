/**
 * Matrix3.c
 * 3x3 matrices.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#include "MatrixMath.h"
#include <stddef.h>
#include <math.h>
#include <assert.h>

void Matrix3_setIdentity(Matrix3 *m)
{
	assert (m != NULL);
	
	m->m11 = m->m22 = m->m33 = 1.0f;
	m->m12 = m->m13 = 0.0f;
	m->m21 = m->m23 = 0.0f;
	m->m31 = m->m32 = 0.0f;
}

void Matrix3_setupRotateX(Matrix3 *m, float angle)
{
	float s, c;
	assert (m != NULL);
	
	s = sinf(angle);
	c = cosf(angle);
	
	Matrix3_setIdentity(m);
	m->m22 = c;
	m->m23 = s;
	m->m32 = -s;
	m->m33 = c;
}

void Matrix3_setupRotateY(Matrix3 *m, float angle)
{
	float s, c;
	assert (m != NULL);
	
	s = sinf(angle);
	c = cosf(angle);
	
	Matrix3_setIdentity(m);
	m->m11 = c;
	m->m13 = -s;
	m->m31 = s;
	m->m33 = c;
}

void Matrix3_setupRotateZ(Matrix3 *m, float angle)
{
	float s, c;
	assert (m != NULL);
	
	s = sinf(angle);
	c = cosf(angle);
	
	Matrix3_setIdentity(m);
	m->m11 =c;
	m->m12 = s;
	m->m21 = -s;
	m->m22 = c;
}

void Matrix3_setupRotateAxisAngle(Matrix3 *m, const Vector3 *axis, float angle)
{
	float s, c;
	assert (m != NULL);
	
	s = sinf(angle);
	c = cosf(angle);
	
	// Pre-compute 1 - cos(radians) and some common subexpressions
	float a = 1.0f - c;
	float ax = a * axis->x;
	float ay = a * axis->y;
	float az = a * axis->z;
	
	m->m11 = ax * axis->x + c;
	m->m12 = ax * axis->y + axis->z * s;
	m->m13 = ax * axis->z - axis->y * s;
	
	m->m21 = ay * axis->x - axis->z * s;
	m->m22 = ay * axis->y + c;
	m->m23 = ay * axis->z + axis->x * s;
	
	m->m31 = az * axis->x + axis->y * s;
	m->m32 = az * axis->y - axis->x * s;
	m->m33 = az * axis->z + c;
}

void Matrix3_makeTranspose(Matrix3 *dst, const Matrix3 *m)
{
	assert (dst != NULL && m != NULL);
	
	dst->m11 = m->m11;
	dst->m12 = m->m21;
	dst->m13 = m->m31;
	
	dst->m21 = m->m12;
	dst->m22 = m->m22;
	dst->m23 = m->m32;
	
	dst->m31 = m->m13;
	dst->m32 = m->m23;
	dst->m33 = m->m33;
}

void Matrix3_concatenate(Matrix3 *dst, const Matrix3 *a, const Matrix3 *b)
{
	assert (dst != NULL && a != NULL && b != NULL);
	
	dst->m11 = a->m11 * b->m11 + a->m12 * b->m21 + a->m13 * b->m31;
	dst->m12 = a->m11 * b->m12 + a->m12 * b->m22 + a->m13 * b->m32;
	dst->m13 = a->m11 * b->m13 + a->m12 * b->m23 + a->m13 * b->m33;
	
	dst->m21 = a->m21 * b->m11 + a->m22 * b->m21 + a->m23 * b->m31;
	dst->m22 = a->m21 * b->m12 + a->m22 * b->m22 + a->m23 * b->m32;
	dst->m23 = a->m21 * b->m13 + a->m22 * b->m23 + a->m23 * b->m33;
	
	dst->m31 = a->m31 * b->m11 + a->m32 * b->m21 + a->m33 * b->m31;
	dst->m32 = a->m31 * b->m12 + a->m32 * b->m22 + a->m33 * b->m32;
	dst->m33 = a->m31 * b->m13 + a->m32 * b->m23 + a->m33 * b->m33;
}
