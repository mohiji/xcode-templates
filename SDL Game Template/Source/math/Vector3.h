/**
 * Vector3.h
 * 3-component vector class.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#ifndef Vector3_h
#define Vector3_h

struct Vector3
{
    float x, y, z;

    // Default constructor leaves the vector un-initialized
	Vector3() {}
	Vector3(float x, float y, float z);
	Vector3(const Vector3 &copy);
	
	Vector3& operator= (const Vector3 &other);
	Vector3& operator+=(const Vector3 &other);
	Vector3& operator-=(const Vector3 &other);
	Vector3& operator*=(float scalar);
	Vector3& operator/=(float scalar);
};

// Arithmetic operations
Vector3 operator+ (const Vector3 &a, const Vector3 &b);
Vector3 operator- (const Vector3 &a, const Vector3 &b);
Vector3 operator* (const Vector3 &a, float scalar);
Vector3 operator* (float scalar, const Vector3 &a);
Vector3 operator/ (const Vector3 &a, float divisor);

// Other operations
float   Magnitude(const Vector3 &v);
float   MagnitudeSquared(const Vector3 &v);
Vector3 Normal(const Vector3 &v);
float   DotProduct(const Vector3 &a, const Vector3 &b);
Vector3 CrossProduct(const Vector3 &a, const Vector3 &b);

#endif /* include guard */
