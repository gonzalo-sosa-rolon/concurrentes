#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>

#define TIEMPO 1500
#define PRECIO_HORA 5
#define CAPACIDAD 10

using namespace std;

void parsearOpciones(int argc, char **argv, int* tiempo, int* precio, int* capacidad) {

	char opcion = 0;
	int tiempoPorParametro = TIEMPO;
	int precioPorParametro = PRECIO_HORA;
	int capacidadPorParametro = CAPACIDAD;

	while ((opcion = getopt(argc, argv, "t:c:p:")) != -1) {

		char* value = optarg;

		if (opcion == -1) {
			break;
		}

		if (!value) {
			break;
		}

		switch (opcion) {
		case 't':
			tiempoPorParametro = atoi(value);
			break;
		case 'p':
			precioPorParametro = atoi(value);
			break;
		case 'c':
			capacidadPorParametro = atoi(value);
			break;
		default:
			abort();
					break;
		}
	}
	*tiempo = tiempoPorParametro;
	*precio = precioPorParametro;
	*capacidad = capacidadPorParametro;
}


int main(int argc, char **argv) {

	int tiempo, precio, capacidad;
	parsearOpciones(argc, argv, &tiempo, &precio, &capacidad);

	cout << "Tiempo " << tiempo << endl;
	cout << "Costo " << precio << endl;
	cout << "Espacio " << capacidad << endl;

	return 0;
}
