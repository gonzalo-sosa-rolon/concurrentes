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
	while ((!this->sigint_handler.getGracefulQuit()) || (!this->estacionamiento->estaVacio())) {
		std::cout << "Salida " << numeroDeSalida << ": Ejecutando proceso" << std::endl;
		liberarPlaza();
		sleep(1);
	}
	std::cout << "Salida " << numeroDeSalida << ": Se termino mi proceso, una lastima. Pid [" << getpid() << "]" << std::endl;
}

void ProcesoSalida::liberarPlaza() {
	bool liberoAlgo = false;

	Plaza plaza;
	for (int i = 0; i < this->estacionamiento->getTamanio(); i++) {

		Lock* lockPlaza = this->estacionamiento->getLockPlaza(i);
		lockPlaza->tomarLock();

		if (this->estacionamiento->getPlaza(i).deseaIrse()) {
			long idDelAutoDesocupado = this->estacionamiento->desocuparLugar(i);
			std::cout << "Salida " << numeroDeSalida << ": Yay! libere la plaza [" << i << "] ; id del auto que se fue [" << idDelAutoDesocupado << "]" << std::endl;
			std::cout << "Salida " << numeroDeSalida << ": Quedan " << this->estacionamiento->getCantidadDeAutos() << " autos en el estacionamiento" << endl;
			liberoAlgo = true;
			break;
		}
		lockPlaza->liberarLock();
	}

	if (!liberoAlgo) {
		std::cout << "Salida " << numeroDeSalida << ": No libere nada y quedan " << this->estacionamiento->getCantidadDeAutos() << " autos en el estacionamiento" << endl;
		std::cout << "Salida " << numeroDeSalida << ": El estacionamiento esta vacio? " << this->estacionamiento->estaVacio() << endl;
	}
}
