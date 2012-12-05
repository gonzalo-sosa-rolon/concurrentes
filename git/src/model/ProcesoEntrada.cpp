/*
 * ProcesoEntrada.cpp
 *
 *  Created on: 04/12/2012
 *      Author: maxi
 */

#include "ProcesoEntrada.h"

ProcesoEntrada::ProcesoEntrada(int cantidadEntradas, char* path, char key)
	:ProcesoPuerta(cantidadEntradas, path, key) {

}

ProcesoEntrada::~ProcesoEntrada() {
	// TODO Auto-generated destructor stub
}


void ProcesoEntrada::terminarEjecucion() {

	while (cantidadEntradasOcupadas > 0) {
		Mensaje::Mensaje msg = leerLiberar();
		liberarPuerta(msg);
	}

}

std::string ProcesoEntrada::getNombre() {
	return string("Entrada");
}
