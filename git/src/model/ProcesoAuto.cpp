/*
 * ProcesoAuto.cpp
 *
 *  Created on: Nov 24, 2012
 *      Author: gsosarolon
 */

#include "ProcesoAuto.h"

ProcesoAuto::ProcesoAuto(Estacionamiento *estacionamiento) {
	this->autoDelProceso = new Auto(estacionamiento);
	this->estacionamiento = estacionamiento;
}

ProcesoAuto::~ProcesoAuto() {

}

void ProcesoAuto::ejecutar() {

	stringstream info;
	info << "Proceso auto: auto solicita lugar" ;
	Log::getLog()->logMensaje(info.str());
	info.str("");

	if (this->autoDelProceso->solicitarLugar()) {
		if (this->autoDelProceso->ocuparPlaza()) {

			//Auto toma plaza y entra info << "Proceso auto: el auto se retira porque el estacionamiento esta lleno";
			Log::getLog()->logMensaje(info.str());
			this->autoDelProceso->entrar();
			this->autoDelProceso->dirigirseAPlaza();

			this->autoDelProceso->aparcar();
			this->autoDelProceso->dirigirseASalida();
			this->autoDelProceso->salir();
		}
	} else {
		info << "Proceso auto: el auto se retira porque el estacionamiento esta lleno";
		Log::getLog()->logMensaje(info.str());
	}
}
