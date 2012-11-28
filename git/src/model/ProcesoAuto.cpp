#include "ProcesoAuto.h"

ProcesoAuto::ProcesoAuto(Estacionamiento *estacionamiento) {
	this->autoDelProceso = new Auto(estacionamiento);
	this->estacionamiento = estacionamiento;
}

ProcesoAuto::~ProcesoAuto() {

}

void ProcesoAuto::ejecutar() {

	stringstream info;
	info << "Auto: [" << this->autoDelProceso->getId() << "]: solicita lugar" ;
	Log::getLog()->logMensaje(info.str());
	info.str("");

	if (this->autoDelProceso->solicitarLugar()) {
		if (this->autoDelProceso->ocuparPlaza()) {

			info << "Auto: [" << this->autoDelProceso->getId() << "]: Entra al estacionamiento.";
			Log::getLog()->logMensaje(info.str());
			info.str("");

			this->autoDelProceso->entrar();

			info << "Auto: [" << this->autoDelProceso->getId() << "]: Se dirige a la plaza \"." << this->autoDelProceso->getNumeroPlaza() << "\"";
			Log::getLog()->logMensaje(info.str());
			info.str("");

			this->autoDelProceso->dirigirseAPlaza();

			info << "Auto: [" << this->autoDelProceso->getId() << "]: va a aparcar.";
			Log::getLog()->logMensaje(info.str());
			info.str("");

			this->autoDelProceso->aparcar();

			info << "Auto: [" << this->autoDelProceso->getId() << "]: Se dirige a la salida.";
			Log::getLog()->logMensaje(info.str());
			info.str("");

			this->autoDelProceso->dirigirseASalida();

			this->autoDelProceso->salir();
			info << "Auto: [" << this->autoDelProceso->getId() << "]: salio del estacionamiento.";
			Log::getLog()->logMensaje(info.str());
			info.str("");

		}
	} else {
		info << "Auto: [" << this->autoDelProceso->getId() << "]: el auto se retira porque el estacionamiento esta lleno";
		Log::getLog()->logMensaje(info.str());
	}
}
