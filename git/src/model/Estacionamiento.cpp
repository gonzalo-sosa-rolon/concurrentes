#include "Estacionamiento.h"

Estacionamiento::Estacionamiento(int tamanio, int precio) {
	this->tamanio = tamanio;
	this->precio = precio;

	this->cantidadDeAutos.crear((char*) PATH_MEMORIA_COMPARTIDA, 'a', 1);
	this->cantidadDeAutos.escribir(0, 0);

	this->cantidadFacturado.crear((char*) PATH_MEMORIA_COMPARTIDA, 'b', 1);
	this->cantidadFacturado.escribir(0, 0);

	this->plazas.crear((char*) PATH_MEMORIA_COMPARTIDA, 'S', tamanio);
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

int Estacionamiento::getTamanio() {
	return tamanio;
}

Estacionamiento::~Estacionamiento() {
	this->cantidadDeAutos.liberar();
	this->cantidadFacturado.liberar();
	this->plazas.liberar();
	eliminarLocks();
}

int Estacionamiento::getCantidadDeAutos() {
	int resultado;

	this->lockCantidadDeAutos->tomarLock();
	resultado = this->cantidadDeAutos.leer(0);
	this->lockCantidadDeAutos->liberarLock();

	return resultado;
}

void Estacionamiento::sumarUnAuto() {

	this->lockCantidadDeAutos->tomarLock();

	int resultado = this->cantidadDeAutos.leer(0);
	this->cantidadDeAutos.escribir(0, ++resultado);

	this->lockCantidadDeAutos->liberarLock();
}

void Estacionamiento::restarUnAuto() {

	this->lockCantidadDeAutos->tomarLock();

	int resultado = this->cantidadDeAutos.leer(0);
	this->cantidadDeAutos.escribir(0, --resultado);

	this->lockCantidadDeAutos->liberarLock();
}

int Estacionamiento::getCantidadFacturado() {
	int resultado;

	this->lockCantidadFacturado->tomarLock();
	resultado = this->cantidadFacturado.leer(0);
	this->lockCantidadFacturado->liberarLock();

	return resultado;
}

bool Estacionamiento::estaLLeno() {
	return (this->getCantidadDeAutos() == this->tamanio);
}

bool Estacionamiento::estaVacio() {
	return (this->getCantidadDeAutos() == 0);
}

bool Estacionamiento::ocuparPlaza(int pos, int tiempo, long autoId) {
	bool resultado = false;

	Plaza plaza = this->plazas.leer(pos);
	if (!plaza.getOcupado()) {
		plaza.ocupar(tiempo, time(NULL), autoId);
		this->plazas.escribir(pos, plaza);
		sumarUnAuto();
		resultado = true;
	}

	return resultado;
}

long Estacionamiento::desocuparLugar(int posicion) {

	Plaza plaza = this->getPlaza(posicion);

	if (plaza.getOcupado()) {
		this->facturar(plaza.getTiempoEstadia());
		plaza.setOcupado(false);
		this->plazas.escribir(posicion, plaza);
		this->restarUnAuto();
		return plaza.getAutoId();
	}
	return 0;
}

Lock* Estacionamiento::getLockPlaza(int pos) {
	return this->lockPlazas[pos];
}

Plaza Estacionamiento::getPlaza(int pos) {
	return this->plazas.leer(pos);
}

void Estacionamiento::facturar(int tiempo) {

	int cantidadFacturada = tiempo * this->precio;
	this->incrementarFacturacion(cantidadFacturada);
}

void Estacionamiento::incrementarFacturacion(int cantidadFacturada) {
	int resultado = this->cantidadFacturado.leer(0) + cantidadFacturada;
	this->cantidadFacturado.escribir(0, resultado);
}

void Estacionamiento::innitLocks() {

	lockCantidadFacturado = new Lock((char*) "lockCantidadFacturado");
	lockCantidadDeAutos = new Lock((char*) "lockCantidadDeAutos");

	lockPlazas = new Lock*[tamanio];

	for (int i = 0; i < tamanio; i++) {
		lockPlazas[i] = new Lock(getNombreLockPlaza(i));
	}
}

void Estacionamiento::eliminarLocks() {

	delete lockCantidadFacturado;
	delete lockCantidadDeAutos;

	for (int i = 0; i < tamanio; i++) {
		delete lockPlazas[i];
	}
	delete lockPlazas;
}

char* Estacionamiento::getNombreLockPlaza(int i) {
	stringstream lockPlaza;
	lockPlaza << "plaza_" << i + 1;

	return (char*) lockPlaza.str().c_str();
}
