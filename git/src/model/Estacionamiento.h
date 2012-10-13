#ifndef ESTACIONAMIENTO_H_
#define ESTACIONAMIENTO_H_

#include "Plaza.h"
#include "../util/Lock.h"
#include "../util/StringUtil.h"

class Estacionamiento {

private:
	double cantidadFacturado;
	Lock* lockCantidadFacturado;

	int cantidadDeAutos;
	Lock* lockCantidadDeAutos;

	int tamanio;
	double precio;

	Plaza* plazas;
	Lock** lockPlazas;

public:
	Estacionamiento(int tamanio, double precio);
	virtual ~Estacionamiento();

	int getCantidadDeAutos();
	void incrementarCantidadDeAutos();
	void reducirCantidadDeAutos();
	double getCantidadFacturado();
	bool estaLLeno();

private:
	void innitLocks();
	char* getNombreLockPlaza(int i);
};


#endif /* ESTACIONAMIENTO_H_ */
