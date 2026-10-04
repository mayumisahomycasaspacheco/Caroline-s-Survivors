#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#include "casita_y_carrito.h"
#include "puerta_secreta.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#include "Game_Manager.h"

using namespace std;
using namespace System;

int main()
{

	Game_Manager juego;
	juego.jugar();

	_getch();
	return 0;
}