#pragma once
#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include "Coraline.h"
#include "Perro_Volador.h"
#include "Drop.h"
#include "Interfaz.h"
#include "Matrices.h"
#include "Derrota_Victoria.h"

using namespace std;
using namespace System;

class Game_Manager
{
private:
	Interfaz* interfaz;
	Coraline* coraline;
	Perro** perros;
	int cantidad_perros;
	Drop** drops;
	int cantidad_drops;
	int mapa_indice;
	int (*mapa_actual)[COLUMNAS];
	int invulnerable;
	bool jugador_murio;

	void agregar_drops(int x, int y);
	bool coraline_toca_drop(Drop* drop);
	void actualizar_drops();
	void liberar_drops();
	bool area_libre_para_perro(int mapa[FILAS][COLUMNAS], int x, int y, int coralineX, int coralineY);
	void crear_perros_en_sala(int cantidad);
	int perros_vivos();
	void liberar_perros();
	void actualizar_perros();
	void actualizar_proyectiles();
	void comprobar_colisiones();
	void comprobar_danio_a_coraline();
	bool tocar_puerta();
	bool avanzar_sala();
	void redibujar_todo();
public:
	Game_Manager();
	~Game_Manager();

	bool jugar();
};

Game_Manager::Game_Manager()
{
	construir_mapas();

	interfaz = new Interfaz();
	coraline = new Coraline(true);
	perros = nullptr;
	cantidad_perros = 0;
	drops = nullptr;
	cantidad_drops = 0;
	mapa_indice = 0;
	mapa_actual = mapas[0];
	invulnerable = 0;
	jugador_murio = false;

	coraline->setX(spawnx[0]);
	coraline->setY(spawny[0]);

	srand((unsigned int)time(0));
}

Game_Manager::~Game_Manager()
{
	liberar_perros();
	liberar_drops();
	delete interfaz;
	delete coraline;
}

void Game_Manager::agregar_drops(int x, int y)
{
	Drop** nuevos = new Drop * [cantidad_drops + 1];
	for (int i = 0; i < cantidad_drops; i++)
	{
		nuevos[i] = drops[i];
	}

	nuevos[cantidad_drops] = new Drop(x, y);

	delete[] drops;
	drops = nuevos;
	cantidad_drops++;

	drops[cantidad_drops - 1]->dibujar();
}

bool Game_Manager::coraline_toca_drop(Drop* drop)
{
	int cx = coraline->getX();
	int cy = coraline->getY();

	bool solapax = cx < drop->getX() + 1 && cx + 3 > drop->getX();
	bool solapay = cy < drop->getY() + 1 && cy + 3 > drop->getY();

	return solapax && solapay;
}

void Game_Manager::actualizar_drops()
{
	for (int i = 0; i < cantidad_drops; i++)
	{
		if (drops[i] == nullptr)
		{
			continue;
		}

		if (coraline_toca_drop(drops[i]))
		{
			drops[i]->borrar(drops[i]->getX(), drops[i]->getY());
			coraline->sumarxp(1);
			delete drops[i];
			drops[i] = nullptr;
		}

	}
}

void Game_Manager::liberar_drops()
{
	for (int i = 0; i < cantidad_drops; i++)
	{
		delete drops[i];
	}

	delete[] drops;
	drops = nullptr;
	cantidad_drops = 0;
}

bool Game_Manager::area_libre_para_perro(int mapa[FILAS][COLUMNAS], int x, int y, int coralineX, int coralineY)
{
	for (int dy = 0; dy < 4; dy++)
	{
		for (int dx = 0; dx < 16; dx++)
		{
			int mx = x + dx, my = y + dy;
			if (mx < 0 || mx >= COLUMNAS || my < 0 || my >= FILAS)
			{
				return false;
			}

			if (mapa[my][mx != VACIO])
			{
				return false;
			}
		}
	}

	bool cerca_de_coraline = (x < coralineX + 10 && x + 16 > coralineX - 10) && (y < coralineY + 8 && y + 4 > coralineY - 8);

	if (cerca_de_coraline)
	{
		return false;
	}

	return true;
}

void Game_Manager::crear_perros_en_sala(int cantidad)
{
	cantidad_perros = cantidad;

	perros = new Perro * [cantidad];

	for (int i = 0; i < cantidad; i++)
	{
		int rx = 0, ry = 0, intentos = 0;
		bool ok = false;

		while (!ok && intentos < 1000)
		{
			rx = rand() % (COLUMNAS - 20);
			ry = rand() % (FILAS - 8);
			ok = area_libre_para_perro(mapa_actual, rx, ry, coraline->getX(), coraline->getY());
			intentos++;
		}

		perros[i] = new Perro(rx, ry);
		perros[i]->dibujar();
	}
}

int Game_Manager::perros_vivos()
{
	int vivos = 0;

	for (int i = 0; i < cantidad_perros; i++)
	{
		if (perros[i]->esta_vivo())
		{
			vivos++;
		}
	}

	return vivos;
}

void Game_Manager::liberar_perros()
{
	if (perros == nullptr)
	{
		return;
	}

	for (int i = 0; i < cantidad_perros; i++)
	{
		delete perros[i];
	}

	delete[] perros;
	perros = nullptr;
	cantidad_perros = 0;
}

void Game_Manager::actualizar_perros()
{
	for (int i = 0; i < cantidad_perros; i++)
	{
		if (!perros[i]->esta_vivo())
		{
			continue;
		}
	}
}