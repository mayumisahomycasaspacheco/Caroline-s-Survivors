#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;
using namespace System;

void pantalla_carga()
{
	system("cls");

	Console::ForegroundColor = ConsoleColor::White;
	Console::SetCursorPosition(55, 8);

	cout << "Caroline's Survivos" << endl;

	//Dibujo de la pantlla de carga

	for (int i = 0; i <= 4; i++)
	{
		Console::SetCursorPosition(40, 13);
		cout << "                    ";

		Console::SetCursorPosition(40, 13);
		cout << "Cargando";

		for (int j = 0; j < i; j++)
		{
			cout << ".......";
		}

		Sleep(1500);

	}

	system("cls");

}

int mostrar_menu()
{
	string opciones[4] = { "Play", "How to play", "Credits", "Exit" };

	int seleccion = 0;
	bool elegido = false;

	while (!elegido)
	{
		system("cls");

		Console::ForegroundColor = ConsoleColor::Cyan;

		SetConsoleOutputCP(65001);
	}
}
