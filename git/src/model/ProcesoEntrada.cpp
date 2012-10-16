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

				stringstream info;
				info << "Entrada " << numeroDeEntrada << ": Acabo de ocupar una plaza, hay " << this->estacionamiento->getCantidadDeAutos() << " Autos en el estacionamiento";
				Log::getLog()->logMensaje(info.str());

			} else {
				stringstream error;
				error << "Entrada " << this->numeroDeEntrada << "algo anda mal, el estacionamiento no esta lleno pero no pude ingresar ";
				Log::getLog()->logError(error.str());
			}

		} else {
			stringstream info;
			info << "Entrada " << this->numeroDeEntrada << ": Se lleno el estacionamiento";
			Log::getLog()->logMensaje(info.str());
		}

		sleep(NumberUtil::getRandom(1, 3));
	}

	stringstream info;
	info << "Entrada " << this->numeroDeEntrada << ": Fin del proceso. Pid [" << getpid() << "]";
	Log::getLog()->logMensaje(info.str());
}

bool ProcesoEntrada::ocuparPlaza() {

	bool resultado = false;

	int tiempo = NumberUtil::getRandom(1, 3);

	for (int i = 0; i < this->estacionamiento->getTamanio(); i++) {
		Lock* lockPlaza = this->estacionamiento->getLockPlaza(i);

		int error = lockPlaza->tomarLock();

		if (error) {
			cerr << "Error: se produjo un error al intentar tomar el lock de la plaza " << i +1 << endl;
			exit(-1);
		}

		if (!this->estacionamiento->getPlaza(i).getOcupado()) {
			long id = NumberUtil::getRandom(RAND_MAX);
			this->estacionamiento->ocuparPlaza(i, tiempo, id);

			stringstream info;
			info << "Entrada " << numeroDeEntrada << ": Yay! ocupe la plaza [" << i << "] id del auto [" << id << "]";
			Log::getLog()->logMensaje(info.str());
			resultado = true;
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

	return resultado;
}

