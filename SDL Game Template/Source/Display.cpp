/**
 * Display.cpp
 *
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
 */

#include "Display.h"
#include <cstddef>
#include <SDL.h>

// Keep track of the primary display surface.  Used simply to determine
// whether or not a window is currently open.
static SDL_Surface *g_displaySurface = NULL;

bool Display_Open(const char *title, int width, int height, int bitdepth, int fullscreen)
{
	Uint32 flags;
	SDL_Event e;
	
	if (g_displaySurface != NULL)
	{
		// A window is already open, bail out.  If you want to switch
		// resolutions, call Display_Close() first.
		return false;
	}
	
	// Let SDL do it's basic initialization stuff
	if(SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}
	
	switch(bitdepth)
	{
		case 32:
		case 24:
		default:
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
			break;
			
		case 16:
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
			break;
			
		case 15:
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
			break;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	// Set the window title before setting the display mode, so that you never
	// see that SDL_display title
	SDL_WM_SetCaption(title, title);
	
	flags = SDL_OPENGL;
	if(fullscreen) flags |= SDL_FULLSCREEN;
	
	g_displaySurface = SDL_SetVideoMode(width, height, bitdepth, flags);
	if(!g_displaySurface)
	{
		return false;
	}
	
	// SDL generates a couple of mouse movements right when  it starts up, 
	// because it moves the cursor to the middle of the screen.  Eat those here
	// so that they don't cause any jumping once the game starts
	while(SDL_PollEvent(&e));
	
	return true;
}

void Display_Close()
{
	if (g_displaySurface != NULL)
	{
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		g_displaySurface = NULL;
	}
}
