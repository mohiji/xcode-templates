/**
 * Vector3.h
 * 3-component vector class.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#include "Vector3.h"
#include <cmath>

Vector3::Vector3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Vector3::Vector3(const Vector3 &copy)
{
    x = copy.x;
    y = copy.y;
    z = copy.z;
}

Vector3& Vector3::operator= (const Vector3 &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

Vector3& Vector3::operator+=(const Vector3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3& Vector3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3& Vector3::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

Vector3 operator+ (const Vector3 &a, const Vector3 &b)
{
    return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 operator- (const Vector3 &a, const Vector3 &b)
{
    return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3 operator* (const Vector3 &v, float scalar)
{
    return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
}

Vector3 operator* (float scalar, const Vector3 &v)
{
    return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
}

Vector3 operator/ (const Vector3 &a, float divisor)
{
    return Vector3(a.x / divisor, a.y / divisor, a.z / divisor);
}

float Magnitude(const Vector3 &v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float MagnitudeSquared(const Vector3 &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

Vector3 Normal(const Vector3 &v)
{
    float magnitude = Magnitude(v);
    return v / magnitude;
}

float DotProduct(const Vector3 &a, const Vector3 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 CrossProduct(const Vector3 &a, const Vector3 &b)
{
    return Vector3(a.y * b.z - a.z * b.y,
                   a.x * b.z - a.z * b.x,
                   a.x * b.y - a.y * b.x);
}
