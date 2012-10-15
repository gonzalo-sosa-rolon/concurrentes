#ifndef ESTACIONAMIENTO_H_
#define ESTACIONAMIENTO_H_

#define PATH_MEMORIA_COMPARTIDA "/bin/ls"

#include "Plaza.h"
#include "../util/Lock.h"
#include "../MemoriaCompartida.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class Estacionamiento {

private:
	int tamanio;
	int precio;

	MemoriaCompartida<double> cantidadFacturado;
	Lock* lockCantidadFacturado;

	MemoriaCompartida<int> cantidadDeAutos;
	Lock* lockCantidadDeAutos;

	MemoriaCompartida<Plaza> plazas;
	Lock** lockPlazas;

public:
	Estacionamiento(int tamanio, int precio);
	virtual ~Estacionamiento();

	int getCantidadDeAutos();

	int getCantidadFacturado();
	bool estaLLeno();
	bool estaVacio();
	int getTamanio();
	void initPlazas();

	int crearOAtacharte();

	/*
	 * Se debe llamar a esta funcion para ocupar un lugar en el estacionamiento.
	 *
	 * @param pos la posicion a ocupar en el estacionamiento
	 * @return devuelve true si pudo ocupar una plaza, false en caso contrario
	 */
	bool ocuparPlaza(int pos, int tiempo, long autoId);

	/*	Se debe llamar a esta funcion para desocupar un lugar en el estacionamiento.
	 *	@return devuelve true si desocupo un lugar.
	 */
	long desocuparLugar(int posicion);

	Plaza getPlaza(int pos);
	Lock* getLockPlaza(int pos);
private:
	void innitLocks();
	char* getNombreLockPlaza(int i);
	void facturar(int tiempo);
	void incrementarFacturacion(int cantidadFacturada);
	void sumarUnAuto();
	void restarUnAuto();
};


#endif /* ESTACIONAMIENTO_H_ */
