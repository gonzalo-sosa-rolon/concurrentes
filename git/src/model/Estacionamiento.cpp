#include "Estacionamiento.h"

Estacionamiento::Estacionamiento(int tamanio, double precio) {
	this->tamanio = tamanio;
	this->precio = precio;

	if (tamanio > 0) {
		this->plazas = new Plaza[tamanio];
	} else {
		this->plazas = NULL;
	}

	innitLocks();
}

Estacionamiento::~Estacionamiento() {
	if (this->plazas != NULL) {
		delete[] this->plazas;
		this->plazas = NULL;
	}
}

void Estacionamiento::incrementarCantidadDeAutos() {
	this->cantidadDeAutos++;
}

void Estacionamiento::reducirCantidadDeAutos() {
	this->cantidadDeAutos--;
}

int Estacionamiento::getCantidadDeAutos() {
	int resultado;

	resultado = this->cantidadDeAutos;

	return resultado;
}

double Estacionamiento::getCantidadFacturado() {
	return this->cantidadFacturado;
}

bool Estacionamiento::estaLLeno() {
	return this->getCantidadDeAutos() == this->tamanio;
}

void Estacionamiento::innitLocks() {

	lockCantidadFacturado = new Lock((char*)"lockCantidadFacturado");
	lockCantidadDeAutos = new Lock((char*)"lockCantidadDeAutos");

	lockPlazas = new Lock*[this->tamanio];

	for (int i = 0; i < this->tamanio; i++) {
		lockPlazas[i] = new Lock(getNombreLockPlaza(i));
	}
}

char* Estacionamiento::getNombreLockPlaza(int i) {
	string lockPlaza = "plaza_" + StringUtil::intToString(i + 1);

	return (char*)lockPlaza.c_str();
}
