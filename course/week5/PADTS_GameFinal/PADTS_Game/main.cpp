#include <iostream>
#include <string>
#include <vector>

#include "Objeto.h"
#include "Bala.h"
#include "Enemy.h"
#include "soundhandler.h"
#include "SoundEffect.h"
#include "SDL/SDL.h"		// SDL, biblioteca grafica
#include "SDL/SDL_timer.h"	//biblioteca de timers

//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

bool init( );
void close_SDL(  );
void pintar_barra();
void limpiar_elementos();

enum KeyValues
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	CLICK,
	TOTAL
};
bool pressed_key[TOTAL];

SDL_Window* gWindow = NULL;				// Ventana principal
SDL_Surface* gScreenSurface = NULL;		//The surface contained by the window
SDL_Surface* Fondo = NULL;
SDL_Surface* Inicio = NULL;
SDL_Surface* Pierde = NULL;
SDL_Surface* Gana = NULL;
// Indicadores de objetivos matados
SDL_Surface* Barra = NULL;
SDL_Surface* Punto = NULL;
int enemigosMatados = 0;

std::vector<Bala> ArrayBalas;
std::vector<Enemy> ArrayEnemy;
int spawn_enemy_T = 0;

Objeto *player;		// Objeto del personaje principal

// Variables para usar timers de SDL
int Timer_cuentas;
bool fin = false, gano = false;


