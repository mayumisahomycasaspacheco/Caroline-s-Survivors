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
	cout << "        Coraline was trapped...     ";
	Console::SetCursorPosition(40, 17);
	cout << "            GAME OVER";
	Console::SetCursorPosition(40, 18);
	cout << "====================================";
	Console::SetCursorPosition(40, 20);
	cout << "Press any key to exit...";
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
	cout << "   Room " << sala_actual << " of " << total_salas << " overcome!";
	Console::SetCursorPosition(40, 17);
	cout << "====================================";
	Console::SetCursorPosition(40, 19);
	cout << "Press any key to exit...";
	Sleep(5000);
	limpiar_buffer_teclado();
	_getch();
}

void pantalla_victoria()
{
	Console::Clear();
	Console::SetCursorPosition(40, 15);
	cout << "==============================================";
	Console::SetCursorPosition(40, 16);
	cout << " Coraline escaped from the theater. You won.!";
	Console::SetCursorPosition(40, 17);
	cout << "==============================================";
	Console::SetCursorPosition(40, 19);
	cout << "Press any key to exit...";
	Sleep(5000);
	limpiar_buffer_teclado();
	_getch();
}
