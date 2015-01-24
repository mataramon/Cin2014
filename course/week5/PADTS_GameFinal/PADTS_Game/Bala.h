#ifndef OBJETO
	#include "Objeto.h"
#endif


class Bala : public Objeto
{
	protected:

	float mX, mY;	// Posicion
	float movX, movY;	// Velocidad

	public:

	Bala();
	Bala(float xi, float yi, float xd, float yd);
	~Bala();
	virtual bool cargaImagenes();
	void muestra_imagen(SDL_Surface * screen);
	void mover(float dX, float dY);
	void mover();
};
