#pragma once
#include "Entidad.h"
#include <iostream>
#include <Windows.h>

using namespace System;
using namespace std;

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

Proyectil::~Proyectil()
{
}

void Proyectil::dibujar()
{
	Console::SetCursorPosition(x, y);
	cout << "o";
}

void Proyectil::borrar(int xanterior, int yanterior)
{
	Console::SetCursorPosition(xanterior, yanterior);
	cout << " ";
}

void Proyectil::mover()
{
	if (distancia_recorrida > 0)
	{
		x += dx * velocidad;
		y += dy * velocidad;
		distancia_recorrida--;
	}
}

int Proyectil::getdistancia_recorrida()
{
	return distancia_recorrida;
}

void Proyectil::detener()
{
	distancia_recorrida = 0;
}