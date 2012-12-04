#include "ProcesoPuerta.h"
#include "Estacionamiento.h" //TODO Estaria bueno sacar este include

ProcesoPuerta::ProcesoPuerta(int cantidadEntradas, char* nombre, char* path, char key)
									: colaDeAutos(path, key), nombre(nombre) {
	this->cantidadEntradas = cantidadEntradas;
	this->cantidadEntradasOcupadas = 0;
}

ProcesoPuerta::~ProcesoPuerta() {
	colaDeAutos.destruir();
}

void ProcesoPuerta::ejecutar() {
	//TODO Emprolijar logs

	stringstream info;

	info << nombre << ": Inicio de ejecucion, pid = [" << getpid() << "]";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	while (!this->getCondicionTerminar()) {
		while ((!this->terminarProceso()) && (cantidadEntradasOcupadas < cantidadEntradas)) {
			ocuparEntrada();
		}

		info << nombre << ": Parece que se llenaron las entradas";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		if (!this->getCondicionTerminar()) {
			liberarEntrada();
		}
	}

	info << nombre << ": Recibi la señal, espero a q pasen los autos. pid = [" << getpid() << "]";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	for (int i = 0; i < cantidadEntradasOcupadas; i++) {
		liberarEntrada();
	}

	info << nombre << ": Termine. pid = [" << getpid() << "]";
	Log::getLog()->logMensaje(info.str());
	info.str("");
}

void ProcesoPuerta::ocuparEntrada() {

	//TODO sacar numeros magicos
	//TODO Emprolijar logs

	stringstream info;

	info << nombre << ": Espero a leer una solicitud";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	Mensaje::Mensaje solicitud;
	colaDeAutos.leer(Mensaje::TOMAR_PUERTA, &solicitud);
	solicitud.mtype = solicitud.pid;
	int resultado = colaDeAutos.escribir(solicitud);
	cantidadEntradasOcupadas++;

	info << nombre << ": Ingrese el auto [" << solicitud.pid << "]" << ". Resultado " << resultado;
	Log::getLog()->logMensaje(info.str());
	info.str("");

	if ((resultado == -1) && (!this->terminarProceso())) {
		info << nombre << "********************** OCUPAR - ERROR: " << strerror(errno);
		Log::getLog()->logMensaje(info.str());
		info.str("");
	}
}

void ProcesoPuerta::liberarEntrada() {

	//TODO sacar numeros magicos
	//TODO Emprolijar logs

	stringstream info;
	Mensaje::Mensaje liberado;
	int resultado = colaDeAutos.leer(Mensaje::LIBERAR_PUERTA, &liberado);
	cantidadEntradasOcupadas--;

	info << nombre << ": Libere el auto [" << liberado.pid << "]" << ". Resultado " << resultado;

	Log::getLog()->logMensaje(info.str());
	info.str("");

	if ((resultado == -1) && (!this->terminarProceso())) {
		info << nombre << "********************** LIBERAR - ERROR: " << strerror(errno);
		Log::getLog()->logMensaje(info.str());
		info.str("");
	}
}


