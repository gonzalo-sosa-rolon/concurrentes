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

	this->lockCantidadDeAutos->tomarLock();
	resultado = this->cantidadDeAutos;
	this->lockCantidadDeAutos->liberarLock();

	return resultado;
}

double Estacionamiento::getCantidadFacturado() {
	double resultado;

	this->lockCantidadDeAutos->tomarLock();
	resultado = this->cantidadFacturado;
	this->lockCantidadDeAutos->liberarLock();

	return resultado;
}

bool Estacionamiento::estaLLeno() {
	return this->getCantidadDeAutos() == this->tamanio;
}

bool Estacionamiento::ocuparLugar(int tiempo) {
	bool resultado = false;

	for (int i = 0; i < tamanio; i++) {
		this->lockPlazas[i]->tomarLock();

		if (!this->plazas[i].getOcupado()) {
			this->plazas[i].ocupar(tiempo, 0); //ver el tema de la hora de ingreso
		}

		this->lockPlazas[i]->liberarLock();
	}

	return resultado;
}

bool Estacionamiento::desocuparLugar() {
	bool resultado = false;
	int tiempoAFacturar = 0;

	for (int i = 0; i < tamanio; i++) {
		this->lockPlazas[i]->tomarLock();

		if (this->plazas[i].getOcupado()) {
			if (this->plazas[i].deseaIrse(0)) { //TODO pasarle el tiempo actual
				tiempoAFacturar = this->plazas[i].getTiempoEstadia();
				resultado = true;
			}
		}

		this->lockPlazas[i]->liberarLock();
	}

	if (resultado) {
		this->facturar(tiempoAFacturar);
	}

	return resultado;
}


void Estacionamiento::facturar(int tiempo) {

	double cantidadFacturada = tiempo * this->precio;

	this->incrementarFacturacion(cantidadFacturada);
}

void Estacionamiento::incrementarFacturacion(double cantidadFacturada) {

	this->lockCantidadFacturado->tomarLock();
	this->cantidadFacturado = this->cantidadFacturado + cantidadFacturada;
	this->lockCantidadFacturado->liberarLock();
}

void Estacionamiento::innitLocks() {

	lockCantidadFacturado = new Lock((char*) "lockCantidadFacturado");
	lockCantidadDeAutos = new Lock((char*) "lockCantidadDeAutos");

	lockPlazas = new Lock*[this->tamanio];

	for (int i = 0; i < this->tamanio; i++) {
		lockPlazas[i] = new Lock(getNombreLockPlaza(i));
	}
}

char* Estacionamiento::getNombreLockPlaza(int i) {
	string lockPlaza = "plaza_" + StringUtil::intToString(i + 1);

	return (char*) lockPlaza.c_str();
}
