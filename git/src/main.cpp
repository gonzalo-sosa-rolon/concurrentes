#include <iostream>
#include <unistd.h>
#include <sys/types.h>
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
	int tiempo;
	int capacidad;
	int precio;

	ParserParametros::parsear(argc, argv, &tiempo, &precio, &capacidad);

	pid_t id;

	Estacionamiento estacionamiento(capacidad, precio);
	pid_t entradas[CANTIDAD_ENTRADAS], salidas[CANTIDAD_SALIDAS];

	for (int i = 0; i < CANTIDAD_ENTRADAS; i++) {
		srand(49 * i);//Para que generen distintos randoms
		id = fork();

		if (!id) {
			ProcesoEntrada procesoEntrada(i + 1, &estacionamiento);
			procesoEntrada.ejecutar();
			break;
		} else {
			entradas[i] = id;
		}
	}


	if (id) {
		for (int i = 0; i < CANTIDAD_SALIDAS; i++) {
			srand(49 * (i+3));//Para que generen distintos randoms
			id = fork();

			if (!id) {
				ProcesoSalida procesoSalida(i + 1, &estacionamiento);
				procesoSalida.ejecutar();
				break;
			} else {
				salidas[i] = id;
			}
		}
	}

	if (id) {
		id = fork();

		if (id) {
			ProcesoSimulacion procesoSimulacion(tiempo, &estacionamiento, entradas, salidas, id);
			procesoSimulacion.ejecutar();
			for (int i = 0; i < 6; i++) {
				wait();
			}
		} else {
			ProcesoConsulta procesoConsulta(&estacionamiento);
			procesoConsulta.ejecutar();
		}
	}

	return 0;
}
