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

		info << "Auto: [" << this->autoDelProceso->getId() << "]: Entra al estacionamiento.";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		this->autoDelProceso->tomarEntrada();
		sleep(2); //TODO sacar numero magico
		this->autoDelProceso->liberarEntrada();


		info << "Auto: [" << this->autoDelProceso->getId() << "]: Ya entro, ocupa la plaza y a dormir.";
		Log::getLog()->logMensaje(info.str());
		info.str("");
		this->autoDelProceso->ocuparPlaza();
		sleep(3);

		info << "Auto: [" << this->autoDelProceso->getId() << "]: Busca la salida.";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		this->autoDelProceso->tomarSalida();
		sleep(2); //TODO sacar numero magico
		this->autoDelProceso->liberarSalida();

		info << "Auto: [" << this->autoDelProceso->getId() << "]: salio del estacionamiento.";
		Log::getLog()->logMensaje(info.str());
		info.str("");

	} else {
		info << "Auto: [" << this->autoDelProceso->getId() << "]: el auto se retira porque el estacionamiento esta lleno";
		Log::getLog()->logMensaje(info.str());
	}
}
