#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "model/ProcesoEntrada.h"
#include "model/ProcesoSalida.h"
#include "model/ProcesoSimulacion.h"
#include "util/ParserParametros.h"
#include "model/ProcesoConsulta.h"
#include "model/Estacionamiento.h"
#include "util/Lock.h"
#include "util/Log.h"
#include "util/NumberUtil.h"
#include <string>

using namespace std;

int main(int argc, char **argv) {

	srand(time(NULL));
	int tiempo = 5;

	//TODO esto habria que pasar a una clase que lance los procesos

	pid_t id;
	Estacionamiento estacionamiento(10, 20); //dummy values
	pid_t entradas[CANTIDAD_ENTRADAS], salidas[CANTIDAD_SALIDAS];

	for (int i = 0; i < CANTIDAD_ENTRADAS; i++) {
		srand(49 * i);//Para que generen distintos randoms
		id = fork();

		if (!id) {
			ProcesoEntrada procesoEntrada(i + 1, &estacionamiento);
			procesoEntrada.ejecutar();
			entradas[i] = id;
			break;
		}
	}


	if (id) {
		for (int i = 0; i < CANTIDAD_SALIDAS; i++) {
			srand(49 * (i+3));//Para que generen distintos randoms
			id = fork();

			if (!id) {
				ProcesoSalida procesoSalida(i + 1, &estacionamiento);
				procesoSalida.ejecutar();
				salidas[i] = id;
				break;
			}
		}
	}

	string opcion;

	if (id) {
		id = fork();

		if (id) {
			ProcesoSimulacion procesoSimulacion(tiempo, entradas, salidas);
			procesoSimulacion.ejecutar();
		}
	}


	return 0;
}
