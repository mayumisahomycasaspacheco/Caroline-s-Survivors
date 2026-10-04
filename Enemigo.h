#pragma once
#include "Entidad.h"

class Enemigo : public Entidad
{
protected:
	int vida;
	int danio;
public:
	Enemigo();

	void dibujar() override;
	void borrar(int xanterior, int yanterior) override;
	void mover() override;

	int getvida();
	int getdanio();
	bool esta_vivo();
	void recibir_danio(int danio);
};

Enemigo::Enemigo()
{
	vida = 30;
	danio = 10;
	x = 60;
	y = 10;
}

void Enemigo::dibujar()
{
}

void Enemigo::borrar(int xanteior, int yanterior)
{
}

void Enemigo::mover()
{
}

int Enemigo::getvida()
{
	return vida;
}

int Enemigo::getdanio()
{
	return danio;
}

void Enemigo::recibir_danio(int danio)
{
	vida -= danio;
}

bool Enemigo::esta_vivo()
{
	return vida > 0;
}