#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <math.h>
#include "Objeto.h"

Objeto::Objeto()
{
	cargaImagenes();
	body = Sprites[ SPRITE_DEFAULT ];
	sprite_state = 0;
	mov_C = 8;	mov_counter = 0;
	vida = 4;
	shoot_count = 0;
	posX = posY = 300;
	movX = movY = 0;
	speed = 1;
	friccion = 0.8;
}

Objeto::~Objeto()
{
	//SDL_FreeSurface(body);
}

bool Objeto::cargaImagenes()
{
	//Loading success flag
	bool success = true;

	// Parado
	Sprites[ SPRITE_DEFAULT ] = loadSurface( "images/player/default.bmp" );
	// Camina
	Sprites[ SPRITE_MOVE_1 ] = loadSurface( "images/player/walk1.bmp" );
	// Vida
	Sprites[ SPRITE_LIFE ] = loadSurface( "images/player/life.bmp" );

	return success;
}

void Objeto::mover(float dY, float dX)
{
	shoot_count++;	// Contador para intervalo de disparo

	movY -= dY;	movX += dX;
	if( (posX + movX) < 640 && (posX + movX) > 0)
	posX += movX*speed;
	if( (posY + movY) < 480 && (posY + movY) > 0)
	posY += movY*speed;

	movX *= friccion;
	if(abs(movX) < 0.001)
		movX = 0;
	movY *= friccion;
	if(abs(movY) < 0.001)
		movY = 0;
	
	if( (abs(movX) > 0.5) || (abs(movY) > 0.5) )
	{
		mov_counter++;
		if(mov_counter == mov_C)
		{
			mov_counter = 0;

			if(sprite_state == 0)
			{
				sprite_state = 1;
				body = Sprites[SPRITE_DEFAULT];
			}
			else
			{
				sprite_state = 0;
				body = Sprites[SPRITE_MOVE_1];
			}
		}
	}
}

void Objeto::muestra_imagen(SDL_Surface* screen)
{ 
	dest.x = (posX - 10);
	dest.y = (posY - 10);
	dest.w = body->w;
	dest.h = body->h;
 
	SDL_BlitSurface(body, NULL, screen, &dest);

	for(int v = 0; v < vida; v++)
	{
		dest.x = 20 + 20*v;
		dest.y = 10;
		dest.w = Sprites[SPRITE_LIFE]->w;
		dest.h = Sprites[SPRITE_LIFE]->h;

		SDL_BlitSurface(Sprites[SPRITE_LIFE], NULL, screen, &dest);
	}
}

void Objeto::borrar()
{
	// Parado
	if( Sprites[ SPRITE_DEFAULT ] != NULL )
		SDL_FreeSurface(Sprites[SPRITE_DEFAULT]);
	// Camina
	if( Sprites[ SPRITE_MOVE_1 ] != NULL )
		SDL_FreeSurface(Sprites[SPRITE_MOVE_1]);
	if( Sprites[ SPRITE_LIFE ] != NULL )
		SDL_FreeSurface(Sprites[SPRITE_LIFE]);
}

void Objeto::danio(int cantidad)
{
	vida -= cantidad;
	if(vida <= 0)
	{
		vida = 0;
		existe = false;
	}
}

bool Objeto::dispara()
{
	if(shoot_count > 10)
	{
		shoot_count = 0;
		return true;
	}
	return false;
}
