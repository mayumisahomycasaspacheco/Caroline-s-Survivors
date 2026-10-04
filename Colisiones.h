#pragma once
#include "matrices.h"
#include <iostream>
using namespace std;

bool puede_mover_entidad(int mapa[FILAS][COLUMNAS], int x, int y, string arte[], int arte_alto)
{
	for (int fila = 0; fila < arte_alto; fila++)
	{
		int ancho = (int)arte[fila].length();

		for (int columna = 0; columna < ancho; columna++)
		{
			int mapax = x + columna;
			int mapay = y + fila;

			if (mapax < 0 || mapax >= COLUMNAS || mapay < 0 || mapay >= FILAS)
			{
				return false;
			}

			if (mapa[mapay][mapax] == PARED || mapa[mapay][mapax] == OBSTACULO)
			{
				return false;
			}

		}
	}

	return true;

}