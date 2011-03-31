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

Texture::Texture()
{
	handle = 0;
	width = 0;
	height = 0;
	sourceWidth = 0;
	sourceHeight = 0;
}

Texture::~Texture()
{
	Texture_releaseHandle(this);
}

Texture* Texture_loadFromFile(const char *filename)
{
	if (!filename || !filename[0]) return NULL;
	
	int w, h;
	SDL_Surface *source, *image;
	SDL_Rect area;
	Texture *texture;
	
	// Load the texture from disk
	source = IMG_Load(filename);
	if (source == NULL)
	{
		return NULL;
	}
	
	// Use the surface width & height expanded to the next powers of two
	w = NearestPowerOfTwo(source->w);
	h = NearestPowerOfTwo(source->h);
	
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
#else
	image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
#endif
	
	if( image == NULL)
	{
		SDL_FreeSurface(source);
		return NULL;
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
	SDL_BlitSurface(source, &area, image, &area);
	
	// Don't need the extra image anymore
	SDL_FreeSurface(source);
	
	// Allocate a texture for it
	texture = new Texture();
	glGenTextures(1, &texture->handle);
	
	// Upload the texture's data to OpenGL
	glBindTexture(GL_TEXTURE_2D, texture->handle);
	
	// Save the new width/height and the source surface
	texture->width = w;
	texture->height = h;
	texture->sourceWidth = area.w;
	texture->sourceHeight = area.h;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,	0, GL_RGBA,	w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	
	SDL_FreeSurface(image);
	return texture;
}

void Texture_releaseHandle(Texture *texture)
{
	if (!texture) return;
	glDeleteTextures(1, &texture->handle);
}

