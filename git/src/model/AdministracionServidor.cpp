#include "AdministracionServidor.h"
#include "Estacionamiento.h"
#include "../util/Log.h"

AdministracionServidor::AdministracionServidor(int cantidadEstacionamientos, int tamanio, int precio) : colaDeMensajes((char*)Mensaje::PATH_TOKEN_COLA_SERVIDOR, 3) {
	this->cantidadEstacionamientos = cantidadEstacionamientos;
	this->tamanio = tamanio;
	this->precio = precio;
}

AdministracionServidor::~AdministracionServidor() {

}

void AdministracionServidor::crearEstacionamientos() {

	stringstream info;
		info << "Proceso administracion servidor: se van a crear " << this->tamanio << " estacionamientos." ;
		Log::getLog()->logMensaje(info.str());
		info.str("");

	for (int i = 0; i < cantidadEstacionamientos; i++) {
		Estacionamiento* estacionamiento = new Estacionamiento(this->tamanio, this->precio);
		this->estacionamientos.push_back(estacionamiento);
	}
}

void AdministracionServidor::ejecutar() {

	/**
	 * 1 ) while true
	 * 2 ) leo mensaje
	 * 3 ) proceso mensaje
	 * 4 ) envio respuesta
	 */
}

