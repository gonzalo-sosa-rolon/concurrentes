#include "ProcesoSimulacion.h"

ProcesoSimulacion::ProcesoSimulacion(int tiempoEjecucion, Estacionamiento* estacionamiento, pid_t* entradas, pid_t* salidas, pid_t consulta) {
	this->tiempoEjecucion = tiempoEjecucion;
	this->estacionamiento = estacionamiento;
	this->consulta = consulta;

	for (int i = 0; i < CANTIDAD_ENTRADAS; i++) {
		this->entradas[i] = entradas[i];
	}

	for (int i = 0; i < CANTIDAD_SALIDAS; i++) {
		this->salidas[i] = salidas[i];
	}
}

ProcesoSimulacion::~ProcesoSimulacion() {

}

void ProcesoSimulacion::ejecutar() {

	cout << "Comienzo de la ejecucion por " << tiempoEjecucion << " segundos" << endl;
	sleep(tiempoEjecucion);

	for (int i = 0; i < CANTIDAD_SALIDAS; i++) {
		kill(salidas[i], SIGINT);
	}

	for (int i = 0; i < CANTIDAD_ENTRADAS; i++) {
		kill(entradas[i], SIGINT);
	}

	kill(consulta, SIGINT);
	cout << "Finalizacion de la ejecucion" << endl;
}
