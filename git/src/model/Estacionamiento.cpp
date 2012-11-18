#include "Estacionamiento.h"
#include <stdlib.h>

const char* Estacionamiento::PATH_TOKEN_MEMORIA_COMPARTIDA = "/bin/ls";

Estacionamiento::Estacionamiento(int tamanio, int precio) {
	this->tamanio = tamanio;
	this->precio = precio;

	int error;
	error = this->cantidadDeAutos.crear(Estacionamiento::PATH_TOKEN_MEMORIA_COMPARTIDA, 'a', 1);

	if (error) {
		imprimirError(error);
		exit(error);
	}

	this->cantidadDeAutos.escribir(0, 0);

	error = this->cantidadFacturado.crear(Estacionamiento::PATH_TOKEN_MEMORIA_COMPARTIDA, 'b', 1);

	if (error) {
		imprimirError(error);
		exit(error);
	}

	this->cantidadFacturado.escribir(0, 0);

	error = this->plazas.crear(Estacionamiento::PATH_TOKEN_MEMORIA_COMPARTIDA, 'S', tamanio);

	if (error) {
		imprimirError(error);
		exit(error);
	}

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

	cout << getpid() << endl;
}

int Estacionamiento::getCantidadDeAutos() {
	int resultado;
	int error = 0;

	error = this->lockCantidadDeAutos->tomarLock();

	if (error) {
		imprimirErrorLock();
		exit(error);
	}

	resultado = this->cantidadDeAutos.leer(0);
	error = this->lockCantidadDeAutos->liberarLock();

	if (error) {
		imprimirErrorLock();
		exit(error);
	}

	return resultado;
}

void Estacionamiento::sumarUnAuto() {

	int error = this->lockCantidadDeAutos->tomarLock();

	if (error) {
		imprimirErrorLock();
		exit(error);
	}

	int resultado = this->cantidadDeAutos.leer(0);
	this->cantidadDeAutos.escribir(0, ++resultado);

	error = this->lockCantidadDeAutos->liberarLock();

	if (error) {
		imprimirErrorLock();
		exit(error);
	}
}

void Estacionamiento::restarUnAuto() {

	int error = this->lockCantidadDeAutos->tomarLock();

	if (error) {
		imprimirErrorLock();
		exit(error);
	}

	int resultado = this->cantidadDeAutos.leer(0);
	this->cantidadDeAutos.escribir(0, --resultado);

	error = this->lockCantidadDeAutos->liberarLock();

	if (error) {
		imprimirErrorLock();
		exit(error);
	}
}

int Estacionamiento::getCantidadFacturado() {
	int resultado;

	int error = this->lockCantidadFacturado->tomarLock();

	resultado = this->cantidadFacturado.leer(0);
	error = this->lockCantidadFacturado->liberarLock();

	if (error) {
		imprimirErrorLock();
		exit(error);
	}

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

void Estacionamiento::facturar(int segundos) {

	int cantidadFacturada = segundos * this->precio / ParserParametros::SEGUNDOS_POR_HORA_DEFAULT;
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


void Estacionamiento::imprimirErrorLock() {
	Log::getLog()->logError("Error: se ha producido un error al intentar tomar o liberar un lock.");
}

void Estacionamiento::imprimirError(int error) {

	if (error == ERROR_FTOK) {
		Log::getLog()->logError("Error:  se ha producido un error al intentar crear la memoria compartida. Verifique que el archivo seleccionado para el token exista");
	} else if (error == ERROR_SHMGET) {
		Log::getLog()->logError("Error: se ha producido un error al intentar alocar memoria compartida");
	} else if (error == ERROR_SHMAT) {
		Log::getLog()->logError("Error: se ha producido un error al intentar adjuntar el segmento de memoria compartida");
	} else {
		Log::getLog()->logError("Se ha producido un error desconocido");
	}
}
