#include "ProcesoPuerta.h"

#include "Estacionamiento.h" //TODO Estaria bueno sacar este include

ProcesoPuerta::ProcesoPuerta(int cantidadEntradas, char* nombre, char key)
									: colaDeAutos((char*)Estacionamiento::PATH_TOKEN_COLAS, key), nombre(nombre) {
	this->cantidadEntradas = cantidadEntradas;
	this->cantidadEntradasOcupadas = 0;
}

ProcesoPuerta::~ProcesoPuerta() {
	colaDeAutos.destruir();
}

void ProcesoPuerta::ejecutar() {
	//TODO Emprolijar logs

	stringstream info;

	while (!this->terminarProceso()) {
		while ((!this->terminarProceso()) && (cantidadEntradasOcupadas < cantidadEntradas)) {
			ocuparEntrada();
		}

		info << nombre << ": Parece que se llenaron las entradas";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		if (!this->terminarProceso()) {
			liberarEntrada();
		}
	}

	for (int i = 0; i < cantidadEntradasOcupadas; i++) {
		liberarEntrada();
	}
}

void ProcesoPuerta::ocuparEntrada() {

	//TODO sacar numeros magicos
	//TODO Emprolijar logs

	stringstream info;

	info << nombre << ": Espero a leer una solicitud";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	solicitudPuerta solicitud;
	colaDeAutos.leer(2, &solicitud);
	solicitud.mtype = solicitud.pid;
	int resultado = colaDeAutos.escribir(solicitud);
	cantidadEntradasOcupadas++;

	info << nombre << ": Ingrese el auto [" << solicitud.pid << "]" << ". Resultado " << resultado;
	Log::getLog()->logMensaje(info.str());
	info.str("");

	if (resultado == -1) {
		info << "ERROR: " << strerror(errno);
		Log::getLog()->logMensaje(info.str());
		info.str("");
	}
}

void ProcesoPuerta::liberarEntrada() {

	//TODO sacar numeros magicos
	//TODO Emprolijar logs

	stringstream info;
	solicitudPuerta liberado;
	int resultado = colaDeAutos.leer(3, &liberado);
	cantidadEntradasOcupadas--;

	info << nombre << ": Libere el auto [" << liberado.pid << "]" << ". Resultado " << resultado;
	Log::getLog()->logMensaje(info.str());
	info.str("");

	if (resultado == -1) {
		info << "ERROR: " << strerror(errno);
		Log::getLog()->logMensaje(info.str());
		info.str("");
	}
}















//void ProcesoPuerta::ejecutar() {
//	while (!this->terminarProceso()) {
//
//		if (!this->estacionamiento->estaLLeno()) {
//
//			if (!ocuparPlaza()) {
//				stringstream error;
//				error << "Entrada " << this->numeroDeEntrada << "algo anda mal, el estacionamiento no esta lleno pero no pude ingresar un auto";
//				Log::getLog()->logError(error.str());
//			}
//
//		} else {
//			stringstream info;
//			info << "Entrada " << this->numeroDeEntrada << ": Se lleno el estacionamiento";
//			Log::getLog()->logMensaje(info.str());
//		}
//
//		sleep(NumberUtil::getRandom(ParserParametros::ENTRADA_SLEEP_MIN_DEFAULT, ParserParametros::ENTRADA_SLEEP_MAX_DEFAULT));
//	}
//
//	stringstream info;
//	info << "Entrada " << this->numeroDeEntrada << ": Fin del proceso. Pid [" << getpid() << "]";
//	Log::getLog()->logMensaje(info.str());
//}
//
//bool ProcesoEntrada::ocuparPlaza() {
//	bool resultado = false;
//	int tiempo = NumberUtil::getRandom(ParserParametros::TIEMPO_ESTADIA_MIN_DEFAULT, ParserParametros::TIEMPO_ESTADIA_MAX_DEFAULT);
//
//	for (int i = 0; i < this->estacionamiento->getTamanio(); i++) {
//		Lock* lockPlaza = ProcesoEntrada::tomarLockPlaza(i);
//
//		if (!this->estacionamiento->getPlaza(i).getOcupado()) {
//			long id = NumberUtil::getRandom(RAND_MAX);
//			this->estacionamiento->ocuparPlaza(i, tiempo, id);
//
//			logOcupePlaza(i, id);
//
//			liberarLockPlaza(i, lockPlaza);
//			resultado = true;
//
//			break;
//		}
//		liberarLockPlaza(i, lockPlaza);
//	}
//
//	return resultado;
//}
//
//void ProcesoEntrada::logOcupePlaza(int nroPlaza, int idAuto) {
//	stringstream info;
//	info << "Entrada " << numeroDeEntrada << ": Ocupé la plaza [" << nroPlaza << "] Id del auto [" << idAuto << "]"
//			<< " Cantidad de autos en el estacionamiento [" << this->estacionamiento->getCantidadDeAutos() << "]";
//	Log::getLog()->logMensaje(info.str());
//}
//
//Lock* ProcesoEntrada::tomarLockPlaza(int nroDePlaza) {
//	Lock* lockPlaza = this->estacionamiento->getLockPlaza(nroDePlaza);
//	int error = lockPlaza->tomarLock();
//
//	if (error) {
//		stringstream errorMsg;
//		errorMsg << "Entrada " << this->numeroDeEntrada << ": Se produjo un error al intentar tomar el lock de la plaza " << nroDePlaza + 1 << endl;
//		Log::getLog()->logError(errorMsg.str());
//		exit(error);
//	}
//	return lockPlaza;
//}
//
//void ProcesoEntrada::liberarLockPlaza(int nroDePlaza, Lock* lockPlaza) {
//	int error = lockPlaza->liberarLock();
//
//	if (error) {
//		stringstream errorMsg;
//		errorMsg << "Entrada " << this->numeroDeEntrada << ": Se produjo un error al intentar liberar el lock de la plaza " << nroDePlaza + 1 << endl;
//		Log::getLog()->logError(errorMsg.str());
//		exit(error);
//	}
//}

