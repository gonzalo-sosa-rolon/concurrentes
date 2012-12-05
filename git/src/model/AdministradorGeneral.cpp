#include "AdministradorGeneral.h"
#include "Estacionamiento.h"
#include "../util/Log.h"
#include <iostream>

AdministradorGeneral::AdministradorGeneral(int cantidadEstacionamientos,
		int tamanio, int precio) :
		colaDeMensajes((char*) Mensaje::PATH_TOKEN_COLA_SERVIDOR, 50) {
	this->cantidadEstacionamientos = cantidadEstacionamientos;
	this->tamanio = tamanio;
	this->precio = precio;
	this->crearEstacionamientos();
}

AdministradorGeneral::~AdministradorGeneral() {

	for (int i = 0; i < cantidadEstacionamientos; i++) {
		delete this->estacionamientos[i];
	}

	colaDeMensajes.destruir();
}

void AdministradorGeneral::crearEstacionamientos() {

	stringstream info;
	info << "Proceso administracion servidor: se van a crear "
			<< this->cantidadEstacionamientos << " estacionamientos.";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	for (int i = 0; i < cantidadEstacionamientos; i++) {
		Estacionamiento* estacionamiento = new Estacionamiento(this->tamanio,
				this->precio);
		this->estacionamientos.push_back(estacionamiento);
	}

	info << "Proceso administracion servidor: estacionamientos creados ";
	Log::getLog()->logMensaje(info.str());
	info.str("");
}

void AdministradorGeneral::procesarMensaje(Mensaje::Mensaje &mensaje) {

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
	case Mensaje::TIPO_CANTIDAD_AUTOS:
		consultaCantidadDeAutos(mensaje);
		break;
	case Mensaje::TIPO_MONTO_FACTURADO:
		consultaMontoFacturado(mensaje);
		break;
	}
}

void AdministradorGeneral::procesarLiberarPlaza(Mensaje::Mensaje mensaje) {
	int resultado =	this->estacionamientos[mensaje.estacionamiento]->desocuparLugar(mensaje.plaza);

	stringstream info;
	info << "Proceso administracion servidor: se proceso el pedido de liberar la plaza ["
			<< mensaje.plaza << "]";
	Log::getLog()->logMensaje(info.str());
}

void AdministradorGeneral::procesarSolicitarLugar(Mensaje::Mensaje mensaje) {
	bool resultado = this->estacionamientos[mensaje.estacionamiento]->solicitarLugar();

	Mensaje::Mensaje respuesta;

	respuesta.resultado = resultado;
	respuesta.mtype = mensaje.pid;

	colaDeMensajes.escribir(respuesta);

	stringstream info;
	info << "Proceso administracion servidor: se proceso la consulta procesar lugar al proceso ["
			<< respuesta.mtype << "] con el resultado {" << resultado << "}";

	Log::getLog()->logMensaje(info.str());
}

void AdministradorGeneral::procesarEstacionamientosVacios(	Mensaje::Mensaje mensaje) {
	bool resultado = this->estacionamientosVacios();
	Mensaje::Mensaje respuesta;

	respuesta.resultado = resultado;
	respuesta.mtype = mensaje.pid;

	colaDeMensajes.escribir(respuesta);
}

void AdministradorGeneral::procesarOcuparPlaza(Mensaje::Mensaje mensaje) {

	int plaza = this->estacionamientos[mensaje.estacionamiento]->seleccionarPlaza(
					mensaje.tiempo, mensaje.automovil);

	Mensaje::Mensaje respuesta;
	stringstream info;

	if (plaza == -1) {
		respuesta.resultado = -1;
		info << "Proceso administracion servidor: Error buscando plaza, no hay ninguna disponible";
		Log::getLog()->logMensaje(info.str());
	} else {
		respuesta.resultado = 0;
		info << "Proceso administracion servidor: se proceso la consulta ocupar plaza para el proceso ["
					<< mensaje.pid << "]. Plaza ocupada [" << plaza << "]";
			Log::getLog()->logMensaje(info.str());
	}
	respuesta.plaza = plaza;
	respuesta.mtype = mensaje.pid;

	colaDeMensajes.escribir(respuesta);
}

void AdministradorGeneral::procesarSalir(Mensaje::Mensaje mensaje) {
	this->estacionamientos[mensaje.estacionamiento]->salirDelEstacionamiento();
}

bool AdministradorGeneral::estacionamientosVacios() {

	bool resultado = true;

	for (int i = 0; i < cantidadEstacionamientos; i++) {
		resultado = resultado && this->estacionamientos[i]->estaVacio();
	}

	return resultado;
}

void AdministradorGeneral::consultaCantidadDeAutos(Mensaje::Mensaje mensaje) {

	int resultado = this->estacionamientos[mensaje.estacionamiento]->getCantidadDeAutos();

	Mensaje::Mensaje respuesta;

	respuesta.resultado = resultado;
	respuesta.mtype = mensaje.pid;

	colaDeMensajes.escribir(respuesta);

	stringstream info;
	info << "Proceso administracion servidor: se proceso la consulta cantidad de autos para el proceso [" << respuesta.mtype << "]";
	Log::getLog()->logMensaje(info.str());

}

void AdministradorGeneral::consultaMontoFacturado(Mensaje::Mensaje mensaje) {
	int resultado =
			this->estacionamientos[mensaje.estacionamiento]->getCantidadFacturado();

	Mensaje::Mensaje respuesta;

	respuesta.resultado = resultado;
	respuesta.mtype = mensaje.pid;

	colaDeMensajes.escribir(respuesta);

	stringstream info;
	info << "Proceso administracion servidor: se proceso la consulta monto facturado para el proceso ["	<< respuesta.mtype << "]";
	Log::getLog()->logMensaje(info.str());
}

void AdministradorGeneral::ejecutar() {

	stringstream info;

	while (!this->terminarProceso() || !this->estacionamientosVacios()) {

		Mensaje::Mensaje mensaje;
		int resultado = colaDeMensajes.leer(Mensaje::MENSAJE_SERVIDOR, &mensaje);

		if ((resultado == -1) && (!this->terminarProceso())) {
			info << "Administrador General - ERROR: " << strerror(errno);
			Log::getLog()->logMensaje(info.str());
			info.str("");
		}

		this->procesarMensaje(mensaje);
	}

	info << "Proceso administracion servidor: Finalizando ejecución";
	Log::getLog()->logMensaje(info.str());
	info.str("");
}