int main( int argc, char* args[] )
{

	// Sonidos
	string fileEnemy = "sounds/enemydead.wav";
	SoundEffect soundEnemy(fileEnemy);
	if (!soundEnemy.engine())
		cout << "Could not startup engine" << endl;

	string fileBullet = "sounds/bullet.wav";
	SoundEffect soundBullet(fileBullet);
	if (!soundBullet.engine())
		cout << "Could not startup engine" << endl;

	string fileGhost = "sounds/ghost.wav";
	SoundEffect soundGhost(fileGhost);
	if (!soundGhost.engine())
		cout << "Could not startup engine" << endl;
	soundGhost.engine_->setSoundVolume(0.7f);

	string fileGoomba = "sounds/Goomba.wav";
	SoundEffect soundGoomba(fileGoomba);
	if (!soundGoomba.engine())
		cout << "Could not startup engine" << endl;

	string fileFondo = "sounds/the_moon.mp3";
	SoundEffect soundFondo(fileFondo);
	if (!soundFondo.engine())
		cout << "Could not startup engine" << endl;
	soundFondo.engine_->setSoundVolume(0.5f);

	string filePierde= "sounds/lilium.wav";
	SoundEffect soundPierde(filePierde);
	if (!soundPierde.engine())
		cout << "Could not startup engine" << endl;

	// Inicializa SDL
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		SDL_Event e;
		Barra = loadSurface("images/ObjetivoBarra.bmp");
		Punto = loadSurface("images/ObjetivoPunto.bmp");

		Inicio = loadSurface("images/inicio.bmp");
		SDL_BlitSurface(Inicio, NULL, gScreenSurface, NULL);
		SDL_BlitSurface(Fondo, NULL, gScreenSurface, NULL);
		// Actualiza imagen
		SDL_UpdateWindowSurface( gWindow );	
		bool empezar = false;

		Gana = loadSurface("images/Win.bmp");
		Pierde = loadSurface("images/Pierde.bmp");
		Fondo = loadSurface("images/fondo.bmp");
		player = new Objeto();
		//Main loop flag
		bool quit = false;
		
		// Mientras el usuario no cierre la aplicaci�n
		while( !quit )
		{
			if( SDL_PollEvent( &e ) != 0 )
			{
				if( !gano && !fin && !empezar && e.type == SDL_MOUSEBUTTONDOWN)
				{	empezar = true;
					soundFondo.play(fileFondo, true);
				}

				if( e.type == SDL_QUIT )
					quit = true;

				// Presiona una tecla/boton
				else if( e.type == SDL_KEYDOWN )
				{
					switch( e.key.keysym.sym )
					{
						case SDLK_UP:
							pressed_key[UP] = true;
						break;
						case SDLK_DOWN:
							pressed_key[DOWN] = true;
						break;
						case SDLK_LEFT:
							pressed_key[LEFT] = true;
						break;
						case SDLK_RIGHT:
							pressed_key[RIGHT] = true;
						break;
					}
				}
				else if( e.type == SDL_KEYUP )
				{
					switch( e.key.keysym.sym )
					{
						case SDLK_UP:
							pressed_key[UP] = false;
						break;
						case SDLK_DOWN:
							pressed_key[DOWN] = false;
						break;
						case SDLK_LEFT:
							pressed_key[LEFT] = false;
						break;
						case SDLK_RIGHT:
							pressed_key[RIGHT] = false;
						break;
					}
				}
				if(e.type == SDL_MOUSEBUTTONDOWN)
				{
					pressed_key[CLICK] = true;
				}
				else if(e.type == SDL_MOUSEBUTTONUP)
				{
					pressed_key[CLICK] = false;
				}

			}


			if( empezar && !fin && !gano && !( SDL_GetTicks() % 25) )
			{
				// Repintar ventana
				SDL_BlitSurface(Fondo, NULL, gScreenSurface, NULL);

				// Crear balas si est� clickeando
				if(pressed_key[CLICK] && player->dispara())
				{
					// Crea enemigos cada 0.5s
					int mx;	int my;
					SDL_GetMouseState(&mx, &my);
					Bala * nuevaBala = new Bala((int)player->posX, (int)player->posY, (float)mx, (float)my);
					ArrayBalas.push_back(*nuevaBala);

					soundBullet.play(fileBullet, false);

					std::cout << std::endl;
					std::cout << std::endl;
					std::cout << "mausX: " << mx;
					std::cout << "  mausY: " << my << std::endl;
				
					std::cout << "X: " << player->posX;
					std::cout << "  Y: " << player->posY << std::endl;

					std::cout << "enemies: " << ArrayEnemy.size();
				}

				// crea enemigos
				spawn_enemy_T++;
				if(spawn_enemy_T > 20)
				{	spawn_enemy_T = 0;
					Enemy * newEnemy = new Enemy();
					ArrayEnemy.push_back(*newEnemy);
				}

				// Mover hacia direccion elegida
				if( pressed_key[UP] )	
				{
					if(pressed_key[LEFT])
						player->mover( 0.7071, -0.7071);
					else if(pressed_key[RIGHT])
						player->mover( 0.7071, 0.7071);
					else
						player->mover( 1, 0);
				}
				else if( pressed_key[DOWN] )	
				{
					if(pressed_key[LEFT])
						player->mover( -0.7071, -0.7071);
					else if(pressed_key[RIGHT])
						player->mover( -0.7071, 0.7071);
					else
						player->mover( -1, 0);
				}
				else if(pressed_key[LEFT])
					player->mover( 0, -1);
				else if(pressed_key[RIGHT])
					player->mover( 0, 1);
				else
					player->mover( 0, 0);
					
				// Actualiza y dibuja balas
				int b;
				for(b = 0; b < ArrayBalas.size(); b++)
				{	
					ArrayBalas[b].mover();
					if( !ArrayBalas[b].existe )
						ArrayBalas.erase( ArrayBalas.begin() + b);
					else
					{
						//ArrayBalas[b].borrar();
						ArrayBalas[b].muestra_imagen(gScreenSurface);
					}
				}
				// Actualiza y dibuja enemigos
				int e;
				for(e = 0; e < ArrayEnemy.size(); e++)
				{	
					// Verifica choque de jugador con enemigos
					if( (player->posX - ArrayEnemy[e].posX)*(player->posX - ArrayEnemy[e].posX) + (player->posY - ArrayEnemy[e].posY)*(player->posY - ArrayEnemy[e].posY) < 80)
					{	
						ArrayEnemy[e].existe = false;
						player->danio(1);

						
					}

					// Verifica choque de enemigos con balas
					ArrayEnemy[e].mover(player->posY, player->posX);
						
					int b;
					for(b = 0; b < ArrayBalas.size(); b++)
					{	
						// calcula distancia y verifica si hubo colision con balas existentes
						if( ArrayBalas[b].existe && ((ArrayBalas[b].posX - ArrayEnemy[e].posX)*(ArrayBalas[b].posX - ArrayEnemy[e].posX) + (ArrayBalas[b].posY - ArrayEnemy[e].posY)*(ArrayBalas[b].posY - ArrayEnemy[e].posY)) < 100)
						{	
							ArrayEnemy[e].existe = false;
							ArrayBalas[b].existe = false;
							enemigosMatados++;
							switch(ArrayEnemy[e].tipo)
							{	case 0:	soundGoomba.play(fileGoomba, false);
										break;
								case 1:	soundEnemy.play(fileEnemy, false);
										break;
								case 2:	soundGhost.play(fileGhost, false);
										break;
							}
						}
					}
	
					if( !ArrayEnemy[e].existe )
					{
						ArrayEnemy[e].borrar();
						ArrayEnemy.erase( ArrayEnemy.begin() + e);
					}
					else
						ArrayEnemy[e].muestra_imagen(gScreenSurface);

				}
				if(enemigosMatados >= 100)
					gano = true;
				// Pone numero de enemigos matados en barra
				pintar_barra();

				fin = !player->existe;
				// Actualiza posicion en pantalla
				player->muestra_imagen(gScreenSurface);
				// Actualiza ventana
				SDL_UpdateWindowSurface( gWindow );		
			}
			else if( fin )
			{
				if(player != NULL)
				{
					player->borrar();
					delete player;
					player = NULL;
					empezar = false;
					SDL_BlitSurface(Pierde, NULL, gScreenSurface, NULL);
					SDL_UpdateWindowSurface( gWindow );
					soundPierde.play(filePierde, false);
					soundFondo.engine_->setSoundVolume(0);
				}
				// Espera a que el usuario presione enter para reiniciar
				SDL_PollEvent(&e);
				if(e.type == SDL_KEYDOWN &&  e.key.keysym.sym == SDLK_RETURN)
				{
					player = new Objeto();
					fin = false;
					empezar = true;
					soundFondo.engine_->setSoundVolume(0.5f);
					enemigosMatados = 0;
					limpiar_elementos();
				}
			}
			else if (gano)
			{
				SDL_BlitSurface(Gana, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface( gWindow );
				soundFondo.engine_->setSoundVolume(0.1f);

				SDL_PollEvent(&e);
				if(e.type == SDL_KEYDOWN &&  e.key.keysym.sym == SDLK_RETURN)
				{
					player = new Objeto();
					gano = false;
					empezar = true;
					soundFondo.engine_->setSoundVolume(0.5f);
					enemigosMatados = 0;
					limpiar_elementos();
				}
			}
		}
	}

	// Libera recursos y cierra SDL
	close_SDL();
	delete player;
	limpiar_elementos();

	return 0;
}


bool init( )
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

void close_SDL(  )
{
	// Cierra ventana
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	// Libera SDL de memoria
	SDL_Quit();
}

void pintar_barra()
{
	SDL_Rect dest;

	dest.x = 500-1;
	dest.y = 10;
	dest.w = Barra->w;
	dest.h = Barra->h;

	SDL_BlitSurface(Barra, NULL, gScreenSurface, &dest);

	for(int e = 0; e < enemigosMatados; e++)
	{
		dest.x = 500 + e;
		dest.y = 10;
		dest.w = Punto->w;
		dest.h = Punto->h;

		SDL_BlitSurface(Punto, NULL, gScreenSurface, &dest);
	}
}

void limpiar_elementos()
{
	int b;
	for(b = 0; b < ArrayBalas.size(); b++)
	{	
		ArrayBalas[b].borrar();
		ArrayBalas.erase( ArrayBalas.begin() + b);
	}
	int e;
	for(e = 0; e < ArrayEnemy.size(); e++)
	{	
		ArrayEnemy[e].borrar();
		ArrayEnemy.erase( ArrayEnemy.begin() + e);
	}
}
