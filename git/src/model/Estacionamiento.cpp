#include "Estacionamiento.h"

Estacionamiento::Estacionamiento(int tamanio, double precio) {
	this->tamanio = tamanio;
	this->precio = precio;

	this->plazas.crear((char*)"README.md", 'S', tamanio);

	innitLocks();
}


//TODO esto no se si va asi
int Estacionamiento::crearOAtacharte() {
	return this->plazas.crear((char*)"README.md", 'S', tamanio);
}

Estacionamiento::~Estacionamiento() {
	this->plazas.liberar();
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

	this->lockPlazas->tomarLock();

	for (int i = 0; i < tamanio; i++) {
		if (!this->plazas.leer(i).getOcupado()) {
			this->plazas.leer(i).ocupar(tiempo, 0); //TODO ver el tema de la hora de ingreso
			resultado = true;
		}
	}

	this->lockPlazas->liberarLock();
	return resultado;
}

// TODO esto.... puede que no se haga asi
bool Estacionamiento::desocuparLugar() {
	bool resultado = false;
//	int tiempoAFacturar = 0;
//
//	for (int i = 0; i < tamanio; i++) {
//		this->lockPlazas[i]->tomarLock();
//
//		if (this->plazas[i].getOcupado()) {
//			if (this->plazas[i].deseaIrse(0)) { //TODO pasarle el tiempo actual
//				tiempoAFacturar = this->plazas[i].getTiempoEstadia();
//				resultado = true;
//			}
//		}
//
//		this->lockPlazas[i]->liberarLock();
//	}
//
//	if (resultado) {
//		this->facturar(tiempoAFacturar);
//	}
//
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

	lockPlazas = new Lock((char*) "lockPlazas");
}

char* Estacionamiento::getNombreLockPlaza(int i) {
	string lockPlaza = "plaza_" + StringUtil::intToString(i + 1);

	return (char*) lockPlaza.c_str();
}
