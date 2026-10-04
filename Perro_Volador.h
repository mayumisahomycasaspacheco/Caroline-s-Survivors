#pragma once
#include "Enemigo.h"
#include <iostream>
#include <Windows.h>

using namespace std;
using namespace System;

string perro_volador_arte[4] = {
"           __",
"      (___()'`;",
"      /,    /`",
"      \\\"--\\"
};

class Perro : public Enemigo
{
private:
	int ticks_lento;
	bool saltar_movimiento;
public:
	Perro(int x, int y);

	void dibujar() override;
	void borrar(int xanterior, int yanterior) override;
	void mover(int objetivox, int objetivoy);

	void ralentizar(int ticks);
	bool esta_lento();
};

Perro::Perro(int x, int y)
{
	vida = 20;
	danio = 8;

	this->x = x;
	this->y = y;

	ticks_lento = 0;
	saltar_movimiento = false;
}

void Perro::dibujar()
{
	for (int fila = 0; fila < 4; fila++)
	{
		int longitud = perro_volador_arte[fila].length();
		for (int columna = 0; columna < longitud; columna++)
		{
			if (perro_volador_arte[fila][columna] == ' ') 
			{
				continue;
			}

			Console::SetCursorPosition(x + columna, y + fila);
			cout << perro_volador_arte[fila][columna];
		}
	}
}

void Perro::borrar(int xanterior, int yanterior)
{
	for (int fila = 0; fila < 4; fila++)
	{
		int longitud = perro_volador_arte[fila].length();
		for (int columna = 0; columna < longitud; columna++)
		{
			Console::SetCursorPosition(xanterior + columna, yanterior + fila);
			cout << " ";
		}
	}
}

void Perro::ralentizar(int ticks)
{
	ticks_lento = ticks;
}

bool Perro::esta_lento()
{
	return ticks_lento > 0;
}

void Perro::mover(int objetivox, int objetivoy)
{
	if (ticks_lento > 0)
	{
		ticks_lento--;
		saltar_movimiento = !saltar_movimiento;
		if (saltar_movimiento)
		{
			return;
		}
	}

	if (x < objetivox)
	{
		x++;
	}

	else if (x > objetivox)
	{
		x--;
	}

	if (y < objetivoy)
	{
		x--;
	}

	else if (y > objetivoy)
	{
		y--;
	}

}