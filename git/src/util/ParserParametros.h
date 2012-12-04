#ifndef PARSERPARAMETROS_H_
#define PARSERPARAMETROS_H_

#include <stdlib.h>

#include <getopt.h>

class ParserParametros {
public:
	void static parsear(int argc, char **argv, int* tiempo, int* precio,
			int* capacidad, int* cantidadEstacionamientos);

	static const int TIEMPO_DEFAULT = 10;
	static const int PRECIO_HORA_DEFAULT = 5;
	static const int CAPACIDAD_DEFAULT = 5;
	static const int CANTIDAD_ESTACION_DEFAULT = 1;

	static const int ENTRADA_SLEEP_MIN_DEFAULT = 1;
	static const int ENTRADA_SLEEP_MAX_DEFAULT = 3;
	static const int TIEMPO_ESTADIA_MIN_DEFAULT = 5;
	static const int TIEMPO_ESTADIA_MAX_DEFAULT = 15;
	static const int SEGUNDOS_POR_HORA_DEFAULT = 1;
};

#endif /* PARSERPARAMETROS_H_ */
