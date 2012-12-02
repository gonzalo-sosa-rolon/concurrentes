#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include "model/Estacionamiento.h"
#include "model/ProcesoGeneradorAutos.h"
#include "model/ProcesoConsulta.h"
#include "model/AdministracionCliente.h"
#include "model/ProcesoPuerta.h"
#include "model/ProcesoSimulacion.h"
#include "model/AdministracionServidor.h"
#include "util/ParserParametros.h"
#include "util/Lock.h"
#include "util/Log.h"
#include "util/NumberUtil.h"
#include "model/Mensaje.h"

using namespace std;

int main(int argc, char **argv) {

	srand(time(NULL));
	int tiempo;
	int capacidad;
	int precio;
	int cantidadEstacionamientos = 1;

	ParserParametros::parsear(argc, argv, &tiempo, &precio, &capacidad, &cantidadEstacionamientos);

	pid_t id;

	Estacionamiento estacionamiento(capacidad, precio);
	AdministracionCliente administracionCliente(cantidadEstacionamientos,
			capacidad, precio);
	pid_t idsAFinalizar[6];

	id = fork();

	if (!id) {
		ProcesoGeneradorAutos procesoGenerador(&estacionamiento,
				&administracionCliente);
		procesoGenerador.ejecutar();
	} else {
		idsAFinalizar[0] = id;
	}

	if (id) {
		for (int i = 0; i < cantidadEstacionamientos; i++) {
			id = fork();

			if (!id) {
				ProcesoPuerta procEntrada(3, (char*) "Entrada",
						(char*) Mensaje::PATH_TOKEN_COLAS_ENTRADA, i);
				procEntrada.ejecutar();
				break;
			}
		}

	} else {
		idsAFinalizar[1] = id;
	}

	if (id) {
		for (int i = 0; i < cantidadEstacionamientos; i++) {
			id = fork();

			if (!id) {

				ProcesoPuerta procSalida(3, (char*) "Salida",
						(char*) Mensaje::PATH_TOKEN_COLAS_SALIDA, i);
				procSalida.ejecutar();
				break;
			}
		}
	} else {
		idsAFinalizar[2] = id;
	}

	if (id) {
		id = fork();
		idsAFinalizar[3] = id;

		if (!id) {
			AdministracionServidor administracionServidor(
					cantidadEstacionamientos, capacidad, precio);
			administracionServidor.ejecutar();
		}
	}

	if (id) {
		id = fork();

		if (id) {
			idsAFinalizar[4] = id;
			ProcesoSimulacion procesoSimulacion(tiempo, &estacionamiento,
					idsAFinalizar, 5);
			procesoSimulacion.ejecutar();

		} else {
			ProcesoConsulta procesoConsulta(&estacionamiento);
			procesoConsulta.ejecutar();
		}
	}

	return 0;
}
