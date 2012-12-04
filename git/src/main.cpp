#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

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

	AdministracionCliente administracionCliente(cantidadEstacionamientos,
			capacidad, precio);
	std::vector<pid_t> idsAFinalizar;

	id = fork();

	if (!id) {
		ProcesoGeneradorAutos procesoGenerador(&administracionCliente);
		procesoGenerador.ejecutar();
	} else {
		idsAFinalizar.push_back(id);
	}

	if (id) {
		for (int i = 0; i < cantidadEstacionamientos; i++) {
			id = fork();

			if (!id) {
				ProcesoPuerta procEntrada(3, (char*) "Entrada",
						(char*) Mensaje::PATH_TOKEN_COLAS_ENTRADA, i);
				procEntrada.ejecutar();
				break;
			} else {
				idsAFinalizar.push_back(id);
			}
		}

	}

	if (id) {
		for (int i = 0; i < cantidadEstacionamientos; i++) {
			id = fork();

			if (!id) {

				ProcesoPuerta procSalida(3, (char*) "Salida",
						(char*) Mensaje::PATH_TOKEN_COLAS_SALIDA, i);
				procSalida.ejecutar();
				break;
			} else {
				idsAFinalizar.push_back(id);
			}
		}
	}

	if (id) {
		id = fork();

		if (!id) {
			AdministracionServidor administracionServidor(cantidadEstacionamientos, capacidad, precio);
			administracionServidor.ejecutar();
		}
		idsAFinalizar.push_back(id);
	}

	if (id) {

		id = fork();

		if (!id) {
			ProcesoConsulta procesoConsulta(&administracionCliente);
			procesoConsulta.ejecutar();

		} else {
			//idsAFinalizar.push_back(id); // TODO revisar si hay q agregar este pid para q mate al proceso consulta
			ProcesoSimulacion procesoSimulacion(tiempo, &administracionCliente,	idsAFinalizar);
			procesoSimulacion.ejecutar();
		}
	}

	return 0;
}
