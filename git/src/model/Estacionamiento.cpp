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

	int error;
	error = this->cantidadDeAutos.crear(
			Estacionamiento::PATH_TOKEN_MEMORIA_COMPARTIDA, 'a', 1);

	if (error) {
		imprimirError(error);
		exit(error);
	}

	this->cantidadDeAutos.escribir(0, 0);

	error = this->cantidadFacturado.crear(
			Estacionamiento::PATH_TOKEN_MEMORIA_COMPARTIDA, 'b', 1);

	if (error) {
		imprimirError(error);
		exit(error);
	}

	this->cantidadFacturado.escribir(0, 0);

	error = this->plazas.crear(Estacionamiento::PATH_TOKEN_MEMORIA_COMPARTIDA,
			'S', tamanio);

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

	int cantidadFacturada = segundos * this->precio
			/ ParserParametros::SEGUNDOS_POR_HORA_DEFAULT;
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

bool Estacionamiento::ocuparPlaza(Auto *automovil) {

	bool resultado = false;

	for (int i = 0; i < this->getTamanio(); i++) {
		Lock* lockPlaza = this->tomarLockPlaza(i);

		if (!this->getPlaza(i).getOcupado()) {

			this->ocuparPlaza(i, automovil->getTiempo(), automovil->getId());
			automovil->setNumeroPlaza(i);
			logOcupePlaza(i, automovil->getId());

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

	int cantidad = this->cantidadDeAutos.leer(0);

	if (cantidad < tamanio) {
		this->cantidadDeAutos.escribir(0, ++cantidad);
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
