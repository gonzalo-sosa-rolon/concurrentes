#include "AdministracionServidor.h"
#include "Estacionamiento.h"
#include "../util/Log.h"
#include <iostream>

AdministracionServidor::AdministracionServidor(int cantidadEstacionamientos,
		int tamanio, int precio) :
		colaDeMensajes((char*) Mensaje::PATH_TOKEN_COLA_SERVIDOR, 50) {
	this->cantidadEstacionamientos = cantidadEstacionamientos;
	this->tamanio = tamanio;
	this->precio = precio;
	this->crearEstacionamientos();
}

AdministracionServidor::~AdministracionServidor() {

	for (int i = 0; i < cantidadEstacionamientos; i++) {
		delete this->estacionamientos[i];
	}

	colaDeMensajes.destruir();
}

void AdministracionServidor::crearEstacionamientos() {

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
//	case Mensaje::TIPO_SALIR:
//		procesarSalir(mensaje);
//		break;
	case Mensaje::TIPO_CANTIDAD_AUTOS:
		consultaCantidadDeAutos(mensaje);
		break;
	case Mensaje::TIPO_MONTO_FACTURADO:
		consultaMontoFacturado(mensaje);
		break;
	}
}

void AdministracionServidor::procesarLiberarPlaza(Mensaje::Mensaje mensaje) {
	int resultado =	this->estacionamientos[mensaje.estacionamiento]->desocuparLugar(mensaje.plaza);

	stringstream info;
	info << "Proceso administracion servidor: se proceso el pedido de liberar la plaza ["
			<< mensaje.plaza << "]";
	Log::getLog()->logMensaje(info.str());
}

void AdministracionServidor::procesarSolicitarLugar(Mensaje::Mensaje mensaje) {
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

void AdministracionServidor::procesarEstacionamientosVacios(	Mensaje::Mensaje mensaje) {
	bool resultado = this->estacionamientosVacios();
	Mensaje::Mensaje respuesta;

	respuesta.resultado = resultado;
	respuesta.mtype = mensaje.pid;

	colaDeMensajes.escribir(respuesta);
}

void AdministracionServidor::procesarOcuparPlaza(Mensaje::Mensaje mensaje) {

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

void AdministracionServidor::procesarSalir(Mensaje::Mensaje mensaje) {

}

bool AdministracionServidor::estacionamientosVacios() {

	bool resultado = true;

	for (int i = 0; i < cantidadEstacionamientos; i++) {
		resultado = resultado && this->estacionamientos[i]->estaVacio();
	}

	return resultado;
}

void AdministracionServidor::consultaCantidadDeAutos(Mensaje::Mensaje mensaje) {

	int resultado =
			this->estacionamientos[mensaje.estacionamiento]->getCantidadDeAutos();

	Mensaje::Mensaje respuesta;

	respuesta.resultado = resultado;
	respuesta.mtype = mensaje.pid;

	colaDeMensajes.escribir(respuesta);

	stringstream info;
	info << "Proceso administracion servidor: se proceso la consulta cantidad de autos para el proceso [" << respuesta.mtype << "]";
	Log::getLog()->logMensaje(info.str());

}

void AdministracionServidor::consultaMontoFacturado(Mensaje::Mensaje mensaje) {
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

void AdministracionServidor::ejecutar() {

	stringstream info;
	cout << "Pid AdministracionServidor=" << getpid() << endl;

	while (!this->terminarProceso() || !this->estacionamientosVacios()) {

		Mensaje::Mensaje mensaje;
		int resultado = colaDeMensajes.leer(Mensaje::MENSAJE_SERVIDOR,
				&mensaje);

		if ((resultado == -1) && (!this->terminarProceso())) {
			info << "********************** ADM GENERAL - ERROR: " << strerror(errno);
			Log::getLog()->logMensaje(info.str());
			info.str("");
		}
		//TODO ver que hacer con el resultado
		this->procesarMensaje(mensaje);
	}

	info << "Proceso administracion servidor: Finalizando ejecución";
	Log::getLog()->logMensaje(info.str());
	info.str("");
}

