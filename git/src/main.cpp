#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "util/ProcesoEntrada.h"
#include "util/ProcesoSalida.h"
#include "util/ParserParametros.h"
#include "util/ProcesoConsulta.h"
#include "util/Lock.h"
#include "util/Log.h"
#include "util/StringUtil.h"
#include "util/NumberUtil.h"
#include <string>

#define CANTIDAD_ENTRADAS 3
#define CANTIDAD_SALIDAS 2

using namespace std;

int main(int argc, char **argv) {

	Log* log = Log::getLog();

	log->logMensaje("Hola");
	log->logError("error :S");

	cout << NumberUtil::getRandom(5) << endl;
}

int main3(int argc, char **argv) {

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

	return 0;
}
