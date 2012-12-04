#include "Estacionamiento.h"
#include "Auto.h"
#include <stdlib.h>

const char* Estacionamiento::PATH_TOKEN_MEMORIA_COMPARTIDA = "/bin/ls";
const char* Estacionamiento::PATH_TOKEN_COLAS = "/bin/ps";

Estacionamiento::Estacionamiento(int tamanio, int precio, int cantidadEntradas,
		int cantidadSalidas) {
	this->tamanio = tamanio;
	this->precio = precio;
	this->cantidadEntradas = cantidadEntradas;
	this->cantidadSalidas = cantidadSalidas;

	this->cantidadDeAutos = 0;
	this->cantidadFacturado = 0;

	initPlazas();
	innitLocks();
}

void Estacionamiento::initPlazas() {
	for (int i = 0; i < tamanio; i++) {
		Plaza* plaza = new Plaza();
		plaza->incializar();
		this->plazas.push_back(plaza);
	}
}

int Estacionamiento::getTamanio() {
	return tamanio;
}

Estacionamiento::~Estacionamiento() {

	for (int i = 0; i < tamanio; i++) {
		delete plazas[i];
	}

	eliminarLocks();
}

int Estacionamiento::getCantidadDeAutos() {
	int resultado;
	int error = 0;

	error = this->lockCantidadDeAutos->tomarLock();

	if (error) {
		imprimirErrorLock();
		exit(error);
	}

	resultado = this->cantidadDeAutos;
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

	this->cantidadDeAutos++;

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

	this->cantidadDeAutos--;

	error = this->lockCantidadDeAutos->liberarLock();

	if (error) {
		imprimirErrorLock();
		exit(error);
	}
}

int Estacionamiento::getCantidadFacturado() {
	int resultado;

	int error = this->lockCantidadFacturado->tomarLock();

	resultado = this->cantidadFacturado;
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

	Plaza *plaza = this->plazas[pos];
	if (!plaza->getOcupado()) {
		//TODO ver por que no le pasan el tiempo aca
		plaza->ocupar(tiempo, time(NULL), autoId);
		resultado = true;
	}

	return resultado;
}

long Estacionamiento::desocuparLugar(int posicion) {

	Plaza* plaza = this->getPlaza(posicion);

	if (plaza->getOcupado()) {
		this->facturar(plaza->getTiempoEstadia());
		plaza->setOcupado(false);
		this->restarUnAuto();
		return plaza->getAutoId();
	}
	return 0;
}

Lock* Estacionamiento::getLockPlaza(int pos) {
	return this->lockPlazas[pos];
}

Plaza *Estacionamiento::getPlaza(int pos) {
	return this->plazas[pos];
}

void Estacionamiento::facturar(int segundos) {

	int cantidadFacturada = segundos * this->precio
			/ ParserParametros::SEGUNDOS_POR_HORA_DEFAULT;
	this->incrementarFacturacion(cantidadFacturada);
}

void Estacionamiento::incrementarFacturacion(int cantidadFacturada) {
	this->cantidadFacturado += cantidadFacturada;
}

void Estacionamiento::innitLocks() {

	lockCantidadFacturado = new Lock((char*) "lockCantidadFacturado");
	lockCantidadDeAutos = new Lock((char*) "lockCantidadDeAutos");

	lockPlazas = new Lock*[tamanio];

	for (int i = 0; i < tamanio; i++) {
		lockPlazas[i] = new Lock(getNombreLockPlaza(i));
	}
}

int Estacionamiento::seleccionarPlaza(int tiempo, long autoId) {

	int resultado = -1;

	for (int i = 0; i < this->getTamanio(); i++) {
		Lock* lockPlaza = this->tomarLockPlaza(i);

		if (!this->getPlaza(i)->getOcupado()) {

			this->ocuparPlaza(i, tiempo, autoId);
			resultado = i;
			logOcupePlaza(i, autoId);

			liberarLockPlaza(i, lockPlaza);
			resultado = true;

			break;
		}
		liberarLockPlaza(i, lockPlaza);
	}

	return resultado;
}

void Estacionamiento::logOcupePlaza(int nroPlaza, int idAuto) {
	stringstream info;
	info << "Se ocupa la plaza [" << nroPlaza << "] Id del auto [" << idAuto
			<< "]" << " Cantidad de autos en el estacionamiento ["
			<< this->getCantidadDeAutos() << "]";
	Log::getLog()->logMensaje(info.str());
}

Lock* Estacionamiento::tomarLockPlaza(int nroDePlaza) {
	Lock* lockPlaza = this->getLockPlaza(nroDePlaza);
	int error = lockPlaza->tomarLock();

	if (error) {
		stringstream errorMsg;
		errorMsg
				<< "Entrada : Se produjo un error al intentar tomar el lock de la plaza "
				<< nroDePlaza + 1 << endl;
		Log::getLog()->logError(errorMsg.str());
		exit(error);
	}
	return lockPlaza;
}

void Estacionamiento::liberarLockPlaza(int nroDePlaza, Lock* lockPlaza) {
	int error = lockPlaza->liberarLock();

	if (error) {
		stringstream errorMsg;
		errorMsg
				<< "Entrada : Se produjo un error al intentar liberar el lock de la plaza "
				<< nroDePlaza + 1 << endl;
		Log::getLog()->logError(errorMsg.str());
		exit(error);
	}
}

/**
 * (cantidad < tamanio) ? cantidad++
 */
bool Estacionamiento::solicitarLugar() {

	bool resultado = false;

	int error = this->lockCantidadDeAutos->tomarLock();

	if (error) {
		imprimirErrorLock();
		exit(error);
	}

	int cantidad = this->cantidadDeAutos;

	if (cantidad < tamanio) {
		this->cantidadDeAutos++;
		resultado = true;
	}

	error = this->lockCantidadDeAutos->liberarLock();

	if (error) {
		imprimirErrorLock();
		exit(error);
	}

	return resultado;
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
	Log::getLog()->logError(
			"Error: se ha producido un error al intentar tomar o liberar un lock.");
}

void Estacionamiento::imprimirError(int error) {

	if (error == ERROR_FTOK) {
		Log::getLog()->logError(
				"Error:  se ha producido un error al intentar crear la memoria compartida. Verifique que el archivo seleccionado para el token exista");
	} else if (error == ERROR_SHMGET) {
		Log::getLog()->logError(
				"Error: se ha producido un error al intentar alocar memoria compartida");
	} else if (error == ERROR_SHMAT) {
		Log::getLog()->logError(
				"Error: se ha producido un error al intentar adjuntar el segmento de memoria compartida");
	} else {
		Log::getLog()->logError("Se ha producido un error desconocido");
	}
}
