#include "Auto.h"
#include "../util/NumberUtil.h"
#include "../util/ParserParametros.h"
#include "AdministracionCliente.h"


const int Auto::TIEMPO_ENTRAR = 2;
const int Auto::TIEMPO_SALIR = 3;
const int Auto::TIEMPO_LLEGAR_PLAZA = 2;
const int Auto::TIEMPO_LLEGAR_SALIDA = 2;
const int Auto::TIEMPO_APARCAR = 15;

Auto::Auto(AdministracionCliente* administracionCliente, int estacionamiento) {
	this->estacionamiento = estacionamiento;
	this->id = NumberUtil::getRandom(RAND_MAX);
	this->tiempo = NumberUtil::getRandom(ParserParametros::TIEMPO_ESTADIA_MIN_DEFAULT, ParserParametros::TIEMPO_ESTADIA_MAX_DEFAULT);
	this->numeroPlaza = -1;
	this->administracionCliente = administracionCliente;
}

Auto::~Auto() {

}

bool Auto::solicitarLugar() {
	return this->administracionCliente->solicitarLugar(this);
}

int Auto::tomarEntrada() {
	return this->administracionCliente->solicitarEntrada(this);
}

int Auto::liberarEntrada() {
	return this->administracionCliente->liberarEntrada(this);
}

int Auto::tomarSalida() {
	return this->administracionCliente->solicitarSalida(this);
}

int Auto::liberarSalida() {
	return this->administracionCliente->liberarSalida(this);
}

bool Auto::ocuparPlaza() {
	return this->administracionCliente->ocuparPlaza(this);
}

long Auto::desocuparPlaza() {
	return this->administracionCliente->descocuparLugar(this);
}

int Auto::getEstacionamiento() {
	return this->estacionamiento;
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

void Auto::entrar() {
	sleep(NumberUtil::getRandom(TIEMPO_ENTRAR));
}

void Auto::salir() {
	sleep(NumberUtil::getRandom(TIEMPO_SALIR));
}

void Auto::aparcar() {
	sleep(this->tiempo);
}
