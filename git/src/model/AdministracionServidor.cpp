#include "AdministracionServidor.h"
#include "Estacionamiento.h"
#include "../util/Log.h"
#include <iostream>

AdministracionServidor::AdministracionServidor(int cantidadEstacionamientos,
		int tamanio, int precio) :
		colaDeMensajes((char*) Mensaje::PATH_TOKEN_COLA_SERVIDOR, 3) {
	this->cantidadEstacionamientos = cantidadEstacionamientos;
	this->tamanio = tamanio;
	this->precio = precio;
	this->crearEstacionamientos();
}

AdministracionServidor::~AdministracionServidor() {

}

void AdministracionServidor::crearEstacionamientos() {

	stringstream info;
	info << "Proceso administracion servidor: se van a crear " << this->tamanio
			<< " estacionamientos.";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	for (int i = 0; i < cantidadEstacionamientos; i++) {
		/*Estacionamiento* estacionamiento = new Estacionamiento(this->tamanio,
				this->precio);
		this->estacionamientos.push_back(estacionamiento);*/
	}

	info << "Proceso administracion servidor: estacionamientos creados ";
	Log::getLog()->logMensaje(info.str());
	info.str("");
}

void AdministracionServidor::procesarMensaje(Mensaje::Mensaje &mensaje) {

	switch (mensaje.tipo) {
	case Mensaje::TIPO_SOLICITAR_LUGAR:
		procesarSolicitarLugar(mensaje);
			break;
	case Mensaje::TIPO_LIBERAR_PLAZA:
		procesarLiberarPlaza(mensaje);
		break;
	case Mensaje::TIPO_OCUPAR_PLAZA:
		procesarOcuparPlaza(mensaje);
		break;
	case Mensaje::TIPO_SALIR:
		procesarSalir(mensaje);
		break;
	}
}

void AdministracionServidor::procesarLiberarPlaza(Mensaje::Mensaje mensaje) {

}

void AdministracionServidor::procesarSolicitarLugar(Mensaje::Mensaje mensaje) {

}

void AdministracionServidor::procesarOcuparPlaza(Mensaje::Mensaje mensaje) {

}

void AdministracionServidor::procesarSalir(Mensaje::Mensaje mensaje) {

}

bool AdministracionServidor::estacionamientosVacios() {

	bool resultado = true;

	for (int i = 0; i < cantidadEstacionamientos; i++) {
		resultado = resultado && this->estacionamientos[i]->estaVacio();
	}

	return resultado;
}

void AdministracionServidor::ejecutar() {

	stringstream info;

	while (!this->terminarProceso() || !this->estacionamientosVacios()) {
		Log::getLog()->logMensaje(info.str());

		Mensaje::Mensaje mensaje;
		int resultado = colaDeMensajes.leer(Mensaje::MENSAJE_SERVIDOR,
				&mensaje);
		//TODO ver que hacer con el resultado
		this->procesarMensaje(mensaje);
	}
}

