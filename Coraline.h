#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Jugador.h"
#include "Tirachinas.h"
using namespace std;
using namespace System;

void arte(int x, int y)
{
	string lineas[3] = {
		" O ",
		"/|\\",
		"/ \\"
	};

	Console::SetCursorPosition(x, y);
	cout << lineas[0];
	Console::SetCursorPosition(x, y + 1);
	cout << lineas[1];
	Console::SetCursorPosition(x, y + 2);
	cout << lineas[2];
}

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
	void mover();

	bool getjugado();
	void setjugado(bool jugado);

	int getdanio_arma();
	int getralentizacion_arma();

	Proyectil** getproyectiles();
	int getcantidad_proyectiles();

	void disparar(int dx, int dy);
	void limpiar_proyectiles();

	string* getarte(int x, int y) override;
	int getarte_alto(int x, int y) override;
};

