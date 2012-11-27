#include "ProcesoGeneradorAutos.h"
#include "../util/NumberUtil.h"
#include "ProcesoAuto.h"
#include <unistd.h>

const int ProcesoGeneradorAutos::TIEMPO_ENTRE_AUTOS = 5;

ProcesoGeneradorAutos::ProcesoGeneradorAutos(Estacionamiento *estacionamiento) {
	this->estacionamiento = estacionamiento;
}

ProcesoGeneradorAutos::~ProcesoGeneradorAutos() {

}

void ProcesoGeneradorAutos::ejecutar() {

	while (!this->terminarProceso()) {
		pid_t id = fork();

		if (!id) {
			ProcesoAuto procesoAuto(estacionamiento);
			procesoAuto.ejecutar();
		}

		// Los autos llegan cada tiempo random
		sleep(NumberUtil::getRandom(0, ProcesoGeneradorAutos::TIEMPO_ENTRE_AUTOS));
	}
}

