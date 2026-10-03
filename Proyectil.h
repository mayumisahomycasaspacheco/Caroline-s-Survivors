#pragma once
#include "Entidad.h"

class Proyectil : public Entidad
{
private:
	int dx;
	int dy;
	int velocidad;
	int distancia_recorrida;

public:
	Proyectil(int x, int y, int dx, int dy);
	~Proyectil();

	void dibujar() override;
	void borrar(int xanterior, int yanterior) override;
	void mover() override;

	int getdistancia_recorrida();
	void detener();
};

Proyectil::Proyectil(int x, int y, int dx, int dy)
{
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	velocidad = 3;
	distancia_recorrida = 7;
}