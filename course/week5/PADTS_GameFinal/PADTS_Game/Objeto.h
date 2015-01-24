#ifndef OBJETO
	#define OBJETO
	#include <SDL/SDL.h>
	#include <iostream>
	#include "SDL_Fus.h"
#endif

class Objeto
{
	protected:

	float movX, movY;	// movimiento
	float speed;
	float friccion;		// Friccion (para limitar velocidad de movimiento)
	int vida;			
	SDL_Surface* body;	// Imagen actual del objeto
	int sprite_state;	// indicador de sprite actual
	int mov_C;	// Duracion de cada sprite
	int	mov_counter;		// cuenta tiempo de sprite
	int shoot_count;

	enum Sprite
	{
		SPRITE_DEFAULT,
		SPRITE_ATTACK,
		SPRITE_MOVE_1,
		SPRITE_MOVE_2,
		SPRITE_MOVE_3,
		SPRITE_MOVE_4,
		SPRITE_LIFE,
		SPRITE_DIES,
		SPRITE_TOTAL
	};

	public:

	float posX, posY;	// Posicion
	bool existe;
	SDL_Rect src, dest;
	// Imagenes de personaje
	SDL_Surface* Sprites[ SPRITE_TOTAL ];

	Objeto();
	// Objeto(int xi, int yi, int xd, int yd);
	~Objeto();
	virtual void borrar();
	virtual bool cargaImagenes();
	void mover(float dX, float dY);
	virtual void muestra_imagen(SDL_Surface * screen);
	virtual void daño(int cantidad);
	bool dispara();
};
