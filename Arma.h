#pragma once
#include <iostream>
using namespace std;

class Proyectil;

class Arma
{
protected:
	string nombre;
	int danio;
public:
	Arma();
	virtual ~Arma();
	string getnombre();
	int getdanio();
	virtual Proyectil* atacar(int x, int y, int dx, int dy);

	virtual int getralentizacion();
};

Arma::Arma()
{
	nombre = "";
	danio = 0;
}

Arma::Arma()
{
}

string Arma::getnombre()
{
	return nombre;
}

int Arma::getdanio()
{
	return danio;
}

Proyectil* Arma::atacar(int x, int y, int dx, int dy)
{
	return nullptr;
}

int Arma::getralentizacion()
{
	return 0;
}
