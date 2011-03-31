/**
 * Texture.h
 * Uses SDL_image to load textures for OpenGL.
 *
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
 */


#ifndef Texture_h
#define Texture_h

#include <SDL_opengl.h>

struct Texture
{
	GLuint handle;
	
	// Width and height of the OpenGL texture
	int width;
	int height;
	
	// Width and height of the image file that
	// the texture was loaded from.
	int sourceWidth;
	int sourceHeight;
	
	// Default constructor initializes members to nil/0
	Texture();
	~Texture();
};

Texture* Texture_loadFromFile(const char *filename);
void     Texture_releaseHandle(Texture *texture);

#endif // include guard
