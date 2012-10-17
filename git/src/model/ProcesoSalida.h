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
	void buscarYSacarAuto();
	bool recorrerEstacionamiento();
	void liberarPlaza(int i);

	Lock* tomarLockPlaza(int nroDePlaza);
	void liberarLockPlaza(int nroDePlaza, Lock* lockPlaza);
public:
	ProcesoSalida(int numeroDeSalida, Estacionamiento* estacionamiento);
	virtual ~ProcesoSalida();
	virtual void ejecutar();
};

#endif /* PROCESOSALIDA_H_ */
