/**
 * Vector2.h
 * 2-component vector class.
 *
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
 */


#include "Vector2.h"
#include <assert.h>
#include <cmath>

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2::Vector2(const Vector2 &copy)
{
	x = copy.x;
	y = copy.y;
}

Vector2& Vector2::operator= (const Vector2 &other)
{
	x = other.x;
	y = other.y;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2 &other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2 &other)
{
	x -= other.x;
	y -= other.y;
	return *this;	
}

Vector2& Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
	assert(scalar != 0.0f);
	x /= scalar;
	y /= scalar;
	return *this;
}
	
Vector2 operator+ (const Vector2 &a, const Vector2 &b)
{
	return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 operator- (const Vector2 &a, const Vector2 &b)
{
	return Vector2(a.x - b.x, a.y - b.y);
}

Vector2 operator* (const Vector2 &a, float scalar)
{
	return Vector2(a.x * scalar, a.y * scalar);
}

Vector2 operator* (float scalar, const Vector2 &a)
{
	return Vector2(a.x * scalar, a.y * scalar);
}

Vector2 operator/ (const Vector2 &a, float divisor)
{
	assert(divisor != 0.0f);
	return Vector2(a.x / divisor, a.y / divisor);
}

float Magnitude(const Vector2 &v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

float MagnitudeSquared(const Vector2 &v)
{
    return v.x * v.x + v.y * v.y;
}

Vector2 Normal(const Vector2 &v)
{
    float mag = Magnitude(v);
    if (mag == 0.0f) return Vector2(0, 0);
    else return v / mag;
}

float DotProduct(const Vector2 &a, const Vector2 &b)
{
    return a.x * b.x + a.y * b.y;
}

// dot-perp operation defined in:
// http://www.geometrictools.com/Documentation/IntersectionLine2Circle2.pdf
float DotPerp(const Vector2 &a, const Vector2 &b)
{
    return a.x * b.y - a.y * b.x;
}

Vector2 Reflect(const Vector2 &V, const Vector2 &N)
{
    return (2 * DotProduct(N, V)) * N - V;
}
