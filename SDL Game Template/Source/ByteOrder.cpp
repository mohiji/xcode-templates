/**
 * ByteOrder.h
 * Make sure your endian-ness is right.
 *
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
 */

#include "ByteOrder.h"
#include <SDL_endian.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
float LittleFloatToHost(float f)
{
	union
	{
		float f32;
		uint32_t u32;
	} u;
	
	u.f32 = f;
	u.u32 = SDL_Swap32(u.u32);
	return u.f32;
}

uint32_t LittleInt32ToHost(uint32_t i)
{
	return SDL_Swap32(i);
}

uint16_t LittleInt16ToHost(uint16_t i)
{
	return SDL_Swap16(i);
}

#else

float LittleFloatToHost(float f) {
	return f;
}

uint32_t LittleInt32ToHost(uint32_t i)
{
	return i;
}

uint16_t LittleInt16ToHost(uint16_t i)
{
	return i;
}
#endif