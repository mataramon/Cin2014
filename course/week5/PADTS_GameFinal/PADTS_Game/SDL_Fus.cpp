#include "SDL_Fus.h"
#include <stdio.h>

bool init( SDL_Window* gWindow, SDL_Surface* gScreenSurface)
{
	bool success = true;

	//Inicializa SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Crea ventana
		gWindow = SDL_CreateWindow( "PADTS Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			// Superficie
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}


void close_SDL( SDL_Window* gWindow )
{
	//Deallocate surfaces
	/*
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( gKeyPressSurfaces[ i ] );
		gKeyPressSurfaces[ i ] = NULL;
	}
	*/

	// Cierra ventana
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


SDL_Surface* loadSurface( std::string path )
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}
	else
	{
		Uint32 color_T = SDL_MapRGB(loadedSurface->format, 255, 0, 255);				// Color transparente: magenta
		SDL_SetColorKey(loadedSurface, SDL_TRUE, color_T);	// pone color transparente
	}

	return loadedSurface;
}
