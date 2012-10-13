#ifndef PROCESOSALIDA_H_
#define PROCESOSALIDA_H_

#include <iostream>
#include "Proceso.h"

using namespace std;

class ProcesoSalida: Proceso {
private:
	int numeroDeSalida;

public:
	ProcesoSalida(int numeroDeSalida);
	virtual ~ProcesoSalida();
	virtual void ejecutar();
};

#endif /* PROCESOSALIDA_H_ */
