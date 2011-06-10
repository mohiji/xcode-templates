/**
 * MathUtil.h
 * Quick utility functions.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#ifndef MathUtil_h
#define MathUtil_h

#include <math.h>

inline float RadiansToDegrees(float radians) {
	return radians * (180.0f / M_PI);
}

inline float DegreesToRadians(float degrees) {
	return degrees * (M_PI / 180.0F);
}

#endif /* include guard */
