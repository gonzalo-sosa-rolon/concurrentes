#include "Estacionamiento.h"

Estacionamiento::Estacionamiento(int tamanio, double precio) {
	this->tamanio = tamanio;
	this->precio = precio;

	if (tamanio > 0) {
		this->plazas = new Plaza[tamanio];
		this->mutexPlazas = new Mutex[tamanio];
	} else {
		this->plazas = NULL;
		this->mutexPlazas = NULL;
	}
}

Estacionamiento::~Estacionamiento() {
	if (this->plazas != NULL) {
		delete[] this->plazas;
		this->plazas = NULL;
	}
}

void Estacionamiento::incrementarCantidadDeAutos() {
	this->mutexCantidadDeAutos.lock();
	this->cantidadDeAutos++;
	this->mutexCantidadDeAutos.unlock();
}

void Estacionamiento::reducirCantidadDeAutos() {
	this->mutexCantidadDeAutos.lock();
	this->cantidadDeAutos--;
	this->mutexCantidadDeAutos.unlock();
}

int Estacionamiento::getCantidadDeAutos() {
	int resultado;

	this->mutexCantidadDeAutos.lock();
	resultado = this->cantidadDeAutos;
	this->mutexCantidadDeAutos.unlock();

	return resultado;
}

double Estacionamiento::getCantidadFacturado() {
	return this->cantidadFacturado;
}

bool Estacionamiento::estaLLeno() {
	return this->getCantidadDeAutos() == this->tamanio;
}

