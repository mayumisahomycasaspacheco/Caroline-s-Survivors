#pragma once
#include "Entidad.h"
#include <iostream>
#include <Windows.h>
using namespace std;
using namespace System;

class Drop : public Entidad
{
public:
	Drop(int x, int y);

	void dibujar() override;
	void borrar(int xanterior, int yanterior) override;
private:
};

Drop::Drop(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Drop::dibujar()
{
	Console::SetCursorPosition(x, y);
	cout << "*";
}

void Drop::borrar(int xanterior, int yanterior)
{
	Console::SetCursorPosition(xanterior, yanterior);
	cout << " ";
}

