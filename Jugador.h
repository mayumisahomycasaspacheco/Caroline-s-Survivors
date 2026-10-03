#pragma once
#include "Entidad.h"
#include <iostream>
using namespace std;

class Jugador : public Entidad
{
protected:
	float vida;
	int xp;
	int nivel;
	int xp_para_subir;
public:
	Jugador();

	float getvida();
	void recibir_danio(int danio);

	virtual string* getarte() = 0;
	virtual int getarte_alto() = 0;

	int getxp();
	int getnivel();
	void sumarxp(int cantidad);
	int getxp_para_subir();
};

Jugador::Jugador() : Entidad()
{
	vida = 100;
	xp = 0;
	nivel = 1;
	xp_para_subir = 100;
}

float Jugador::getvida()
{
	return vida;
}

void Jugador::recibir_danio(int danio)
{
	vida -= danio;
}

int Jugador::getxp_para_subir()
{
	return xp_para_subir;
}

int Jugador::getxp()
{
	return xp;
}

int Jugador::getnivel()
{
	return nivel;
}

void Jugador::sumarxp(int cantidad)
{
	xp += cantidad;
	if (xp >= xp_para_subir)
	{
		xp -= xp_para_subir;
		nivel++;
	}
}