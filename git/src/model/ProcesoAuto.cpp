#include "ProcesoAuto.h"
#include "AdministracionCliente.h"

ProcesoAuto::ProcesoAuto(AdministracionCliente* administracionCliente,
		int estacionamiento) {
	this->autoDelProceso = new Auto(administracionCliente, estacionamiento);
	this->administracionCliente = administracionCliente;
}

ProcesoAuto::~ProcesoAuto() {

}

void ProcesoAuto::ejecutar() {
	stringstream info;
	info << "Auto: [" << this->autoDelProceso->getId() << "]: solicita lugar";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	if (this->autoDelProceso->solicitarLugar()) {

		info << "Auto: [" << this->autoDelProceso->getId()
				<< "]: Entra al estacionamiento.";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		this->autoDelProceso->tomarEntrada();
		this->autoDelProceso->entrar();
		this->autoDelProceso->liberarEntrada();

		info << "Auto: [" << this->autoDelProceso->getId()
				<< "]: Ya entro, ocupa la plaza y a dormir.";
		Log::getLog()->logMensaje(info.str());
		info.str("");
		this->autoDelProceso->ocuparPlaza();
		this->autoDelProceso->aparcar();

		info << "Auto: [" << this->autoDelProceso->getId()
				<< "]: Busca la salida.";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		this->autoDelProceso->desocuparPlaza();

		info << "Auto: [" << this->autoDelProceso->getId()
				<< "]: desocupo su lugar.";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		this->autoDelProceso->tomarSalida();
		this->autoDelProceso->salir();
		this->autoDelProceso->liberarSalida();

		info << "Auto: [" << this->autoDelProceso->getId()
				<< "]: salio del estacionamiento.";
		Log::getLog()->logMensaje(info.str());
		info.str("");

	} else {
		info << "Auto: [" << this->autoDelProceso->getId()
				<< "]: el auto se retira porque el estacionamiento esta lleno";
		Log::getLog()->logMensaje(info.str());
	}
}
