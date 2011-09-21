/**
 * Main.cpp
 * Entry point to the game.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Display.h"
#include "Constants.h"
#include "SimpleFont.h"
#include "Texture.h"
#include "Utility.h"

Texture logoTexture;
float vertices[4];
float texcoords[4];

SimpleFont demoFont;

int Init()
{
    if (!logoTexture.loadFromFile(PathForResource("logo.png")))
    {
        fprintf(stderr, "Unable to load logo.png!\n");
        return -1;
    }
      
    // Precalculate vertices and texture coordinates to draw that logo
    // centered on the window.
    vertices[0] = (kWindowWidth / 2.0f) - (logoTexture.width / 2.0f);
    vertices[1] = (kWindowHeight / 2.0f) - (logoTexture.height / 2.0f);
    vertices[2] = vertices[0] + logoTexture.width;
    vertices[3] = vertices[1] + logoTexture.height;
    
    texcoords[0] = 0;
    texcoords[1] = 0;
    texcoords[2] = 1.0f;
    texcoords[3] = 1.0f;

	if (!demoFont.loadFromFile(PathForResource("Orbitron-Regular.ttf"), 20))
	{
		fprintf(stderr, "Unable to load Orbitron-Regular.ttf!\n");
		return -1;
	}
	
    return 0;
}

void Cleanup()
{
	logoTexture.releaseHandle();
	demoFont.releaseTextureHandle();
}

void Draw(float currentTime)
{
    // Set up the projection matrix and viewport for standard 2D drawing
    glViewport(0, 0, kWindowWidth, kWindowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, kWindowWidth, 0, kWindowHeight, -1, 1);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, logoTexture.handle);
    glColor3f(1, 1, 1);
    
    glBegin(GL_QUADS);
    glTexCoord2f(texcoords[0], texcoords[3]);
    glVertex2f(vertices[0], vertices[1]);
    glTexCoord2f(texcoords[0], texcoords[1]);
    glVertex2f(vertices[0], vertices[3]);
    glTexCoord2f(texcoords[2], texcoords[1]);
    glVertex2f(vertices[2], vertices[3]);
    glTexCoord2f(texcoords[2], texcoords[3]);
    glVertex2f(vertices[2], vertices[1]);
    glEnd();
	
	demoFont.drawFormattedText(40, kWindowHeight - 40, "Seconds Elapsed: %.4f", currentTime);
}

void MainLoop()
{
    // Timing data
    float currentTime = SDL_GetTicks() / 1000.0f;
    float accumulator = 0.0f;
    
    bool alive = true;
    while (alive)
    {
        // Update timing data
        float newTime = SDL_GetTicks() / 1000.0f;
		float deltaTime = newTime - currentTime;
		currentTime = newTime;
		
		// Clamp the time delta to a maximum of 0.25 seconds for easier debugging
		if (deltaTime > 0.25f) deltaTime = 0.25f;
		
		accumulator += deltaTime;
        
        while (accumulator >= kTargetDT)
        {
            // Run through SDL's normal event loop to see whether the user is trying
			// to quit.
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				switch (e.type) {
					case SDL_QUIT:
						alive = false;
						break;
						
					case SDL_KEYUP:
                        switch (e.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                SDL_Event quitEvent;
                                quitEvent.type = SDL_QUIT;
                                SDL_PushEvent(&quitEvent);
                                break;
                                
                        }
                        break;
						
					default:
						break;
				}
			}
            
            accumulator -= kTargetDT;
        }
        
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        Draw(currentTime);
        
		SDL_GL_SwapBuffers();
		
		// Let the OS have a bit of time to breath.
		SDL_Delay(1);
    }
    
}

int SDL_main(int argc, char **argv)
{
    if (!Display_Open(kWindowTitle, kWindowWidth, kWindowHeight, 32, false))
    {
        fprintf(stderr, "Unable to open an OpenGL window!\n");
        goto cleanup;
    }
    
    if (Init() != 0)
    {
        goto cleanup;
    }
    
    // Seed the stdlib random number generator
    srand(time(NULL));

    MainLoop();
    
cleanup:
    Cleanup();
    Display_Close();
    return 0;
}
