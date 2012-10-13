#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "util/ProcesoEntrada.h"
#include "util/ProcesoSalida.h"
#include "util/ParserParametros.h"

#define CANTIDAD_ENTRADAS 3
#define CANTIDAD_SALIDAS 2

using namespace std;

int main(int argc, char **argv) {

	//TODO esto habria que pasar a una clase que lance los procesos

	pid_t id;

	for (int i = 0; i < CANTIDAD_ENTRADAS; i++) {
		id = fork();

		if (!id) {
			ProcesoEntrada procesoEntrada(i + 1);
			procesoEntrada.ejecutar();
			break;
		}
	}

	if (id) {
		for (int i = 0; i < CANTIDAD_SALIDAS; i++) {
			id = fork();

			if (!id) {
				ProcesoSalida procesoSalida(i + 1);
				procesoSalida.ejecutar();
				break;
			}
		}
	}

	cout << "padre muere" << endl;
	return 0;
}
