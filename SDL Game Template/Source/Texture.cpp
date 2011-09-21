/**
 * Texture.cpp
 * Uses SDL_image to load textures for OpenGL.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#include "Texture.h"
#include "Utility.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <assert.h>

Texture::Texture()
{
	width = 0;
	height = 0;
	handle = 0;
}

Texture::~Texture()
{
	releaseHandle();
}

void Texture::ensureHandle()
{
	if (handle == 0)
	{
		glGenTextures(1, &handle);
	}
}

void Texture::releaseHandle()
{
	if (handle != 0)
	{
		glDeleteTextures(1, &handle);
		handle = 0;
	}
}

bool Texture::loadFromFile(const char *filename)
{
	if (!filename || !filename[0]) return false;
	
	int w, h;
	SDL_Surface *source, *converted;
	SDL_Rect area;
	
	source = IMG_Load(filename);
	if (source == NULL)
	{
		return false;
	}
	
	// Make sure that the texture is in a format OpenGL will be happy with
	w = source->w;
	h = source->h;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	converted = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
#else
	converted = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
#endif
	
	if (converted == NULL)
	{
		SDL_FreeSurface(source);
		return false;
	}
	
	// Turn off source alpha on this image if it's on
	if ( (source->flags & SDL_SRCALPHA) == SDL_SRCALPHA )
	{
		SDL_SetAlpha(source, 0, 0);
	}
	
	// Copy the surface into the texture image
	area.x = 0;
	area.y = 0;
	area.w = source->w;
	area.h = source->h;
	SDL_BlitSurface(source, &area, converted, &area);
	
	// Don't need the original image anymore
	SDL_FreeSurface(source);
	
	ensureHandle();
	assert (handle != 0);
	
	// Upload the texture data to OpenGL
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,	0, GL_RGBA,	w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, converted->pixels);
	
	SDL_FreeSurface(converted);
	width = w;
	height = h;
	return true;
}

