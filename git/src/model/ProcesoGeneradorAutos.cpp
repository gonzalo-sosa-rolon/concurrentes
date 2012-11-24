#include "ProcesoGeneradorAutos.h"

const int ProcesoGeneradorAutos::TIEMPO_ENTRE_AUTOS = 3;

ProcesoGeneradorAutos::ProcesoGeneradorAutos() {

}

ProcesoGeneradorAutos::~ProcesoGeneradorAutos() {

}

void ProcesoGeneradorAutos::ejecutar() {

	while (!this->terminarProceso()) {
		//sleep(NumberUtil::getRandom(ParserParametros::ENTRADA_SLEEP_MIN_DEFAULT, ParserParametros::ENTRADA_SLEEP_MAX_DEFAULT));
	}
}

