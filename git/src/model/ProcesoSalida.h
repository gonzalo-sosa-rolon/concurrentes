#ifndef PROCESOSALIDA_H_
#define PROCESOSALIDA_H_

#include <iostream>
#include "Estacionamiento.h"
#include "Proceso.h"
#include "../signals/EventHandler.h"
#include "../signals/SignalHandler.h"
#include "../signals/SIGINT_Handler.h"
#include "../util/Log.h"
#include <sstream>

using namespace std;

class ProcesoSalida: Proceso {
private:
	int numeroDeSalida;
	SIGINT_Handler sigint_handler;
	Estacionamiento* estacionamiento;
	void liberarPlaza();
public:
	ProcesoSalida(int numeroDeSalida, Estacionamiento* estacionamiento);
	virtual ~ProcesoSalida();
	virtual void ejecutar();
};

#endif /* PROCESOSALIDA_H_ */
