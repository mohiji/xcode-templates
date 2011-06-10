/**
 * Utility.c
 * Handy helper functions.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#include "Utility.h"

int NearestPowerOfTwo(int n)
{
	int value = 1;
	while (value < n) value *= 2;
	
	return value;
}
