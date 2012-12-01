#include "ProcesoSimulacion.h"

ProcesoSimulacion::ProcesoSimulacion(int tiempoEjecucion, Estacionamiento* estacionamiento, pid_t* idsAFinalizar, int cantidadIds) {
	this->tiempoEjecucion = tiempoEjecucion;
	this->estacionamiento = estacionamiento;

	this->idsAFinalizar = new pid_t[cantidadIds];
	this->cantidadIds = cantidadIds;

	for (int i = 0; i < cantidadIds; i++) {
		this->idsAFinalizar[i] = idsAFinalizar[i];
	}
}

ProcesoSimulacion::~ProcesoSimulacion() {

}

void ProcesoSimulacion::ejecutar() {
	stringstream info;

	cout << "Comienzo de la ejecucion por " << tiempoEjecucion << " segundos" << endl;
	sleep(tiempoEjecucion);

	info << "Finalizando Ejecucion, enviando señales a procesos";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	for (int i = 0; i < this->cantidadIds; i++) {
		kill(idsAFinalizar[i], SIGINT);
	}

	cout << "Finalizacion de la ejecucion" << endl;
}
