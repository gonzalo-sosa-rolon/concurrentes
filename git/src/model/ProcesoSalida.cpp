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
	while ((!this->sigint_handler.getGracefulQuit()) || this->estacionamiento->estaVacio()) {
		std::cout << "Salida " << numeroDeSalida << ": Ejecutando proceso" << std::endl;
		liberarPlaza();
		sleep(1);
	}
	std::cout << "Salida " << numeroDeSalida << ": Se termino mi proceso, una lastima. Pid [" << getpid() << "]" << std::endl;
}

void ProcesoSalida::liberarPlaza() {
	this->estacionamiento->tomarLockPlazas();
	Plaza plaza;
	for (int i = 0; i < this->estacionamiento->getTamanio(); i++) {
		plaza = this->estacionamiento->getPlaza(i);
		if (plaza.deseaIrse()) {
			this->estacionamiento->desocuparLugar(i);
			std::cout << "Salida " << numeroDeSalida << ": Yay! libere la plaza [" << i << "]" << std::endl;
			break;
		} else {
			std::cout << "Salida " << numeroDeSalida << ": Plaza [" << i << "] no se quiere ir" << std::endl;
		}
	}
	this->estacionamiento->liberarLockPlazas();
}
