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
}

int Estacionamiento::getCantidadDeAutos() {
	int resultado;

	resultado = this->cantidadDeAutos;

	return resultado;
}

void Estacionamiento::sumarUnAuto() {
	this->cantidadDeAutos++;
}

void Estacionamiento::restarUnAuto() {
	this->cantidadDeAutos--;
}

int Estacionamiento::getCantidadFacturado() {
	int resultado;
	resultado = this->cantidadFacturado;
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
		//this->restarUnAuto();
		return plaza->getAutoId();
	}
	return 0;
}

void Estacionamiento::salirDelEstacionamiento() {
	this->restarUnAuto();
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

int Estacionamiento::seleccionarPlaza(int tiempo, long autoId) {

	for (int i = 0; i < this->getTamanio(); i++) {
		if (!this->getPlaza(i)->getOcupado()) {

			this->ocuparPlaza(i, tiempo, autoId);
			logOcupePlaza(i, autoId);

			return i;
		}
	}

	return -1;
}

void Estacionamiento::logOcupePlaza(int nroPlaza, int idAuto) {
	stringstream info;
	info << "Se ocupa la plaza [" << nroPlaza << "] Id del auto [" << idAuto
			<< "]" << " Cantidad de autos en el estacionamiento ["
			<< this->getCantidadDeAutos() << "]";
	Log::getLog()->logMensaje(info.str());
}


/**
 * (cantidad < tamanio) ? cantidad++
 */
bool Estacionamiento::solicitarLugar() {

	if (this->cantidadDeAutos < tamanio) {
		this->cantidadDeAutos++;
		return true;
	}

	return false;
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
