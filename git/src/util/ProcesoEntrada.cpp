#include "ProcesoEntrada.h"

ProcesoEntrada::ProcesoEntrada(int numeroDeEntrada) {
	this->numeroDeEntrada = numeroDeEntrada;
}

ProcesoEntrada::~ProcesoEntrada() {

}

void ProcesoEntrada::ejecutar() {

	while (true) {
		cout << "ejecutando entrada " << this->numeroDeEntrada << endl;
		sleep(1);
	}
}
