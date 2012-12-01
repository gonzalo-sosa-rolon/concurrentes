#include "Auto.h"
#include "../util/NumberUtil.h"
#include "../util/ParserParametros.h"


const int Auto::TIEMPO_ENTRAR = 2;
const int Auto::TIEMPO_SALIR = 3;
const int Auto::TIEMPO_LLEGAR_PLAZA = 2;
const int Auto::TIEMPO_LLEGAR_SALIDA = 2;

Auto::Auto(Estacionamiento* estacionamiento) {
	this->estacionamiento = estacionamiento;
	this->id = NumberUtil::getRandom(RAND_MAX);
	this->tiempo = NumberUtil::getRandom(ParserParametros::TIEMPO_ESTADIA_MIN_DEFAULT, ParserParametros::TIEMPO_ESTADIA_MAX_DEFAULT);
	this->numeroPlaza = -1;
}

Auto::~Auto() {

}

bool Auto::solicitarLugar() {
	return this->estacionamiento->solicitarLugar();
}

int Auto::tomarEntrada() {
	return this->estacionamiento->solicitarEntrada();
}

int Auto::liberarEntrada() {
	return this->estacionamiento->liberarEntrada();
}

int Auto::tomarSalida() {
	return this->estacionamiento->solicitarSalida();
}

int Auto::liberarSalida() {
	return this->estacionamiento->liberarSalida();
}

bool Auto::ocuparPlaza() {
	return this->estacionamiento->ocuparPlaza(this);
}

long Auto::desocuparPlaza() {
	return this->estacionamiento->desocuparLugar(this->numeroPlaza);
}

void Auto::setNumeroPlaza(int numeroPlaza) {
	this->numeroPlaza = numeroPlaza;
}

int Auto::getNumeroPlaza() {
	return this->numeroPlaza;
}

void Auto::setId(long id) {
	this->id = id;
}

long Auto::getId() {
	return this->id;
}

int Auto::getTiempo() {
	return this->tiempo;
}
