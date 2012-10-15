#include "ProcesoSimulacion.h"

ProcesoSimulacion::ProcesoSimulacion(int tiempoEjecucion, pid_t entradas[], pid_t salidas[]) {
	this->tiempoEjecucion = tiempoEjecucion;

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
		cout << "Enviando señal a salida [" << salidas[i] << "]" << endl ;
		kill(salidas[i], SIGINT);
	}

	for (int i = 0; i < CANTIDAD_ENTRADAS; i++) {
		cout << "Enviando señal a entrada [" << entradas[i] << "]" << endl;
		kill(entradas[i], SIGINT);
	}

	cout << "Finalizacion de la ejecucion" << endl;
}
