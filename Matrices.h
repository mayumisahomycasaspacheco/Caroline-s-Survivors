#pragma once

const int VACIO = 0;
const int PARED = 1;
const int PUERTA = 2;

const int FILAS = 40;
const int COLUMNAS = 120;
const int TOTAL_SALAS = 3;

int mapa_platea[FILAS][COLUMNAS];
int mapa_escenario[FILAS][COLUMNAS];
int mapa_camerinos[FILAS][COLUMNAS];

int (*mapas[TOTAL_SALAS])[COLUMNAS];

int spawnx[TOTAL_SALAS] = { 5, 5, 5 };
int spawny[TOTAL_SALAS] = { 18, 18, 18};

int perros_por_salas[TOTAL_SALAS] = { 3, 5, 8 };

void generar_sala_vacia(int mapa[FILAS][COLUMNAS])
{
	for (int fila = 0; fila < FILAS; fila++)
	{
		for (int columna = 0; columna < COLUMNAS; columna++)
		{
			if (fila == 0 || fila == FILAS - 1 || columna == 0 || columna == COLUMNAS - 1)
			{
				mapa[fila][columna] = PARED;
			}

			else
			{
				mapa[fila][columna] = VACIO;
			}
		}
	}
}

void agregar_butacas(int mapa[FILAS][COLUMNAS])
{
	for (int fila = 10; fila <= 28; fila += 4)
	{
		for (int columna = 15; columna <= 100; columna += 3)
		{
			mapa[fila][columna] = PARED;
		}
	}
}

void agregar_cajas(int mapa[FILAS][COLUMNAS])
{
	for (int columna = 20; columna <= 90; columna += 10)
	{
		for (int fila = 8; fila <= 30; fila += 5)
		{
			mapa[fila][columna] = PARED;
			mapa[fila][columna + 1] = PARED;
		}
	}
}

void abrir_puerta(int mapa[FILAS][COLUMNAS], int fila_centro)
{
	mapa[fila_centro][COLUMNAS - 1] = PUERTA;
	mapa[fila_centro + 1][COLUMNAS - 1] = PUERTA;
	mapa[fila_centro + 2][COLUMNAS - 1] = PUERTA;
}

void construir_mapas()
{
	generar_sala_vacia(mapa_platea);
	agregar_butacas(mapa_platea);
	abrir_puerta(mapa_platea, 18);

	generar_sala_vacia(mapa_escenario);
	abrir_puerta(mapa_escenario, 18);

	generar_sala_vacia(mapa_camerinos);
	agregar_cajas(mapa_camerinos);

	mapas[0] = mapa_platea;
	mapas[1] = mapa_escenario;
	mapas[2] = mapa_camerinos;
}
