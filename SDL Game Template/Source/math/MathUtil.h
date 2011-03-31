/**
 * MathUtil.h
 * Quick utility functions.
 *
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
 */

#ifndef MathUtil_h
#define MathUtil_h

#include <cmath>

inline float RadiansToDegrees(float radians) {
	return radians * (180.0f / M_PI);
}

inline float DegreesToRadians(float degrees) {
	return degrees * (M_PI / 180.0F);
}

#endif /* include guard */
