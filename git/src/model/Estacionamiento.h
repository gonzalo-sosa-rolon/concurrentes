#ifndef ESTACIONAMIENTO_H_
#define ESTACIONAMIENTO_H_

#include "Plaza.h"
#include "../util/Mutex.h"

class Estacionamiento {

private:
	double cantidadFacturado;
	Mutex mutexCantidadFacturado;

	int cantidadDeAutos;
	Mutex mutexCantidadDeAutos;

	int tamanio;
	double precio;
	Plaza* plazas;
	Mutex* mutexPlazas;
public:
	Estacionamiento(int tamanio, double precio);
	virtual ~Estacionamiento();

	int getCantidadDeAutos();
	void incrementarCantidadDeAutos();
	void reducirCantidadDeAutos();
	double getCantidadFacturado();
	bool estaLLeno();
};


#endif /* ESTACIONAMIENTO_H_ */
