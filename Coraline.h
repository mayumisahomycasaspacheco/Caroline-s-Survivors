#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#pragma comment(lib, "User32.lib")
#include "Jugador.h"
#include "Tirachinas.h"
#include "Colisiones.h"
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
	void mover(int mapa[FILAS][COLUMNAS]);

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
	tiempo_disparo = 800;

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
	return arma->getdanio() + (getnivel() - 1);
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
		int longitud = (int)coraline_arte[fila].length();

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
		int longitud = (int)coraline_arte[fila].length();
		for (int columna = 0; columna < longitud; columna++)
		{
			Console::SetCursorPosition(xanterior + columna, yanterior + fila);
			cout << " ";
		}
	}
}

void Coraline::disparar(int dx, int dy)
{
	if (tiempo_disparo >= 800) // 0.4s de recarga, en vez de 1 segundo
	{
		Proyectil* nuevo_proyectil = arma->atacar(x, y, dx, dy);

		Proyectil** nuevos_proyectiles = new Proyectil * [cantidad_proyectiles + 1];
		for (int i = 0; i < cantidad_proyectiles; i++)
		{
			nuevos_proyectiles[i] = proyectiles[i];
		}

		nuevos_proyectiles[cantidad_proyectiles] = nuevo_proyectil;

		delete[] proyectiles;
		proyectiles = nuevos_proyectiles;
		cantidad_proyectiles++;

		tiempo_disparo = 0;

	}
}

void Coraline::limpiar_proyectiles()
{
	int vivos = 0;
	for (int i = 0; i < cantidad_proyectiles; i++)
	{
		if (proyectiles[i]->getdistancia_recorrida() > 0)
		{
			vivos++;
		}
	}

	if (vivos == cantidad_proyectiles)
	{
		return;
	}

	Proyectil** nuevos_proyectiles = nullptr;

	if (vivos > 0)
	{
		nuevos_proyectiles = new Proyectil * [vivos];
	}

	int j = 0;
	for (int i = 0; i < cantidad_proyectiles; i++)
	{
		if (proyectiles[i]->getdistancia_recorrida() > 0)
		{
			nuevos_proyectiles[j] = proyectiles[i];
			j++;
		}

		else
		{
			delete proyectiles[i];
		}

	}

	delete[] proyectiles;
	proyectiles = nuevos_proyectiles;
	cantidad_proyectiles = vivos;

}

void Coraline::mover(int mapa[FILAS][COLUMNAS])
{
	if (jugado == true)
	{
		int xnuevo = x;
		int ynuevo = y;

		if (GetAsyncKeyState('W') & 0x8000)
		{
			ynuevo = y - 1;
			direccionx = 0;
			direcciony = -1;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			ynuevo = y + 1;
			direccionx = 0;
			direcciony = 1;
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			xnuevo = x - 1;
			direccionx = -1;
			direcciony = 0;
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			xnuevo = x + 1;
			direccionx = 1;
			direcciony = 0;
		}

		if (puede_mover_entidad(mapa, xnuevo, ynuevo, coraline_arte, 3))
		{
			x = xnuevo;
			y = ynuevo;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			disparar(0, -1);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			disparar(0, 1);
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			disparar(-1, 0);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			disparar(1, 0);
		}
	}

	tiempo_disparo += 100;
}
