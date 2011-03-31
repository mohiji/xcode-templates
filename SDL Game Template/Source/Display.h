/**
 * Display.cpp
 * Interface for opening and closing the display window.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#ifndef Display_h
#define Display_h

bool Display_Open(const char *title, int width, int height, int bitdepth, int fullscreen);
void Display_Close();

#endif /* include guard */
