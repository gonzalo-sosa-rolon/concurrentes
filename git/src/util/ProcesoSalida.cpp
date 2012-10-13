#include "ProcesoSalida.h"

ProcesoSalida::ProcesoSalida(int numeroDeSalida) {
	this->numeroDeSalida  = numeroDeSalida;
}

ProcesoSalida::~ProcesoSalida() {

}

void ProcesoSalida::ejecutar() {
	while (true) {
		//cout << "ejecutando salida " << this->numeroDeSalida << endl;
		sleep(1);
	}
}
