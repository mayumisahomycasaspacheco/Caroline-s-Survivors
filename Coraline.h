#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Jugador.h"
#include "Tirachinas.h"
using namespace std;
using namespace System;

string coraline_arte[3] = {
	" O ",
	"/|\\",
	"/ \\"
};

class Coraline : public Jugador
{
private:
	Tirachinas* arma;
	Proyectil** proyectiles;
	int cantidad_proyectiles;
	int tiempo_disparo;
	bool jugado;
	int direccionx;
	int direcciony;

public:
	Coraline(bool jugado);
	~Coraline();

	void dibujar();
	void borrar(int xanterior, int yanterior);
	void mover();

	bool getjugado();
	void setjugado(bool jugado);

	int getdanio_arma();
	int getralentizacion_arma();

	Proyectil** getproyectiles();
	int getcantidad_proyectiles();

	void disparar(int dx, int dy);
	void limpiar_proyectiles();

	string* getarte() override;
	int getarte_alto() override;
};

Coraline::Coraline(bool jugado) : Jugador()
{
	arma = new Tirachinas();

	proyectiles = nullptr;
	cantidad_proyectiles = 0;
	tiempo_disparo = 2000;

	x = 20;
	y = 10;
	direccionx = 1;
	direcciony = 0;

	this->jugado = jugado;

	nombre = "Coraline";
	xp = 0;
	nivel = 1;
	xp_para_subir = 5;
}

Coraline::~Coraline()
{
	for (int i = 0; i < cantidad_proyectiles; i++)
	{
		delete proyectiles[i];
	}

	delete[] proyectiles;
	delete arma;
}

bool Coraline::getjugado()
{
	return jugado;
}

void Coraline::setjugado(bool jugado)
{
	this->jugado = jugado;
}

int Coraline::getdanio_arma()
{
	return arma->getdanio();
}

int Coraline::getralentizacion_arma()
{
	return arma->getralentizacion();
}

Proyectil** Coraline::getproyectiles()
{
	return proyectiles;
}

int Coraline::getcantidad_proyectiles()
{
	return cantidad_proyectiles;
}

string* Coraline::getarte()
{
	return coraline_arte;
}

int Coraline::getarte_alto()
{
	return 3;
}

void Coraline::dibujar()
{
	for (int fila = 0; fila < 3; fila++)
	{
		int longitud = coraline_arte[fila].length();

		for (int columna = 0; columna < longitud; columna++)
		{
			if (coraline_arte[fila][columna] == ' ') continue;
			Console::SetCursorPosition(x + columna, y + fila);
			cout << coraline_arte[fila][columna];
		}

	}
}

void Coraline::borrar(int xanterior, int yanterior)
{
	for (int fila = 0; fila < 3; fila++)
	{
		int longitud = coraline_arte[fila].length();
		for (int columna = 0; columna < longitud; columna++)
		{
			Console::SetCursorPosition(xanterior + columna, yanterior + fila);
			cout << " ";
		}
	}
}
