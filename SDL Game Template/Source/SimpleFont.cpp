/**
 * SimpleFont.cpp
 * TTF font loading/drawing via SDL_ttf.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#include "SimpleFont.h"
#include "Utility.h"
#include <SDL_opengl.h>

static const SDL_Color kTextColor = { 0xff, 0xff, 0xff, 0 };
static const int kSimpleFontMaxTextLength = 501;
static char textFormatBuffer[kSimpleFontMaxTextLength];

static void ensureInitialized()
{
	if (!TTF_WasInit())
	{
		TTF_Init();
	}
}

// The following function was copied from the gl_font.c file included with SDL_ttf
static int copySurfaceToTexture(SDL_Surface *surface, GLfloat *texCoords)
{
	int w, h;
	SDL_Surface *image;
	SDL_Rect area;
	Uint32 saved_flags;
	Uint8 saved_alpha;
	
	// Use the surface width & height expanded to the next powers of two
	w = NearestPowerOfTwo(surface->w);
	h = NearestPowerOfTwo(surface->h);
	texCoords[0] = 0.0f;
	texCoords[1] = 0.0f;
	texCoords[2] = (GLfloat)surface->w / w;
	texCoords[3] = (GLfloat)surface->h / h;
	
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
#else
	image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
#endif
	
	if(image == NULL)
	{
		return 0;
	}
	
	// Save the alpha blending attributes
	saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
	saved_alpha = surface->format->alpha;
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA )
	{
		SDL_SetAlpha(surface, 0, 0);
	}
	
	// Copy the surface into the texture image
	area.x = 0;
	area.y = 0;
	area.w = surface->w;
	area.h = surface->h;
	SDL_BlitSurface(surface, &area, image, &area);
	
	// Restore the blending attributes
	if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA )
	{
		SDL_SetAlpha(surface, saved_flags, saved_alpha);
	}
	
	// Send the texture to OpenGL
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,	0, GL_RGBA,	w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,	image->pixels);
	
	// Don't need the extra image anymore
	SDL_FreeSurface(image);
	
	return 1;
}

SimpleFont::SimpleFont()
{
	ttfFont_ = NULL;
	textureHandle_ = 0;
}

SimpleFont::~SimpleFont()
{
	if (ttfFont_ != NULL)
	{
		TTF_CloseFont(ttfFont_);
	}
	
	if (textureHandle_ != 0)
	{
		glDeleteTextures(1, &textureHandle_);
	}
}

bool SimpleFont::loadFromFile(const char *fileName, int pointSize)
{
	ensureInitialized();
	
	if (ttfFont_ != NULL)
	{
		TTF_CloseFont(ttfFont_);
		ttfFont_ = NULL;
	}
	
	ttfFont_ = TTF_OpenFont(fileName, pointSize);
	if (ttfFont_ == NULL)
	{
		return false;
	}
	
	return true;
}

void SimpleFont::drawFormattedText(float x, float y, const char *format, ...)
{
	SDL_Surface *textSurface;
	
	if (ttfFont_ == NULL) return;
	
	// Make sure the caller actually passed in a string.
	if (format == NULL || format[0] == 0) return;
	
	va_list args;
	va_start(args, format);
	vsnprintf(textFormatBuffer, kSimpleFontMaxTextLength, format, args);
	va_end(args);
	
	textSurface = TTF_RenderText_Blended(ttfFont_, textFormatBuffer, kTextColor);
	
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	this->ensureTextureHandle();
	if (copySurfaceToTexture(textSurface, textureCoordinates_))
	{
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(textureCoordinates_[0], textureCoordinates_[1]);
		glVertex2f(x, y + textSurface->h);
		glTexCoord2f(textureCoordinates_[2], textureCoordinates_[1]);
		glVertex2f(x + textSurface->w, y + textSurface->h);
		glTexCoord2f(textureCoordinates_[0], textureCoordinates_[3]);
		glVertex2f(x, y);
		glTexCoord2f(textureCoordinates_[2], textureCoordinates_[3]);
		glVertex2f(x + textSurface->w, y);
		glEnd();
	}
	glPopAttrib();
	SDL_FreeSurface(textSurface);
}

void SimpleFont::ensureTextureHandle()
{
	if (textureHandle_ == 0)
	{
		glGenTextures(1, &textureHandle_);
	}
	glBindTexture(GL_TEXTURE_2D, textureHandle_);
}

void SimpleFont::releaseTextureHandle()
{
	if (textureHandle_ != 0)
	{
		glDeleteTextures(1, &textureHandle_);
		textureHandle_ = 0;
	}
}
