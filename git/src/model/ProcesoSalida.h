#ifndef PROCESOSALIDA_H_
#define PROCESOSALIDA_H_

#include <iostream>
#include <sstream>

#include "Estacionamiento.h"
#include "Proceso.h"
#include "../util/Log.h"

using namespace std;

class ProcesoSalida: Proceso {
private:
	int numeroDeSalida;
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
