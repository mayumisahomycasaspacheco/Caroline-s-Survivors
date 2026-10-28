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

void Game_Manager::comprobar_colisiones()
{
	for (int i = 0; i < cantidad_perros; i++)
	{
		if (!perros[i]->esta_vivo())
		{
			continue;
		}

		for (int j = 0; j < coraline->getcantidad_proyectiles(); j++)
		{
			Proyectil* proyectil = coraline->getproyectiles()[j];

			if (proyectil->getdistancia_recorrida() <= 0)
			{
				continue;
			}

			bool solapax = proyectil->getX() >= perros[i]->getX() + PERRO_HITBOX_OFFSET_X && proyectil->getX() < perros[i]->getX() + PERRO_HITBOX_OFFSET_X + PERRO_HITBOX_ANCHO;
			bool solapay = proyectil->getY() >= perros[i]->getY() && proyectil->getY() < perros[i]->getY() + PERRO_HITBOX_ALTO;

			if (solapax && solapay)
			{
				perros[i]->recibir_danio(coraline->getdanio_arma());
				perros[i]->ralentizar(coraline->getralentizacion_arma());

				proyectil->borrar(proyectil->getX(), proyectil->getY());
				proyectil->detener();

				if (!perros[i]->esta_vivo())
				{
					perros[i]->borrar(perros[i]->getX(), perros[i]->getY(), mapa_actual);
					agregar_drops(perros[i]->getX(), perros[i]->getY());
				}

				break;
			}
		}
	}
}

void Game_Manager::comprobar_danio_a_coraline()
{
	if (invulnerable > 0)
	{
		invulnerable--;
		return;
	}

	for (int i = 0; i < cantidad_perros; i++)
	{
		if (!perros[i]->esta_vivo())
		{
			continue;
		}

		bool solapax = coraline->getX() < perros[i]->getX() + PERRO_HITBOX_OFFSET_X + PERRO_HITBOX_ANCHO && coraline->getX() + 3 > perros[i]->getX() + PERRO_HITBOX_OFFSET_X;
		bool solapay = coraline->getY() < perros[i]->getY() + PERRO_HITBOX_ALTO && coraline->getY() + 3 > perros[i]->getY();

		if (solapax && solapay)
		{
			coraline->recibir_danio(perros[i]->getdanio());
			invulnerable = 20;
			break;
		}
	}
}

bool Game_Manager::tocar_puerta()
{
	for (int fila = 0; fila < 3; fila++)
	{
		for (int columna = 0; columna < 4; columna++)
		{
			int mapaX = coraline->getX() + columna;
			int mapaY = coraline->getY() + fila;

			if (mapaX < 0 || mapaX >= COLUMNAS || mapaY < 0 || mapaY >= FILAS)
			{
				continue;
			}

			if (mapa_actual[mapaY][mapaX] == PUERTA)
			{
				return true;
			}
		}
	}
	return false;
}

void Game_Manager::redibujar_todo()
{
	Console::Clear();
	interfaz->dibujar_mapa(mapa_actual);
	coraline->dibujar();
	interfaz->dibujar_HUD(coraline);
	interfaz->dibujar_objetivo(mapa_indice + 1, TOTAL_SALAS, perros_vivos());
}

bool Game_Manager::avanzar_sala()
{
	liberar_perros();
	liberar_drops();

	mapa_indice++;
	
	if (mapa_indice >= TOTAL_SALAS)
	{
		return true;
	}

	mapa_actual = mapas[mapa_indice];
	coraline->setX(spawnx[mapa_indice]);
	coraline->setY(spawny[mapa_indice]);
	invulnerable = 0;

	redibujar_todo();
	crear_perros_en_sala(perros_por_sala[mapa_indice]);
	return false;
}

bool Game_Manager::jugar()
{
	interfaz->configurar_consola();
	redibujar_todo();
	crear_perros_en_sala(perros_por_sala[0]);

	while (true)
	{
		int xanterior = coraline->getX();
		int yanterior = coraline->getY();

		coraline->mover(mapa_actual);
		coraline->borrar(xanterior, yanterior);

		if (coraline->getvida() <= 0)
		{
			jugador_murio = true;
			break;
		}

		if (perros_vivos() == 0 && mapa_indice == TOTAL_SALAS - 1)
		{
			pantalla_victoria();
			return true;
		}

		if (tocar_puerta() && perros_vivos() == 0)
		{
			pantalla_nivel_superado(mapa_indice + 1, TOTAL_SALAS);
			if (avanzar_sala())
			{
				break;
			}
			continue;
		}

		actualizar_perros();
		comprobar_danio_a_coraline();
		actualizar_proyectiles();
		comprobar_colisiones();
		actualizar_drops();

		for (int i = 0; i < cantidad_drops; i++)
		{
			if (drops[i] != nullptr)
			{
				drops[i]->dibujar();
			}
		}

		bool coraline_visible = (invulnerable == 0) || ((invulnerable / 3) % 2 == 0);

		if (coraline_visible)
		{
			coraline->dibujar();
		}

		coraline->limpiar_proyectiles();

		interfaz->dibujar_HUD(coraline);
		interfaz->dibujar_objetivo(mapa_indice + 1, TOTAL_SALAS, perros_vivos());

		Sleep(50);
	}

	if (jugador_murio)
	{
		pantalla_derrota();
		return false;
	}

	pantalla_victoria();
	return true;
}