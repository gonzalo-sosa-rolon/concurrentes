#include "ProcesoEntrada.h"

ProcesoEntrada::ProcesoEntrada(int numeroDeEntrada, Estacionamiento* estacionamiento) {
	this->numeroDeEntrada = numeroDeEntrada;
	this->estacionamiento = estacionamiento;

	// se registra el event handler declarado antes
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);
}

ProcesoEntrada::~ProcesoEntrada() {

}

void ProcesoEntrada::ejecutar() {

	while (!this->sigint_handler.getGracefulQuit()) {
		//cout << "ejecutando entrada " << this->numeroDeEntrada << endl;
		sleep(1);
	}
	std::cout << "Entrada: Se termino mi proceso, una lastima. Pid [" << getpid() << "]" << std::endl;
}
