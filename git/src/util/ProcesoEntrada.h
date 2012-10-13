#ifndef PROCESOENTRADA_H_
#define PROCESOENTRADA_H_

#include "Proceso.h"
#include <iostream>

using namespace std;

class ProcesoEntrada: public Proceso {

private:
	int numeroDeEntrada;
public:
	ProcesoEntrada(int numeroDeEntrada);
	virtual ~ProcesoEntrada();

	virtual void ejecutar();
};

#endif /* PROCESOENTRADA_H_ */
