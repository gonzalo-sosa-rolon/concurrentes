#include "ProcesoSalida.h"

ProcesoSalida::ProcesoSalida(int numeroDeSalida, Estacionamiento* estacionamiento) {
	this->numeroDeSalida  = numeroDeSalida;
	this->estacionamiento = estacionamiento;
}

ProcesoSalida::~ProcesoSalida() {

}

void ProcesoSalida::ejecutar() {
	while ((!this->terminarProceso()) || (!this->estacionamiento->estaVacio())) {
		buscarYSacarAuto();
		sleep(ParserParametros::SEGUNDOS_POR_HORA_DEFAULT);
	}

	stringstream info;
	info << "Salida  " <<  numeroDeSalida << ": Fin del proceso. Pid [" << getpid() << "]";

	Log::getLog()->logMensaje(info.str());
}

void ProcesoSalida::buscarYSacarAuto() {
	bool liberoAlgo = recorrerEstacionamiento();

	if (!liberoAlgo) {
		stringstream info;
		info << "Salida  "  << this->numeroDeSalida << ": No liberé nada y quedan [" << this->estacionamiento->getCantidadDeAutos()
				<< "] autos en el estacionamiento. ¿El estacionamiento está vacío? ";
		if (this->estacionamiento->estaVacio()) {
			info << "Si";
		} else {
			info << "No";
		}

		Log::getLog()->logMensaje(info.str());
	}
}

bool ProcesoSalida::recorrerEstacionamiento() {
	bool resultado = false;
	stringstream info;

	for (int i = 0; i < this->estacionamiento->getTamanio(); i++) {

		Lock* lockPlaza = tomarLockPlaza(i);

		if (this->estacionamiento->getPlaza(i).deseaIrse()) {
			liberarPlaza(i);
			resultado = true;

			liberarLockPlaza(i, lockPlaza);
			break;
		}

		liberarLockPlaza(i, lockPlaza);
	}

	return resultado;
}

void ProcesoSalida::liberarPlaza(int nroDePlaza) {
	long idDelAutoDesocupado = this->estacionamiento->desocuparLugar(nroDePlaza);

	stringstream info;
	info << "Salida  " << this->numeroDeSalida << ": Liberé la plaza [" << nroDePlaza << "] Id del auto que se fue [" << idDelAutoDesocupado
			<< "] Quedan [" << this->estacionamiento->getCantidadDeAutos() << "] autos en el estacionamiento"
			<< ". Cantidad Facturada [" << this->estacionamiento->getCantidadFacturado() << "]";

	Log::getLog()->logMensaje(info.str());
}

Lock* ProcesoSalida::tomarLockPlaza(int nroDePlaza) {
	Lock* lockPlaza = this->estacionamiento->getLockPlaza(nroDePlaza);
	int error = lockPlaza->tomarLock();

	if (error) {
		stringstream errorMsg;
		errorMsg << "Salida  " << this->numeroDeSalida << ": Se produjo un error al intentar tomar el lock de la plaza " << nroDePlaza + 1 << endl;
		Log::getLog()->logError(errorMsg.str());
		exit(error);
	}
	return lockPlaza;
}

void ProcesoSalida::liberarLockPlaza(int nroDePlaza, Lock* lockPlaza) {
	int error = lockPlaza->liberarLock();

	if (error) {
		stringstream errorMsg;
		errorMsg << "Salida  " << this->numeroDeSalida << ": Se produjo un error al intentar liberar el lock de la plaza " << nroDePlaza + 1 << endl;
		Log::getLog()->logError(errorMsg.str());
		exit(error);
	}
}
