#include "ProcesoGeneradorAutos.h"
#include "../util/NumberUtil.h"
#include "ProcesoAuto.h"
#include <unistd.h>
#include <vector>
#include "../util/Log.h"
#include <sstream>

const int ProcesoGeneradorAutos::TIEMPO_ENTRE_AUTOS = 5;

ProcesoGeneradorAutos::ProcesoGeneradorAutos(Estacionamiento *estacionamiento) {
	this->estacionamiento = estacionamiento;
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
			ProcesoAuto procesoAuto(estacionamiento);
			procesoAuto.ejecutar();
		} else {
			info << "Proceso Generador Autos: se genero un auto con p_id ["
					<< id << "]";
			Log::getLog()->logMensaje(info.str());
			info.str("");
			idsProcesosAutos.push_back(id);
		}

		// Los autos llegan cada tiempo random
		sleep(
				NumberUtil::getRandom(0,
						ProcesoGeneradorAutos::TIEMPO_ENTRE_AUTOS));
	}

	info << "Proceso Generador Autos: fin de generacion de autos";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	if (id) {
		for (int i = 0; i < idsProcesosAutos.size(); i++) {
			//TODO waitpid
		}
	}

	info << "Proceso Generador Autos: fin del proceso";
	Log::getLog()->logMensaje(info.str());
	info.str("");
}

