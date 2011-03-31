/**
 * Utility.cpp
 * Handy helper functions.
 *
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
 */

#include "Utility.h"

int NearestPowerOfTwo(int n)
{
	int value = 1;
	while (value < n) value *= 2;
	
	return value;
}
