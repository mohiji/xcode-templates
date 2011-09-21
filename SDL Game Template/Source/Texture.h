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

class Texture
{
public:
	Texture();
	~Texture();
	
	// Dimensions of the texture
	int width;
	int height;
	
	// OpenGL texture handle
	GLuint handle;
	
	bool loadFromFile(const char *fileName);
	
	void ensureHandle();
	void releaseHandle();
};

#endif // include guard
