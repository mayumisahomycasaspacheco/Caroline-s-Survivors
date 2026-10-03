#pragma once
#include "Arma.h"
#include "Proyectil.h"
#include <iostream>

using namespace std;
using namespace System;

class Tirachinas : public Arma
{
private:
	int ralentizacion;
public:
	Tirachinas();
	Proyectil* atacar(int x, int y, int dx, int dy) override;
	int getralentizacion() override;
};

Tirachinas::Tirachinas() : Arma()
{
	nombre = "Tirachinas";
	danio = 5;
	ralentizacion = 40;
}

int Tirachinas::getralentizacion()
{
	return ralentizacion;
}

Proyectil* Tirachinas::atacar(int x, int y, int dx, int dy)
{
	int inicioX = x;
	int inicioY = y;

	if (dx == 1)
	{
		inicioX = x + 9;
		inicioY = y + 1;
	}

	if (dx == -1)
	{
		inicioX = x - 3;
		inicioY = y + 1;
	}

	if (dy == -1)
	{
		inicioX = x + 4;
		inicioY = y - 1;
	}

	if (dy == 1)
	{
		inicioX = x + 4;
		inicioY = y + 3;
	}

	Proyectil* proyectil = new Proyectil(inicioX, inicioY, dx, dy);

	Console::ForegroundColor = ConsoleColor::Gray;
	proyectil->dibujar();
	Console::ResetColor();

	return proyectil;

}