/*
 * ProcesoSalida.cpp
 *
 *  Created on: 04/12/2012
 *      Author: maxi
 */

#include "ProcesoSalida.h"

ProcesoSalida::ProcesoSalida(int cantidadEntradas, char* path, char key,
		AdministracionCliente* administracionCliente, int nroEstacionamiento)
		:ProcesoPuerta(cantidadEntradas, path, key, nroEstacionamiento) {

	this->adminCliente = administracionCliente;
}

ProcesoSalida::~ProcesoSalida() {
	// TODO Auto-generated destructor stub
}

int ProcesoSalida::getCantidadAutos() {
	return this->adminCliente->consultarCantidadAutos(this->nroEstacionamiento);
}

void ProcesoSalida::terminarEjecucion() {

	std::stringstream info;
	info << getNombre() << ": Ejecutando metodo terminarEjecucion";
	Log::getLog()->logMensaje(info.str());
	info.str("");


	while (getCantidadAutos() > 0) {
		info << getNombre() << ": El estacionamiento tiene [" << getCantidadAutos() << "] autos";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		procesarIngresoOEgreso();
	}

	while (cantidadEntradasOcupadas > 0) {

		info << getNombre() << ": El estacionamiento esta vacío, entradas ocupadas = " << cantidadEntradasOcupadas;
		Log::getLog()->logMensaje(info.str());
		info.str("");

		procesarEgreso();
	}

	info << getNombre() << ": Terminando Ejecucion";
	Log::getLog()->logMensaje(info.str());
	info.str("");

}

std::string ProcesoSalida::getNombre() {
	std::stringstream nombre;
	nombre << "Salida " << this->nroEstacionamiento;
	return nombre.str();
}

