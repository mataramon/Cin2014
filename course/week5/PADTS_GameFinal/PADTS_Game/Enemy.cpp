#include <math.h>
#include "Enemy.h"

Enemy::Enemy( )	// Recibe valores "semilla" para generar posicion inicial pseudoaleatoria. Estos son: pos de jugador, pos de mouse, numero de balas y numero de elementos en el mapa
{
	tipo = rand() % 3;	// Elige entre 0 ~ 2
	cargaImagenes();

	// Posicion de inicio aleatoria
	if( (rand() % 100) < 50)
	{
		posX = rand() % 640;
		if( (rand() % 100) < 50)
			posY = -100;
		else
			posY = 580;
	}
	else
	{
		posY = rand() % 480;
		if( (rand() % 100) < 50)
			posX = -100;
		else
			posX = 740;
	}
	dirCounter = 0;
	dirX = -4 + rand()%8;
	dirY = -4 + rand()%8;

	if(tipo == 0)	// Goomba
	{
		speed = 0.25 + (float)(rand()%40)/100;
		movX = movY = 0;
		existe = true;
		friccion = 0.8;
	}
	else if(tipo == 1)	// Zombie
	{
		speed = 0.3 + (float)(rand()%50)/100;
		movX = movY = 0;
		existe = true;
		friccion = 0.8;
	}
	else	// Fantasma
	{
		speed = 0.6 + (float)(rand()%50)/100;
		movX = movY = 0;
		existe = true;
		friccion = 0.8;
	}

	mov_C = 8;	mov_counter = 0;	
}

Enemy::~Enemy()
{
	//SDL_FreeSurface(body);
}

bool Enemy::cargaImagenes()
{
	//Loading success flag
	bool success = true;

	if(tipo == 0)
	{
		Sprites[ SPRITE_DEFAULT ] = loadSurface( "images/enemy/enemy.bmp" );
		Sprites[ SPRITE_MOVE_1 ] = loadSurface( "images/enemy/Ewalk.bmp" );
		body = Sprites[SPRITE_DEFAULT];
	}
	else if(tipo == 1)
	{
		Sprites[ SPRITE_DEFAULT ] = loadSurface( "images/enemy2/enemy.bmp" );
		Sprites[ SPRITE_MOVE_1 ] = loadSurface( "images/enemy2/Ewalk.bmp" );
		body = Sprites[SPRITE_DEFAULT];
	}
	else
	{
		Sprites[ SPRITE_MOVE_1 ] = loadSurface( "images/enemy3/right.bmp" );
		Sprites[ SPRITE_MOVE_2 ] = loadSurface( "images/enemy3/up.bmp" );
		Sprites[ SPRITE_MOVE_3 ] = loadSurface( "images/enemy3/left.bmp" );
		Sprites[ SPRITE_MOVE_4 ] = loadSurface( "images/enemy3/down.bmp" );
		body = Sprites[SPRITE_MOVE_1];
	}

	return success;
}

void Enemy::mover(float dY, float dX)
{	
	/// SE MUEVE SEGUN QUÉ ENEMIGO ES
	if(tipo == 0)
	{	
		dirCounter++;
		if(dirCounter > 20)
		{
			dirCounter = 0;
			dirY = dY -200 + rand()%400;	dirX = dX -200 + rand()%400;
		}
	}
	else if(tipo == 1)
	{		dirY = dY -50 + rand()%100;		dirX = dX - 50 + rand()%100;	}
	else
	{	
		dirCounter++;
		if(dirCounter > 45)
		{
			dirCounter = 0;

			if( rand()%100 < 50)
			{
				dirX = posX;
				if( rand()%100 < 50 )
				{
					dirY = posY + 500;
					body = Sprites[SPRITE_MOVE_4];
				}
				else
				{
					body = Sprites[SPRITE_MOVE_2];
					dirY = posY - 500;
				}
			}
			else
			{
				dirY = posY;
				if( rand()%100 < 50 )
				{
					dirX = posX + 500;
					body = Sprites[SPRITE_MOVE_1];
				}
				else
				{
					dirX = posX - 500;
					body = Sprites[SPRITE_MOVE_3];
				}
			}
		}
	}
	/////////////////////////
	
	if( (dirX - posX) == 0)		// Evitar divisiones por 0
		dirX += 0.00000001;	
	float m = (dirY - posY)/(dirX - posX);
	m = atan(m);
	if( (dirX - posX) < 0)
		m += 3.1416;
	movY += sin(m)*speed;	movX += cos(m)*speed;
	posX += movX;	posY += movY;

	movX *= friccion;
	if(abs(movX) < 0.001)
		movX = 0;

	movY *= friccion;
	if(abs(movY) < 0.001)
		movY = 0;

	if(tipo != 2)
	{
		mov_counter++;
		if(mov_counter == mov_C)
		{
			mov_counter = 0;
			
			if(tipo != 2)
			{
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
}

void Enemy::muestra_imagen(SDL_Surface* screen)
{ 
	dest.x = (posX-5);
	dest.y = (posY-5);
	dest.w = body->w;
	dest.h = body->h;
 
	SDL_BlitSurface(body, NULL, screen, &dest);
}
