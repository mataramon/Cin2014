#include <iostream>
#include <string>
#include <math.h>
#include "Bala.h"

Bala::Bala()
{
	cargaImagenes();
	body = Sprites[ SPRITE_DEFAULT ];
	posX = posY = 300;
	movX = movY = 0;
	existe = true;
}

Bala::Bala(float xi, float yi, float xd, float yd)	// Argumentos: x&y de inicio, x&y destino
{
	cargaImagenes();
	body = Sprites[ SPRITE_DEFAULT ];
	posX = xi;
	posY = yi;

	float m = (yd - yi)/(xd - xi);
	m = atan(m);
	if( (xd - xi) < 0)
		m += 3.1416;
	movY = sin(m)*6;	movX = cos(m)*6;
}

Bala::~Bala()
{
	//SDL_FreeSurface(body);
}

bool Bala::cargaImagenes()
{
	//Loading success flag
	bool success = true;

	// Parado
	Sprites[ SPRITE_DEFAULT ] = loadSurface( "images/player/bullet.bmp" );

	return success;
}

void Bala::mover(float dY, float dX)
{
	
}

void Bala::mover()
{
	posX += movX;	posY += movY;

	if( (posX > 640) || ( posX < -200) || (posY > 480 ) || (posY < -200 ) )
	{
		existe = false;
	}
}

void Bala::muestra_imagen(SDL_Surface* screen)
{ 
	dest.x = (posX-5);
	dest.y = (posY-5);
	dest.w = body->w;
	dest.h = body->h;
 
	SDL_BlitSurface(body, NULL, screen, &dest);
}