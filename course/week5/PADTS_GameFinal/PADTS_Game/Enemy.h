#ifndef OBJETO
	#include "Objeto.h"
	#include <cstdlib>
#endif

// Hereda de "Objeto" porque tiene los mismos datos (posicion, movimiento...)
class Enemy : public Objeto
{
	// Se agregan valores para indicar direccion de movimiento
	int dirCounter;
	float dirY, dirX;

	public:

	int tipo;	// Determina cuál enemigo es
	SDL_Rect src, dest;
	// Imagenes de personaje
	SDL_Surface* Sprites[ SPRITE_TOTAL ];

	Enemy();
	~Enemy();
	virtual bool cargaImagenes();
	void muestra_imagen(SDL_Surface * screen);
	void mover(float dX, float dY);
};
