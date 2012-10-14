#include "ProcesoEntrada.h"

ProcesoEntrada::ProcesoEntrada(int numeroDeEntrada, Estacionamiento* estacionamiento) {
	this->numeroDeEntrada = numeroDeEntrada;
	this->estacionamiento = estacionamiento;

	// se registra el event handler declarado antes
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	srand(time(NULL));
}

ProcesoEntrada::~ProcesoEntrada() {

}

void ProcesoEntrada::ejecutar() {

	while (!this->sigint_handler.getGracefulQuit()) {
		int tiempo = NumberUtil::getRandom(1, 3);
		cout << "ejecutando entrada " << this->numeroDeEntrada << "; Ocupando lugar por " << tiempo << " horas"<< endl;
		this->estacionamiento->tomarLockPlazas();
		if (!this->estacionamiento->ocuparPlaza(tiempo)) {
			if (this->estacionamiento->estaLLeno()) {
				cout << "Se lleno el estacionamiento" << endl;
			} else {
				cout << "TERROR: algo anda mal, no pude ingresar el auto y el estacionamiento no esta lleno" << endl;
			}

		}
		this->estacionamiento->liberarLockPlazas();
		sleep(NumberUtil::getRandom(1, 3));
	}

	std::cout << "Entrada: Se termino mi proceso, una lastima. Pid [" << getpid() << "]" << std::endl;
}
