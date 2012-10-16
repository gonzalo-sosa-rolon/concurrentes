#include "ProcesoSalida.h"
#include <stdlib.h>


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
		liberarPlaza();
		sleep(1);
	}

	stringstream info;
	info << "Salida " <<  numeroDeSalida << ": Se termino mi proceso, una lastima. Pid [" << getpid() << "]";

	Log::getLog()->logMensaje(info.str());
}

void ProcesoSalida::liberarPlaza() {
	bool liberoAlgo = false;

	Plaza plaza;

	stringstream info;
	info << "Salida " << this->numeroDeSalida << ": intentara liberar una plaza";
	Log::getLog()->logMensaje(info.str());

	for (int i = 0; i < this->estacionamiento->getTamanio(); i++) {

		Lock* lockPlaza = this->estacionamiento->getLockPlaza(i);
		int error = lockPlaza->tomarLock();

		if (error) {
			cerr << "Error: se produjo un error al intentar tomar el lock de la plaza " << i +1 << endl;
			exit(-1);
		}

		if (this->estacionamiento->getPlaza(i).deseaIrse()) {
			long idDelAutoDesocupado = this->estacionamiento->desocuparLugar(i);

			stringstream info;
			info << "Salida " << this->numeroDeSalida << ": Yay! libere la plaza [" << i << "] ; id del auto que se fue [" << idDelAutoDesocupado << "]";
			Log::getLog()->logMensaje(info.str());

			info.str("");

			info << "Salida " << this->numeroDeSalida << ": Quedan " << this->estacionamiento->getCantidadDeAutos()
				 << " autos en el estacionamiento";

			Log::getLog()->logMensaje(info.str());

			liberoAlgo = true;
			error = lockPlaza->liberarLock();

			if (error) {
				cerr << "Error: se produjo un error al intentar liberar el lock de la plaza " << i +1 << endl;
				exit(-1);
			}
			break;
		}

		error = lockPlaza->liberarLock();

		if (error) {
			cerr << "Error: se produjo un error al intentar liberar el lock de la plaza " << i +1 << endl;
			exit(-1);
		}
	}

	if (!liberoAlgo) {
		stringstream info;
		info << "Salida "  << this->numeroDeSalida << ": No libere nada y quedan " << this->estacionamiento->getCantidadDeAutos() << " autos en el estacionamiento";

		Log::getLog()->logMensaje(info.str());
		info.str("");

		info << "Salida "  << this->numeroDeSalida << ": El estacionamiento esta vacio? " << this->estacionamiento->estaVacio();
		Log::getLog()->logMensaje(info.str());

	}
}
