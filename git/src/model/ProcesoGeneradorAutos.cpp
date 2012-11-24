#include "ProcesoGeneradorAutos.h"
#include "../util/NumberUtil.h"
const int ProcesoGeneradorAutos::TIEMPO_ENTRE_AUTOS = 3;

ProcesoGeneradorAutos::ProcesoGeneradorAutos() {

}

ProcesoGeneradorAutos::~ProcesoGeneradorAutos() {

}

void ProcesoGeneradorAutos::ejecutar() {

	while (!this->terminarProceso()) {
		// Los autos llegan cada tiempo random
		sleep(NumberUtil::getRandom(0, ProcesoGeneradorAutos::TIEMPO_ENTRE_AUTOS));
	}
}

