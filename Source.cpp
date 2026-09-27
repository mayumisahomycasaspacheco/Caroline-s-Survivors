#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#include "casita_y_carrito.h"
#include "puerta_secreta.h"

using namespace std;
using namespace System;

int main()
{
	//Escena 1
	casita(7, 1);
	carrito(95, 52, 23);
	personaje(75, 20, 19, 7, 1, 52, 23);

	system("cls");

	//Escena 2
	int cortina_x = 50;
	int cortina_y = 5;
	int puerta_x = 5;
	int puerta_y = 23;

	cortina(cortina_x, cortina_y);
	puertita(puerta_x, puerta_y);

	personaje_va_puerta(80, puerta_x + 8, 21, cortina_x, cortina_y, puerta_x, puerta_y);

	system("cls");

	_getch();
	return 0;
}