/**
 * Vector2.h
 * 2-component vector class.
 *
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
 */

#ifndef Vector2_h
#define Vector2_h

struct Vector2
{
	float x, y;
	
	// Default constructor leaves the vector un-initialized
	Vector2() {}
	Vector2(float x, float y);
	Vector2(const Vector2 &copy);
	
	Vector2& operator= (const Vector2 &other);
	Vector2& operator+=(const Vector2 &other);
	Vector2& operator-=(const Vector2 &other);
	Vector2& operator*=(float scalar);
	Vector2& operator/=(float scalar);
};

// Arithmetic operations
Vector2 operator+ (const Vector2 &a, const Vector2 &b);
Vector2 operator- (const Vector2 &a, const Vector2 &b);
Vector2 operator* (const Vector2 &a, float scalar);
Vector2 operator* (float scalar, const Vector2 &a);
Vector2 operator/ (const Vector2 &a, float divisor);

// Other operations
float   Magnitude(const Vector2 &v);
float   MagnitudeSquared(const Vector2 &v);
Vector2 Normal(const Vector2 &v);
float   DotProduct(const Vector2 &a, const Vector2 &b);
float   DotPerp(const Vector2 &a, const Vector2 &b);

// Determine the vector resulting reflecting vector V through a
// ray with direction N
Vector2 Reflect(const Vector2 &V, const Vector2 &N);

#endif /* include guard */
