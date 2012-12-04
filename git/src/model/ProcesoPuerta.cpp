#include "ProcesoPuerta.h"
#include "Estacionamiento.h" //TODO Estaria bueno sacar este include

ProcesoPuerta::ProcesoPuerta(int cantidadEntradas, char* path, char key)
									: colaDeAutos(path, key) {
	this->cantidadEntradas = cantidadEntradas;
	this->cantidadEntradasOcupadas = 0;
}

ProcesoPuerta::~ProcesoPuerta() {
	colaDeAutos.destruir();
}

string ProcesoPuerta::getNombre() {
	return "";
}

void ProcesoPuerta::ejecutar() {
	//TODO Emprolijar logs

	stringstream info;

	info << getNombre() << ": Inicio de ejecucion, pid = [" << getpid() << "]";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	while (!this->terminarProceso()) {
		while ((!this->terminarProceso()) && (cantidadEntradasOcupadas < cantidadEntradas)) {
			procesarIngresoOEgreso();
		}

		info << getNombre() << ": Parece que se llenaron las puertas";
		Log::getLog()->logMensaje(info.str());
		info.str("");

		if (!this->terminarProceso()) {
			procesarEgreso();
		}
	}

	info << getNombre() << ": Recibi la señal, espero a q pasen los autos. pid = [" << getpid() << "]";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	terminarEjecucion();

	info << getNombre() << ": Termine. pid = [" << getpid() << "]";
	Log::getLog()->logMensaje(info.str());
	info.str("");
}

void ProcesoPuerta::procesarIngresoOEgreso() {
	Mensaje::Mensaje msg = leerTomarOLiberar();
	if (msg.mtype == Mensaje::TOMAR_PUERTA) {
		ocuparPuerta(msg);
	} else if (msg.mtype == Mensaje::LIBERAR_PUERTA) {
		liberarPuerta(msg);
	}
}

void ProcesoPuerta::procesarEgreso() {
	Mensaje::Mensaje msg = leerLiberar();
	liberarPuerta(msg);
}

Mensaje::Mensaje ProcesoPuerta::leerTomarOLiberar() {
	return leerMensaje(Mensaje::TOMAR_O_LIBERAR_PUERTA);
}

Mensaje::Mensaje ProcesoPuerta::leerLiberar() {
	return leerMensaje(Mensaje::LIBERAR_PUERTA);
}

Mensaje::Mensaje ProcesoPuerta::leerMensaje(int mtype) {
	stringstream info;
	Mensaje::Mensaje msg;
	int resultado = colaDeAutos.leer(mtype, &msg);

	if ((resultado == -1) && (!this->terminarProceso())) {
		info << getNombre() << "*** ERROR: " << strerror(errno) << " ***";
		Log::getLog()->logMensaje(info.str());
		info.str("");
	}

	return msg;
}

void ProcesoPuerta::ocuparPuerta(Mensaje::Mensaje &msg) {

	//TODO sacar numeros magicos
	//TODO Emprolijar logs

	stringstream info;
	msg.mtype = msg.pid;
	int resultado = colaDeAutos.escribir(msg);
	cantidadEntradasOcupadas++;

	info << getNombre() << ": Ingrese el auto [" << msg.pid << "]" << ". Resultado " << resultado;
	Log::getLog()->logMensaje(info.str());
	info.str("");

	if ((resultado == -1) && (!this->terminarProceso())) {
		info << getNombre() << "********************** OCUPAR - ERROR: " << strerror(errno);
		Log::getLog()->logMensaje(info.str());
		info.str("");

	}
}

void ProcesoPuerta::liberarPuerta(Mensaje::Mensaje &msg) {
	stringstream info;
	cantidadEntradasOcupadas--;

	info << getNombre() << ": Libere el auto [" << msg.pid << "]";
	Log::getLog()->logMensaje(info.str());
}


