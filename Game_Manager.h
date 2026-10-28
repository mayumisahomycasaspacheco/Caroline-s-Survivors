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
	delete coraline;
	delete interfaz;
}

void Game_Manager::agregar_drops(int x, int y)
{
	int dropX = x;
	int dropY = y;

	if (dropX < 0 || dropX >= COLUMNAS || dropY < 0 || dropY >= FILAS || mapa_actual[dropY][dropX] != VACIO)
	{
		bool encontrada = false;

		for (int radio = 1; radio <= 6 && !encontrada; radio++)
		{
			for (int dy = -radio; dy <= radio && !encontrada; dy++)
			{
				for (int dx = -radio; dx <= radio && !encontrada; dx++)
				{
					int nx = x + dx, ny = y + dy;

					if (nx < 1 || nx >= COLUMNAS - 1 || ny < 1 || ny >= FILAS - 1)
					{
						continue;
					}

					if (mapa_actual[ny][nx] == VACIO)
					{
						dropX = nx;
						dropY = ny;
						encontrada = true;
					}
				}
			}
		}
	}

	Drop** nuevos = new Drop * [cantidad_drops + 1];
	
	for (int i = 0; i < cantidad_drops; i++)
	{
		nuevos[i] = drops[i];
	}

	nuevos[cantidad_drops] = new Drop(dropX, dropY);

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
	for (int dy = 0; dy < PERRO_HITBOX_ALTO; dy++)
	{
		for (int dx = 0; dx < PERRO_HITBOX_ANCHO; dx++)
		{
			int mx = x + PERRO_HITBOX_OFFSET_X + dx, my = y + dy;
			
			if (mx < 0 || mx >= COLUMNAS || my < 0 || my >= FILAS)
			{
				return false;
			}

			if (mapa[my][mx] != VACIO)
			{
				return false;
			}
		}
	}

	int hitboxX = x + PERRO_HITBOX_OFFSET_X;
	bool cercaDeCoraline = (hitboxX < coralineX + 10 && hitboxX + PERRO_HITBOX_ANCHO > coralineX - 10) && (y < coralineY + 8 && y + PERRO_HITBOX_ALTO > coralineY - 8);
	
	if (cercaDeCoraline)
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

		int xAnterior = perros[i]->getX();
		int yAnterior = perros[i]->getY();

		perros[i]->mover(coraline->getX(), coraline->getY());
		perros[i]->borrar(xAnterior, yAnterior, mapa_actual);
		perros[i]->dibujar();
	}
}

void Game_Manager::actualizar_proyectiles()
{
	for (int i = 0; i < coraline->getcantidad_proyectiles(); i++)
	{
		Proyectil* proyectil = coraline->getproyectiles()[i];

		int xanterior = proyectil->getX();
		int yanterior = proyectil->getY();

		proyectil->mover();
		proyectil->borrar(xanterior, yanterior);

		if (proyectil->getdistancia_recorrida() <= 0)
		{
			continue;
		}

		int mapaX = proyectil->getX();
		int mapaY = proyectil->getY();

		bool fuera_de_limites = (mapaX < 0 || mapaX >= COLUMNAS || mapaY < 0 || mapaY >= FILAS);
		bool choco_pared = false;

		if (!fuera_de_limites)
		{
			if (mapa_actual[mapaY][mapaX] == PARED || mapa_actual[mapaY][mapaX] == OBSTACULO)
			{
				choco_pared = true;
			}
		}

		if (fuera_de_limites || choco_pared)
		{
			proyectil->detener();
		}

		else
		{
			proyectil->dibujar();
		}
	}
}