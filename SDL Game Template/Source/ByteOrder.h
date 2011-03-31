/**
 * ByteOrder.h
 * Make sure your endian-ness is right.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#ifndef ByteOrder_h
#define ByteOrder_h

#include <stdint.h>

uint32_t LittleInt32ToHost(uint32_t i);
uint16_t LittleInt16ToHost(uint16_t i);
float LittleFloatToHost(float f);

#endif /* include guard */
