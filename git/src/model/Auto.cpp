#include "Auto.h"
#include "../util/NumberUtil.h"
#include "../util/ParserParametros.h"

Auto::Auto(Estacionamiento* estacionamiento) {
	this->estacionamiento = estacionamiento;
	this->id = NumberUtil::getRandom(RAND_MAX);
	this->tiempo = NumberUtil::getRandom(ParserParametros::TIEMPO_ESTADIA_MIN_DEFAULT, ParserParametros::TIEMPO_ESTADIA_MAX_DEFAULT);
}

Auto::~Auto() {

}

bool Auto::solicitarLugar() {
	return this->estacionamiento->solicitarLugar();
}

void Auto::aparcar() {

}

void Auto::entrar() {

}

bool Auto::solicitarPlaza() {
	return false;
}

void Auto::dirigirseAPlaza() {

}

void Auto::dirigirseASalida() {

}

void Auto::salir() {

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
