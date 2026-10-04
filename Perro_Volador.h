#pragma once
#include "Enemigo.h"
#include "Matrices.h"
#include <iostream>
#include <Windows.h>

using namespace std;
using namespace System;

const int PERRO_HITBOX_OFFSET_X = 6;
const int PERRO_HITBOX_ANCHO = 10;
const int PERRO_HITBOX_ALTO = 4;

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
	int contador_movimiento;
public:
	Perro(int x, int y);

	void dibujar() override;
	void borrar(int xanterior, int yanterior, int mapa[FILAS][COLUMNAS]);
	void mover(int objetivox, int objetivoy);

	void ralentizar(int ticks);
	bool esta_lento();
};

Perro::Perro(int x, int y)
{
	vida = 15;
	danio = 8;

	this->x = x;
	this->y = y;

	ticks_lento = 0;
	contador_movimiento = 0;
}

void Perro::dibujar()
{
	for (int fila = 0; fila < 4; fila++)
	{
		int longitud = (int)perro_volador_arte[fila].length();
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

void Perro::borrar(int xanterior, int yanterior, int mapa[FILAS][COLUMNAS])
{
	for (int fila = 0; fila < 4; fila++)
	{
		int longitud = (int)perro_volador_arte[fila].length();
		for (int columna = 0; columna < longitud; columna++)
		{
			int mapaX = xanterior + columna;
			int mapaY = yanterior + fila;

			Console::SetCursorPosition(mapaX, mapaY);

			if (mapaX < 0 || mapaX >= COLUMNAS || mapaY < 0 || mapaY >= FILAS)
			{
				continue;
			}

			if (mapa[mapaY][mapaX] == PARED)
			{
				Console::ForegroundColor = ConsoleColor::White;
				cout << "#";
			}
			else if (mapa[mapaY][mapaX] == OBSTACULO)
			{
				Console::ForegroundColor = ConsoleColor::DarkYellow;
				cout << "n";
			}
			else if (mapa[mapaY][mapaX] == PUERTA)
			{
				Console::ForegroundColor = ConsoleColor::Green;
				cout << "=";
			}
			else
			{
				cout << " ";
			}
		}
	}

	Console::ForegroundColor = ConsoleColor::Gray;
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
	contador_movimiento++;

	int intervalo = 3;

	if (ticks_lento > 0)
	{
		intervalo = 6;
		ticks_lento--;
	}

	if (contador_movimiento % intervalo != 0)
	{
		return;
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
		y++;
	}

	else if (y > objetivoy)
	{
		y--;
	}

}