#include <SDL/SDL.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init( SDL_Window* *gWindow, SDL_Surface* *gScreenSurface);		//Starts up SDL and creates window
SDL_Surface* loadSurface( std::string path );	//Carga imagen individual
void close_SDL( SDL_Window* gWindow );	//Frees media and shuts down SDL