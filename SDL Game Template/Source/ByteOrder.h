/**
 * ByteOrder.h
 * Make sure your endian-ness is right.
 *
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
 */

#ifndef ByteOrder_h
#define ByteOrder_h

#include <stdint.h>

uint32_t LittleInt32ToHost(uint32_t i);
uint16_t LittleInt16ToHost(uint16_t i);
float LittleFloatToHost(float f);

#endif /* include guard */
