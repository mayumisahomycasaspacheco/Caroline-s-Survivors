#pragma once
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<cstdlib>
#include "Matrices.h"
#include "Casita_y_Carrito.h"
#include "Puerta_Secreta.h"
#include "Game_Manager.h"
using namespace std;
using namespace System;

void configurar_ventana()
{
	Console::Title = "Coraline's Survivos";
	Console::CursorVisible = false;

	try
	{
		Console::SetBufferSize(COLUMNAS + 1, FILAS + 5);
		Console::SetBufferSize(COLUMNAS, FILAS + 2);
	}

	catch (Exception^)
	{

	}
}

void centrar_texto(string texto, int fila)
{
	int x = (COLUMNAS - (int)texto.length()) / 2;
	Console::SetCursorPosition(x, fila);
	cout << texto;
}

void dibujar_titulo()
{
	string palabra1[5] = {
		"  ____ ___  ____      _    _     ___ _   _ _____ _ ____",
		" / ___/ _ \\|  _ \\    / \\  | |   |_ _| \\ | | ____( ) ___|",
		"| |  | | | | |_) |  / _ \\ | |    | ||  \\| |  _| |/\\___ \\",
		"| |__| |_| |  _ <  / ___ \\| |___ | || |\\  | |___   ___) |",
		" \\____\\___/|_| \\_\\/_/   \\_\\_____|___|_| \\_|_____| |____/"
	};

	string palabra2[5] = {
		" ____  _   _ ______     _______     _____  ____  ____",
		"/ ___|| | | |  _ \\ \\   / /_ _\\ \\   / / _ \\|  _ \\/ ___|",
		"\\___ \\| | | | |_) \\ \\ / / | | \\ \\ / / | | | |_) \\___ \\",
		" ___) | |_| |  _ < \\ V /  | |  \\ V /| |_| |  _ < ___) |",
		"|____/ \\___/|_| \\_\\ \\_/  |___|  \\_/  \\___/|_| \\_\\____/"
	};

	int x = (COLUMNAS - 57) / 2;

	Console::ForegroundColor = ConsoleColor::Yellow;

	for (int i = 0; i < 5; i++)
	{
		Console::SetCursorPosition(x, 2 + i);
		cout << palabra1[i];
	}

	for (int i = 0; i < 5; i++)
	{
		Console::SetCursorPosition(x, 2 + 5 + 1 + i);
		cout << palabra2[i];
	}

	Console::ForegroundColor = ConsoleColor::Gray;
}

void dibujar_descripcion()
{
	Console::ForegroundColor = ConsoleColor::Gray;

	centrar_texto("Coraline crossed the little door and found an other world full of wonders...", 15);
	centrar_texto("...but every wonder hides a danger. Clear each room, collect the drops,", 16);
	centrar_texto("level up, and escape before the dogs catches you.", 17);

	Console::ForegroundColor = ConsoleColor::DarkGray;
	centrar_texto("Move: W A S D | Shoot: SPACE or the arrow keys", 19);

	Console::ForegroundColor = ConsoleColor::Gray;
}

void dibujar_opciones()
{
	Console::ForegroundColor = ConsoleColor::White;

	centrar_texto("1. Play", 22);
	centrar_texto("2. Credits", 23);
	centrar_texto("3. Exit", 24);

	Console::ForegroundColor = ConsoleColor::Gray;
	centrar_texto("Choose an option (1-3", 27);
}

void mostrar_creditos()
{
	system("cls");

	Console::ForegroundColor = ConsoleColor::Yellow;
	centrar_texto("CREDITS", 5);

	Console::ForegroundColor = ConsoleColor::Gray;
	centrar_texto("Inspired by Coraline (Neil Gaiman / Laika", 8);
	centrar_texto("Made for miauyummii", 9);

	Console::ForegroundColor = ConsoleColor::DarkGray;
	centrar_texto("Press any key to go back to the menu...", 22);
	Console::ForegroundColor = ConsoleColor::Gray;

	limpiar_buffer_teclado();
	_getch();
}

void jugar_con_lore()
{
	Console::ForegroundColor = ConsoleColor::Gray;
	system("cls");

	casita(7, 1);
	carrito(95, 52, 23);
	personaje(75, 20, 19, 7, 1, 52, 23);

	system("cls");

	int cortina_x = 50;
	int cortina_y = 5;
	int puerta_x = 5;
	int puerta_y = 23;

	cortina(cortina_x, cortina_y);
	puertita(puerta_x, puerta_y);
	personaje_va_puerta(80, puerta_x + 8, 21, cortina_x, cortina_y, puerta_x, puerta_y);

	system("cls");

	Game_Manager juego;
	juego.jugar();
}

void menu_principal()
{
	configurar_ventana();

	char opcion;
	bool opcion_invalida = false;

	do
	{
		system("cls");

		dibujar_titulo();
		dibujar_descripcion();
		dibujar_opciones();

		if (opcion_invalida)
		{
			Console::ForegroundColor = ConsoleColor::Red;
			centrar_texto("Invalid option. Please press 1, 2, or 3.", 29);
			Console::ForegroundColor = ConsoleColor::Gray;
		}

		limpiar_buffer_teclado();
		opcion = _getch();

		if (opcion == '1')
		{
			opcion_invalida = false;
			jugar_con_lore();
		}

		else if (opcion == '2')
		{
			opcion_invalida = false;
			mostrar_creditos();
		}

		else if (opcion == '3')
		{
			opcion_invalida = false;
		}

		else
		{
			opcion_invalida = true;
		}
	}

	while (opcion != '3');

	system("cls");
	Console::ForegroundColor = ConsoleColor::Gray;
	centrar_texto("Thanks for playing!", 15);
	Console::SetCursorPosition(0, 20);
}