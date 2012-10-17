#ifndef PROCESOENTRADA_H_
#define PROCESOENTRADA_H_

#include "Proceso.h"
#include "Estacionamiento.h"
#include <iostream>
#include "../signals/EventHandler.h"
#include "../signals/SignalHandler.h"
#include "../signals/SIGINT_Handler.h"
#include "../util/NumberUtil.h"
#include "../util/Log.h"
#include <sstream>

using namespace std;

class ProcesoEntrada: public Proceso {

private:
	int numeroDeEntrada;
	Estacionamiento* estacionamiento;
	SIGINT_Handler sigint_handler;

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
