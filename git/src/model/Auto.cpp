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

void Auto::aparcar() {
	sleep(this->tiempo);
}

void Auto::entrar() {
	this->estacionamiento->solicitarEntrada();
	sleep(NumberUtil::getRandom(0, TIEMPO_ENTRAR));
	this->estacionamiento->liberarEntrada();
}

bool Auto::ocuparPlaza() {
	return this->estacionamiento->ocuparPlaza(this);
}

void Auto::dirigirseAPlaza() {
	sleep(NumberUtil::getRandom(0, TIEMPO_LLEGAR_PLAZA));
}

void Auto::dirigirseASalida() {
	sleep(NumberUtil::getRandom(0, TIEMPO_LLEGAR_SALIDA));
}

void Auto::salir() {
	this->estacionamiento->desocuparLugar(this->numeroPlaza);
	this->estacionamiento->solicitarSalida();
	sleep(NumberUtil::getRandom(0, TIEMPO_SALIR));
	this->estacionamiento->liberarSalida();
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
