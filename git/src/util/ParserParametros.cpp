#include "ParserParametros.h"

void ParserParametros::parsear(int argc, char **argv, int* tiempo, int* precio,
		int* capacidad, int* cantidadEstacionamientos) {

	char opcion = 0;
	int tiempoPorParametro = TIEMPO_DEFAULT;
	int precioPorParametro = PRECIO_HORA_DEFAULT;
	int capacidadPorParametro = CAPACIDAD_DEFAULT;
	int cantEstacionamientosPorParametro = CANTIDAD_ESTACION_DEFAULT;

	while ((opcion = getopt(argc, argv, "t:c:p:e:")) != -1) {

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
		case 'e':
			cantEstacionamientosPorParametro = atoi(value);
			break;
		default:
			abort();
			break;
		}
	}
	*tiempo = tiempoPorParametro;
	*precio = precioPorParametro;
	*capacidad = capacidadPorParametro;
	*cantidadEstacionamientos = cantEstacionamientosPorParametro;
}
