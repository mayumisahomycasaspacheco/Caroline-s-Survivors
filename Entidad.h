#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;
using namespace System;

class Entidad
{
protected:
	string nombre;
	string descripcion;
	int x;
	int y;
public:
	Entidad();
	virtual ~Entidad();

	string getnombre();
	string getdescripcion();
	int getX();
	int getY();

	void setnombre(string nombre);
	void setdescripcion(string descripcion);
	void setX(int x);
	void setY(int y);

	virtual void mover();
	virtual void borrar(int xanterior, int yanterior);
	virtual void dibujar();
};

Entidad::Entidad()
{
	nombre = "";
	descripcion = "";
	x = 0;
	y = 0;
}

Entidad::~Entidad()
{
}

string Entidad::getnombre()
{
	return nombre;
}

string Entidad::getdescripcion()
{
	return descripcion;
}

int Entidad::getX()
{
	return x;
}

int Entidad::getY()
{
	return y;
}

void Entidad::setnombre(string nombre)
{
	this->nombre = nombre;
}

void Entidad::setdescripcion(string descripcion)
{
	this->descripcion = descripcion;
}

void Entidad::setX(int x)
{
	this->x = x;
}

void Entidad::setY(int y)
{
	this->y = y;
}

void Entidad::mover()
{
}

void Entidad::borrar(int xanterior, int yanterior)
{
}

void Entidad::dibujar()
{
}