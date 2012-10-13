#include "Plaza.h"

Plaza::Plaza() {
	this->id = 0;
	this->ocupado = false;
}

Plaza::Plaza(int id) {
	this->id = id;
	this->ocupado = false;
}

int Plaza::getHoraIngreso() {
	return horaIngreso;
}

int Plaza::getId() {
	return id;
}

bool Plaza::getOcupado() {
	return ocupado;
}

void Plaza::setHoraIngreso(int horaIngreso) {
	this->horaIngreso = horaIngreso;
}

void Plaza::setId(int id) {
	this->id = id;
}

void Plaza::setOcupado(bool ocupado) {
	this->ocupado = ocupado;
}

void Plaza::ocupar() {
	this->ocupado = true;
	//TODO set time
}
