#ifndef PARSERPARAMETROS_H_
#define PARSERPARAMETROS_H_

#include <stdlib.h>

#define TIEMPO 15
#define PRECIO_HORA 5
#define CAPACIDAD 9

#include <getopt.h>

class ParserParametros {
public:
	void static parsear(int argc, char **argv, int* tiempo, int* precio,
			int* capacidad);
};

#endif /* PARSERPARAMETROS_H_ */
