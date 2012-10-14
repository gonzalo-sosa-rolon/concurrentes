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

		if (!this->estacionamiento->estaLLeno()) {

			if (ocuparPlaza()) {
				std::cout << "Entrada " << numeroDeEntrada << ": Acabo de ocupar una plaza, hay " << this->estacionamiento->getCantidadDeAutos() << " Autos en el estacionamiento" << std::endl;
			} else {
				cout << "Entrada " << this->numeroDeEntrada << ": ERROR, algo anda mal, el estacionamiento no esta lleno pero no pude ingresar " << endl;
			}

		} else {
			cout << "Entrada " << this->numeroDeEntrada << ": Se lleno el estacionamiento" << endl;
		}

		sleep(NumberUtil::getRandom(1, 3));
	}

	std::cout << "Entrada " << this->numeroDeEntrada << ": Se termino mi proceso, una lastima. Pid [" << getpid() << "]" << std::endl;
}

bool ProcesoEntrada::ocuparPlaza() {

	bool resultado = false;

	int tiempo = NumberUtil::getRandom(1, 3);

	for (int i = 0; i < this->estacionamiento->getTamanio(); i++) {
		Lock* lockPlaza = this->estacionamiento->getLockPlaza(i);

		lockPlaza->tomarLock();
		if (!this->estacionamiento->getPlaza(i).getOcupado()) {
			long id = NumberUtil::getRandom(RAND_MAX);
			this->estacionamiento->ocuparPlaza(i, tiempo, id);
			std::cout << "Entrada " << numeroDeEntrada << ": Yay! ocupe la plaza [" << i << "] id del auto [" << id << "]" << std::endl;
			resultado = true;
			break;
		}
		lockPlaza->liberarLock();
	}

	return resultado;
}

