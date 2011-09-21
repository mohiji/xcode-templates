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

class SimpleFont
{
public:
	SimpleFont();
	~SimpleFont();
	
	bool loadFromFile(const char *filename, int pointSize);
	void drawFormattedText(float x, float y, const char *format, ...);
	
	void ensureTextureHandle();
	void releaseTextureHandle();
	
private:
	TTF_Font *ttfFont_;
	GLuint    textureHandle_;
	GLfloat   textureCoordinates_[4];
};

#endif /* include guard */

