#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
using namespace std;
using namespace System;

void cortina(int x, int y)
{
	string lineas[16] = {
"(IIIIIIIIIIIIIIIIIII)",
")'.'.'.':;:;:'.'.'.'(",
"('.'.'.;' | `:.'.'.')",
")'.'.';'  |  `:'.'.'(",
"('.'.;'   |   `:.'.')",
")'.';'____|____`:'.'(",
"(==@'     |     `@==)",
")'.:     @()     :.'(",
"('.'.   ()@()   .'.')",
")'.'.  ()@()@)  .'.'(",
"('.'.   _\\|/_   .'.')",
")'.'.  |-----|  .'.'(",
"('.'.___\\___/___.'.')",
")'.'============='.'(",
"('.'             '.')",
" ~                 ~"
	};

	Console::SetCursorPosition(x, y);
	cout << lineas[0];
	Console::SetCursorPosition(x, y + 1);
	cout << lineas[1];
	Console::SetCursorPosition(x, y + 2);
	cout << lineas[2];
	Console::SetCursorPosition(x, y + 3);
	cout << lineas[3];
	Console::SetCursorPosition(x, y + 4);
	cout << lineas[4];
	Console::SetCursorPosition(x, y + 5);
	cout << lineas[5];
	Console::SetCursorPosition(x, y + 6);
	cout << lineas[6];
	Console::SetCursorPosition(x, y + 7);
	cout << lineas[7];
	Console::SetCursorPosition(x, y + 8);
	cout << lineas[8];
	Console::SetCursorPosition(x, y + 9);
	cout << lineas[9];
	Console::SetCursorPosition(x, y + 10);
	cout << lineas[10];
	Console::SetCursorPosition(x, y + 11);
	cout << lineas[11];
	Console::SetCursorPosition(x, y + 12);
	cout << lineas[12];
	Console::SetCursorPosition(x, y + 13);
	cout << lineas[13];
	Console::SetCursorPosition(x, y + 14);
	cout << lineas[14];
	Console::SetCursorPosition(x, y + 15);
	cout << lineas[15];
}

void puertita(int x, int y)
{
	string lineas[5] = {
" ______ ",
"|.-\"\"-.|",
"| |  | |",
"| |  | |",
"|_|__|_|"
	};

	Console::SetCursorPosition(x, y);
	cout << lineas[0];
	Console::SetCursorPosition(x, y + 1);
	cout << lineas[1];
	Console::SetCursorPosition(x, y + 2);
	cout << lineas[2];
	Console::SetCursorPosition(x, y + 3);
	cout << lineas[3];
	Console::SetCursorPosition(x, y + 4);
	cout << lineas[4];
}

void personaje_va_puerta(int xinicial, int xfinal, int y, int cortina_x, int cortina_y, int puerta_x, int puerta_y)
{
	string lineas[8] = {
"  _",
"_[_]_",
" (_)",
"//:\\\\",
"\\|~|/",
" |||",
" |||",
" - -"
	};

	string espacios(10, ' ');

	for (int x = xinicial; x >= xfinal; x--)
	{
		for (int i = 0; i < 8; i++)
		{
			Console::SetCursorPosition(x, y + i);
			cout << lineas[i];
		}

		Sleep(100);

		if (x > xfinal)
		{
			for (int i = 0; i < 8; i++)
			{
				Console::SetCursorPosition(x, y + i);
				cout << espacios;
			}

			cortina(cortina_x, cortina_y);
			puertita(puerta_x, puerta_y);
		}
	}

	Sleep(1500);

	for (int i = 0; i < 8; i++)
	{
		Console::SetCursorPosition(xfinal, y + i);
		cout << espacios;
	}

	cortina(cortina_x, cortina_y);
	puertita(puerta_x, puerta_y);
}