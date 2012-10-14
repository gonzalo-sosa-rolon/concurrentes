#include "ProcesoSalida.h"


ProcesoSalida::ProcesoSalida(int numeroDeSalida, Estacionamiento* estacionamiento) {
	this->numeroDeSalida  = numeroDeSalida;
	this->estacionamiento = estacionamiento;

	// se registra el event handler declarado antes
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);
}

ProcesoSalida::~ProcesoSalida() {

}

void ProcesoSalida::ejecutar() {
	while (!this->sigint_handler.getGracefulQuit()) {
		//cout << "ejecutando salida " << this->numeroDeSalida << endl;
		sleep(1);
	}
	std::cout << "Salida: Se termino mi proceso, una lastima. Pid [" << getpid() << "]" << std::endl;
}
