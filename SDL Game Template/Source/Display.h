/**
 * Display.cpp
 * Interface for opening and closing the display window.
 *
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
 */

#ifndef Display_h
#define Display_h

bool Display_Open(const char *title, int width, int height, int bitdepth, int fullscreen);
void Display_Close();

#endif /* include guard */
