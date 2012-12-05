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
#include "model/ProcesoEntrada.h"
#include "model/ProcesoSalida.h"
#include "model/ProcesoPuerta.h"
#include "model/ProcesoSimulacion.h"
#include "model/AdministradorGeneral.h"
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
	int cantidadEstacionamientos;

	ParserParametros::parsear(argc, argv, &tiempo, &precio, &capacidad, &cantidadEstacionamientos);

	pid_t id;

	AdministracionCliente administracionCliente(cantidadEstacionamientos, capacidad, precio);
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
				ProcesoEntrada procEntrada(3, (char*) Mensaje::PATH_TOKEN_COLAS_ENTRADA, i, i);
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

				ProcesoSalida procSalida(2, (char*) Mensaje::PATH_TOKEN_COLAS_SALIDA, i, &administracionCliente, i);
				procSalida.ejecutar();
				break;
			} else {
				idsAFinalizar.push_back(id);
			}
		}
	}

	pid_t pidAdminServidor;

	if (id) {
		id = fork();

		if (!id) {
			AdministradorGeneral administracionServidor(cantidadEstacionamientos, capacidad, precio);
			administracionServidor.ejecutar();
		}
		pidAdminServidor = id;
	}

	if (id) {

		id = fork();

		if (!id) {
			ProcesoConsulta procesoConsulta(&administracionCliente);
			procesoConsulta.ejecutar();

		} else {
			idsAFinalizar.push_back(id);
			ProcesoSimulacion procesoSimulacion(tiempo, &administracionCliente,	idsAFinalizar, pidAdminServidor, id);
			procesoSimulacion.ejecutar();
		}
	}

	return 0;
}
