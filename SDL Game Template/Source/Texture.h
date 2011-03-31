/**
 * Texture.h
 * Uses SDL_image to load textures for OpenGL.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
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
