#ifndef PROCESOENTRADA_H_
#define PROCESOENTRADA_H_

#include <iostream>
#include <sstream>

#include "Proceso.h"
#include "Estacionamiento.h"
#include "../util/NumberUtil.h"
#include "../util/Log.h"

using namespace std;

class ProcesoEntrada: public Proceso {

private:
	int numeroDeEntrada;
	Estacionamiento* estacionamiento;

	bool ocuparPlaza();
	void logOcupePlaza(int nroPlaza, int idAuto);
	Lock* tomarLockPlaza(int nroDePlaza);
	void liberarLockPlaza(int nroDePlaza, Lock* lockPlaza);

public:
	ProcesoEntrada(int numeroDeEntrada, Estacionamiento* estacionamiento);
	virtual ~ProcesoEntrada();

	virtual void ejecutar();
};

#endif /* PROCESOENTRADA_H_ */
