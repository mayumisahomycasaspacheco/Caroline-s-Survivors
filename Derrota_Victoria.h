#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
using namespace System;

void limpiar_buffer_teclado()
{
	while (_kbhit())
	{
		_getch();
	}
}

void pantalla_derrota()
{
	Console::Clear();
	Console::SetCursorPosition(40, 15);
	cout << "====================================";
	Console::SetCursorPosition(40, 16);
	cout << "     Coraline fue atrapada...     ";
	Console::SetCursorPosition(40, 17);
	cout << "            GAME OVER";
	Console::SetCursorPosition(40, 18);
	cout << "====================================";
	Console::SetCursorPosition(40, 20);
	cout << "Presiona una tecla para salir...";
	Sleep(5000);
	limpiar_buffer_teclado();
	_getch();
}

void pantalla_nivel_superado(int sala_actual, int total_salas)
{
	Console::Clear();
	Console::SetCursorPosition(40, 15);
	cout << "====================================";
	Console::SetCursorPosition(40, 16);
	cout << "   Sala " << sala_actual << " de " << total_salas << " superada!";
	Console::SetCursorPosition(40, 17);
	cout << "====================================";
	Console::SetCursorPosition(40, 19);
	cout << "Presione una tecla para continuar...";
	Sleep(5000);
	limpiar_buffer_teclado();
	_getch();
}

void pantalla_victoria()
{
	Console::Clear();
	Console::SetCursorPosition(40, 15);
	cout << "====================================";
	Console::SetCursorPosition(40, 16);
	cout << " Coraline escapo del teatro. Ganaste!";
	Console::SetCursorPosition(40, 17);
	cout << "====================================";
	Console::SetCursorPosition(40, 19);
	cout << "Presiona una tecla para continuar...";
	Sleep(5000);
	limpiar_buffer_teclado();
	_getch();
}
