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
#include "util/ParserParametros.h"
#include "util/Lock.h"
#include "util/Log.h"
#include "util/NumberUtil.h"

using namespace std;

int main(int argc, char **argv) {

	srand(time(NULL));
	int tiempo;
	int capacidad;
	int precio;

	ParserParametros::parsear(argc, argv, &tiempo, &precio, &capacidad);

	pid_t id;

	Estacionamiento estacionamiento(capacidad, precio);
	AdministracionCliente administracionCliente;
	pid_t idsAFinalizar[5];

	id = fork();

	if (!id){
		ProcesoGeneradorAutos procesoGenerador(&estacionamiento, &administracionCliente);
		procesoGenerador.ejecutar();
	} else {
		idsAFinalizar[0] = id;
	}

	if (id){
		id = fork();

		if (!id){
			ProcesoPuerta procEntrada(3, (char*)"Entrada", 'E');
			procEntrada.ejecutar();
		} else {
			idsAFinalizar[1] = id;
		}
	}

	if (id){
		id = fork();

		if (!id){
			ProcesoPuerta procSalida(3, (char*)"Salida", 'S');
			procSalida.ejecutar();
		} else {
			idsAFinalizar[2] = id;
		}
	}

	if (id) {
		id = fork();

		if (id) {
			idsAFinalizar[3] = id;
			ProcesoSimulacion procesoSimulacion(tiempo, &estacionamiento, idsAFinalizar, 4);
			procesoSimulacion.ejecutar();

			for (int i = 0; i < 6; i++) {
				//TODO ver de esperar a los procesos waitpid(0);
			}
		} else {
			ProcesoConsulta procesoConsulta(&estacionamiento);
			procesoConsulta.ejecutar();
		}
	}

	return 0;
}
