#pragma once
#include <iostream>
#include <Windows.h>
#include "Matrices.h"
#include "Coraline.h"
using namespace std;
using namespace System;

class Interfaz
{
public:
	void configurar_consola();
	void dibujar_mapa(int mapa[FILAS][COLUMNAS]);
	void dibujar_HUD(Coraline* coraline);
	void dibujar_objetivo(int sala_actual, int total_salas, int perros_vivos);
private:
};

void Interfaz::configurar_consola()
{
	Console::Title = "Coraline vs Perros Voladores (Maravilla del Teatro)";
	Console::CursorVisible = false;
	Console::SetBufferSize(COLUMNAS + 1, FILAS + 5);
	Console::SetWindowSize(COLUMNAS, FILAS + 2);
}

void Interfaz::dibujar_mapa(int mapa[FILAS][COLUMNAS])
{
	for (int fila = 0; fila < FILAS; fila++)
	{
		Console::SetCursorPosition(0, fila);
		
		for (int columna = 0; columna < COLUMNAS; columna++)
		{
			if (mapa[fila][columna] == PARED)
			{
				cout << "#";
			}

			else if (mapa[fila][columna] == PUERTA)
			{
				cout << "=";
			}

			else
			{
				cout << " ";
			}

		}
	}
}

void Interfaz::dibujar_HUD(Coraline* coraline)
{
	Console::SetCursorPosition(0, FILAS);
	cout << "Vida: " << coraline->getvida()
		<< " Nivel: " << coraline->getnivel()
		<< " XP: " << coraline->getxp() << "/" << coraline->getxp_para_subir()
		<< "       ";
}

void Interfaz::dibujar_objetivo(int sala_actual, int total_salas, int perros_vivos)
{
	Console::SetCursorPosition(0, FILAS + 1);
	cout << "Sala " << sala_actual << "/" << total_salas
		<< "    Perros vivos: " << perros_vivos
		<< "           ";
}