#ifndef PROCESOCONSULTA_H_
#define PROCESOCONSULTA_H_

#include "Proceso.h"
#include <iostream>
#include <string>

using namespace std;

class ProcesoConsulta: public Proceso {

public:
	ProcesoConsulta();
	virtual ~ProcesoConsulta();
	void ejecutar();

private:
	void imprimirOpciones();
	string leerOpcion();
	void ejecutarOpcion(string opcion);
};

#endif /* PROCESOCONSULTA_H_ */
