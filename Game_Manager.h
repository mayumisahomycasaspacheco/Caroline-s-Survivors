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
	Perro* perros;
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
public:
};