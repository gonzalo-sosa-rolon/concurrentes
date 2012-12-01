#include "ProcesoGeneradorAutos.h"
#include "AdministracionCliente.h"
const int ProcesoGeneradorAutos::TIEMPO_ENTRE_AUTOS = 5;

ProcesoGeneradorAutos::ProcesoGeneradorAutos(Estacionamiento *estacionamiento, AdministracionCliente* administracionCliente) {
	this->estacionamiento = estacionamiento;
	this->administracionCliente = administracionCliente;
}

ProcesoGeneradorAutos::~ProcesoGeneradorAutos() {

}

void ProcesoGeneradorAutos::ejecutar() {

	std::vector<pid_t> idsProcesosAutos;
	pid_t id;
	stringstream info;
	info << "Proceso Generador Autos: inicio de ejecucion";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	while (!this->terminarProceso()) {
		id = fork();

		if (!id) {
			ProcesoAuto procesoAuto(administracionCliente, 0); //TODO setear el nombre del estacionamiento
			procesoAuto.ejecutar();
			return;
		} else {
			info << "Proceso Generador Autos: se genero un auto con p_id ["
					<< id << "]";
			Log::getLog()->logMensaje(info.str());
			info.str("");
			idsProcesosAutos.push_back(id);
			// Los autos llegan cada tiempo random
//			sleep(
//					NumberUtil::getRandom(2,
//							ProcesoGeneradorAutos::TIEMPO_ENTRE_AUTOS));
			sleep(1); //TODO
		}

	}

	info << "Proceso Generador Autos: fin de generacion de autos";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	for (unsigned int i = 0; i < idsProcesosAutos.size(); i++) {
		waitpid(idsProcesosAutos[i], NULL, 0);
	}

	info << "Proceso Generador Autos: fin del proceso";
	Log::getLog()->logMensaje(info.str());
	info.str("");
}

