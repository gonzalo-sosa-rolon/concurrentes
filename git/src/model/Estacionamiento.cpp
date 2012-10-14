#include "Estacionamiento.h"

Estacionamiento::Estacionamiento(int tamanio, double precio) {
	this->tamanio = tamanio;
	this->precio = precio;
	this->cantidadDeAutos = 0;
	this->cantidadFacturado = 0;

	this->plazas.crear((char*)"README.md", 'S', tamanio);
	initPlazas();
	innitLocks();
}

void Estacionamiento::initPlazas() {
	Plaza plaza;
	plaza.incializar();
	for (int i = 0; i < tamanio; i++) {
		this->plazas.escribir(i, plaza);
	}
}

//TODO esto no se si va asi
int Estacionamiento::crearOAtacharte() {
	return this->plazas.crear((char*)"README.md", 'S', tamanio);
}

int Estacionamiento::getTamanio() {
	return tamanio;
}

Estacionamiento::~Estacionamiento() {
	this->plazas.liberar();
}

int Estacionamiento::getCantidadDeAutos() {
	int resultado;

	this->lockCantidadDeAutos->tomarLock();
	resultado = this->cantidadDeAutos;
	this->lockCantidadDeAutos->liberarLock();

	return resultado;
}

void Estacionamiento::sumarUnAuto() {

	this->lockCantidadDeAutos->tomarLock();
	this->cantidadDeAutos++;
	this->lockCantidadDeAutos->liberarLock();
}

void Estacionamiento::restarUnAuto() {

	this->lockCantidadDeAutos->tomarLock();
	this->cantidadDeAutos--;
	this->lockCantidadDeAutos->liberarLock();
}

double Estacionamiento::getCantidadFacturado() {
	double resultado;

	this->lockCantidadDeAutos->tomarLock();
	resultado = this->cantidadFacturado;
	this->lockCantidadDeAutos->liberarLock();

	return resultado;
}

bool Estacionamiento::estaLLeno() {
	return (this->getCantidadDeAutos() == this->tamanio);
}

bool Estacionamiento::estaVacio() {
	return (this->getCantidadDeAutos() == 0);
}

bool Estacionamiento::ocuparPlaza(int tiempo) {
	bool resultado = false;

	for (int i = 0; i < tamanio; i++) {
		Plaza p = this->plazas.leer(i);
		if (!p.getOcupado()) {
			p.ocupar(tiempo, time(NULL));
			this->plazas.escribir(i, p);
			sumarUnAuto();
			return true;
		}
	}

	return resultado;
}

bool Estacionamiento::desocuparLugar(int posicion) {

	Plaza plaza = this->getPlaza(posicion);

	if (plaza.getOcupado()) {
		this->facturar(plaza.getTiempoEstadia());
		this->restarUnAuto();
		plaza.setOcupado(false);
		return true;
	}
	return false;
}

int Estacionamiento::tomarLockPlazas() {
	return this->lockPlazas->tomarLock();
}

int Estacionamiento::liberarLockPlazas(){
	return this->lockPlazas->liberarLock();
}

Plaza Estacionamiento::getPlaza(int pos) {
	return this->plazas.leer(pos);
}

void Estacionamiento::facturar(int tiempo) {

	double cantidadFacturada = tiempo * this->precio;

	this->incrementarFacturacion(cantidadFacturada);
}

void Estacionamiento::incrementarFacturacion(double cantidadFacturada) {
	this->cantidadFacturado = this->cantidadFacturado + cantidadFacturada;
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
