/**
 * VectorMath.c
 * 2 and 3 component vectors.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#include "VectorMath.h"
#include <stddef.h>
#include <math.h>
#include <assert.h>

#pragma mark Vector2

Vector2 Vector2_new(float x, float y)
{
    Vector2 v;
    v.x = x;
    v.y = y;
    return v;
}

void Vector2_add(Vector2 *dst, const Vector2 *a, const Vector2 *b)
{
    assert (dst != NULL);
    assert (a != NULL && b != NULL);
	
    dst->x = a->x + b->x;
    dst->y = a->y + b->y;
}

void Vector2_sub(Vector2 *dst, const Vector2 *a, const Vector2 *b)
{
    assert (dst != NULL);
    assert (a != NULL && b != NULL);
	
    dst->x = a->x - b->x;
    dst->y = a->y - b->y;
}

void Vector2_scale(Vector2 *dst, const Vector2 *v, float scalar)
{
    assert (dst != NULL);
    assert (v != NULL);
	
    dst->x = v->x * scalar;
    dst->y = v->y * scalar;
}

float Vector2_magnitude(const Vector2 *v)
{
    assert (v != NULL);
    return sqrtf(v->x * v->x + v->y * v->y);
}

float Vector2_magnitudeSquared(const Vector2 *v)
{
    assert (v != NULL);
    return (v->x * v->x + v->y * v->y);
}

void Vector2_normal(Vector2 *dst, const Vector2 *v)
{
    assert (dst != NULL);
    assert (v != NULL);
	
    float magnitude = Vector2_magnitude(v);
    if (magnitude == 0.0f)
    {
        // Avoid a divide by zero here
        dst->x = dst->y = 0.0f;
    } else
    {
        Vector2_scale(dst, v, 1.0f / magnitude);
    }
}

float Vector2_dotProduct(const Vector2 *a, const Vector2 *b)
{
    assert (a != NULL && b != NULL);
    return a->x * b->x + a->y * b->y;
}

/* Used in doing line intersections, the dotPerp operation is defined here:
 http://www.geometrictools.com/Documentation/IntersectionLine2Circle2.pdf
 */
float Vector2_dotPerp(const Vector2 *a, const Vector2 *b)
{
    assert (a != NULL && b != NULL);
    return a->x * b->y - a->y * b->x;
}

void Vector2_rotate(Vector2 *dst, const Vector2 *v, float theta)
{
    assert (dst != NULL);
    assert (v != NULL);
	
    float c = cosf(theta);
    float s = sinf(theta);
	
    dst->x = v->x * c - v->y * s;
    dst->y = v->x * s + v->y * c;
}

void Vector2_reflect(Vector2 *dst, const Vector2 *v, const Vector2 *n)
{
    assert (dst != NULL);
    assert (v != NULL && n != NULL);
	
    float dp = Vector2_dotProduct(n, v);
    Vector2_scale(dst, n, 2.0f * dp);
    Vector2_sub(dst, dst, v);
}

#pragma mark Vector3

Vector3 Vector3_new(float x, float y, float z)
{
    Vector3 v;
    v.x = x;
    v.y = y;
	v.z = z;
    return v;
}

void Vector3_add(Vector3 *dst, const Vector3 *a, const Vector3 *b)
{
    assert (dst != NULL);
    assert (a != NULL && b != NULL);
	
    dst->x = a->x + b->x;
    dst->y = a->y + b->y;
	dst->z = a->z + b->z;
}

void Vector3_sub(Vector3 *dst, const Vector3 *a, const Vector3 *b)
{
    assert (dst != NULL);
    assert (a != NULL && b != NULL);
	
    dst->x = a->x - b->x;
    dst->y = a->y - b->y;
	dst->z = a->z - b->z;
}

void Vector3_scale(Vector3 *dst, const Vector3 *v, float scalar)
{
    assert (dst != NULL);
    assert (v != NULL);
	
    dst->x = v->x * scalar;
    dst->y = v->y * scalar;
	dst->z = v->z * scalar;
}

float Vector3_magnitude(const Vector3 *v)
{
    assert (v != NULL);
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

float Vector3_magnitudeSquared(const Vector3 *v)
{
    assert (v != NULL);
    return (v->x * v->x + v->y * v->y + v->z * v->z);
}

void Vector3_normal(Vector3 *dst, const Vector3 *v)
{
    assert (dst != NULL);
    assert (v != NULL);
	
    float magnitude = Vector3_magnitude(v);
    if (magnitude == 0.0f)
    {
        // Avoid a divide by zero here
        dst->x = dst->y = dst->z = 0.0f;
    } else
    {
        Vector3_scale(dst, v, 1.0f / magnitude);
    }
}
