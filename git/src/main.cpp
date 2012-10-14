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

	cout << "Main Creando entradas" << endl;
	for (int i = 0; i < CANTIDAD_ENTRADAS; i++) {
		id = fork();

		if (!id) {
			ProcesoEntrada procesoEntrada(i + 1, &estacionamiento);
			procesoEntrada.ejecutar();
			entradas[i] = id;
			break;
			sleep(1);
		}
	}


	if (id) {
		cout << "Main creando salidas" << endl;
		for (int i = 0; i < CANTIDAD_SALIDAS; i++) {
			id = fork();

			if (!id) {
				ProcesoSalida procesoSalida(i + 1, &estacionamiento);
				procesoSalida.ejecutar();
				salidas[i] = id;
				break;
				sleep(1);
			}
		}
	}

	if (id) {
		cout << "Main duerme 15 segundos" << endl;
		sleep(15);
		for (int i = 0; i < CANTIDAD_SALIDAS; i++) {
			cout << "Enviando señal a salida [" << salidas[i] << "]" << endl;
			kill(salidas[i], SIGINT);
		}
		for (int i = 0; i < CANTIDAD_ENTRADAS; i++) {
			cout << "Enviando señal a entrada [" << entradas[i] << "]" << endl;
			kill(entradas[i], SIGINT);
		}

		for (int i = 0; i < 5; i++) {
			cout << "Hola, soy el padre y me pongo a esperar a mis hijos" << endl;
			wait();
			cout << "Padre: mis hijos murieron. Cantidad de autos en el estacionamiento: " << estacionamiento.getCantidadDeAutos() << endl;
		}

	}


	return 0;
}
