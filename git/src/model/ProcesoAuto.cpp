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
	int resultado = 0;

	resultado = this->autoDelProceso->solicitarLugar();

	if (resultado) {

		info << "Auto: [" << this->autoDelProceso->getId()
				<< "]: Entra al estacionamiento.";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		this->autoDelProceso->tomarEntrada();
		this->autoDelProceso->entrar();
		this->autoDelProceso->liberarEntrada();

		info << "Auto: [" << this->autoDelProceso->getId() << "]: Ya entré, ocupo la plaza y a dormir.";
		Log::getLog()->logMensaje(info.str());
		info.str("");
		bool resultado = this->autoDelProceso->ocuparPlaza();

		if (resultado == false) {
			info << "Auto: Errir al ocupar lugar, terminando ejecución";
			Log::getLog()->logMensaje(info.str());
			info.str("");
			exit(1);
		}

		this->autoDelProceso->aparcar();

		info << "Auto: [" << this->autoDelProceso->getId()
				<< "]: Busca la salida.";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		this->autoDelProceso->desocuparPlaza();

		info << "Auto: [" << this->autoDelProceso->getId() << "]: desocupo su lugar.";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		this->autoDelProceso->tomarSalida();
		this->autoDelProceso->salir();
		this->autoDelProceso->liberarSalida();

		info << "Auto: [" << this->autoDelProceso->getId() << "]: salio del estacionamiento.";
		Log::getLog()->logMensaje(info.str());
		info.str("");

	} else {
		info << "Auto: [" << this->autoDelProceso->getId() << "]: el auto se retira porque el estacionamiento esta lleno";
		Log::getLog()->logMensaje(info.str());
	}
}
