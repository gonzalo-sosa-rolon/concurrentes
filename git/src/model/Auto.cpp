#include "Auto.h"

Auto::Auto(Estacionamiento* estacionamiento) {
	this->estacionamiento = estacionamiento;
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
