/**
 * SimpleFont.h
 * TTF font loading/drawing via SDL_ttf.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#ifndef SimpleFont_h
#define SimpleFont_h

#include <SDL_ttf.h>
#include <SDL_opengl.h>

struct SimpleFont
{
	TTF_Font *ttfFont;
	GLuint    textureHandle;
	GLfloat   textureCoordinates[4];
	
	SimpleFont();
	~SimpleFont();
	
	void ensureTextureHandle();
	void drawFormattedText(float x, float y, const char *format, ...);
	
	static SimpleFont *loadFromFile(const char *fileName, int pointSize);
};

#endif /* include guard */

