/**
 * VectorMath.h
 * 2 and 3 component geometric vectors
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#ifndef VectorMath_h
#define VectorMath_h

typedef struct Vector2_s
{
	float x, y;
}Vector2;

typedef struct Vector3_s
{
	float x, y, z;
}Vector3;

Vector2 Vector2_new(float x, float y);
void    Vector2_add(Vector2 *dst, const Vector2 *a, const Vector2 *b);
void    Vector2_sub(Vector2 *dst, const Vector2 *a, const Vector2 *b);
void    Vector2_scale(Vector2 *dst, const Vector2 *v, float scalar);
float   Vector2_magnitude(const Vector2 *v);
float   Vector2_magnitudeSquared(const Vector2 *v);
void    Vector2_normal(Vector2 *dst, const Vector2 *v);
float   Vector2_dotProduct(const Vector2 *v1, const Vector2 *v2);
float   Vector2_dotPerp(const Vector2 *v1, const Vector2 *v2);
void    Vector2_rotate(Vector2 *dst, const Vector2 *v, float theta);
void    Vector2_reflect(Vector2 *dst, const Vector2 *v, const Vector2 *n);

Vector3 Vector3_new(float x, float y, float z);
void    Vector3_add(Vector3 *dst, const Vector3 *a, const Vector3 *b);
void    Vector3_sub(Vector3 *dst, const Vector3 *a, const Vector3 *b);
void    Vector3_scale(Vector3 *dst, const Vector3 *v, float scalar);
float   Vector3_magnitude(const Vector3 *v);
float   Vector3_magnitudeSquared(const Vector3 *v);
void    Vector3_normal(Vector3 *dst, const Vector3 *v);
float   Vector3_dotProduct(const Vector3 *v1, const Vector3 *v2);
void    Vector3_crossProduct(Vector3 *dst, const Vector3 *a, const Vector3 *b);

#endif /* include guard */
