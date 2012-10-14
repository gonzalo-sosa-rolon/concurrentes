#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "model/ProcesoEntrada.h"
#include "model/ProcesoSalida.h"
#include "util/ParserParametros.h"
#include "model/ProcesoConsulta.h"
#include "model/Estacionamiento.h"
#include "signals/EventHandler.h"
#include "signals/SignalHandler.h"
#include "signals/SIGINT_Handler.h"
#include "util/Lock.h"
#include "util/Log.h"
#include "util/StringUtil.h"
#include "util/NumberUtil.h"
#include <string>

#define CANTIDAD_ENTRADAS 3
#define CANTIDAD_SALIDAS 2

using namespace std;

int main(int argc, char **argv) {

	srand(time(NULL));

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

	if (id) {
		cout << "Main duerme 150 segundos" << endl;
		sleep(150);
		for (int i = 0; i < CANTIDAD_SALIDAS; i++) {
			cout << "Enviando señal a salida [" << salidas[i] << "]" << endl;
			kill(salidas[i], SIGINT);
		}
		for (int i = 0; i < CANTIDAD_ENTRADAS; i++) {
			cout << "Enviando señal a entrada [" << entradas[i] << "]" << endl;
			kill(entradas[i], SIGINT);
		}
	}

	return 0;
}
