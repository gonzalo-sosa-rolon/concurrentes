#ifndef ESTACIONAMIENTO_H_
#define ESTACIONAMIENTO_H_

#include "Plaza.h"
#include "../util/Lock.h"
#include "../util/StringUtil.h"
#include "../MemoriaCompartida.h"

class Estacionamiento {

private:
	double cantidadFacturado;
	Lock* lockCantidadFacturado;

	int cantidadDeAutos;
	Lock* lockCantidadDeAutos;

	int tamanio;
	double precio;

	MemoriaCompartida<Plaza> plazas;
	Lock* lockPlazas;

public:
	Estacionamiento(int tamanio, double precio);
	virtual ~Estacionamiento();

	int getCantidadDeAutos();
	void incrementarCantidadDeAutos();
	void reducirCantidadDeAutos();

	double getCantidadFacturado();
	bool estaLLeno();

	int crearOAtacharte();

	/*
	 * Se debe llamar a esta funcion para ocupar un lugar en el estacionamiento.
	 *
	 * @param tiempo el tiempo que se va a quedar el auto
	 * @return devuelve true si pudo ocupar una plaza, false en caso contrario
	 */
	bool ocuparLugar(int tiempo);

	/*	Se debe llamar a esta funcion para desocupar un lugar en el estacionamiento.
	 *	@return devuelve true si desocupo un lugar.
	 */
	bool desocuparLugar();

private:
	void innitLocks();
	char* getNombreLockPlaza(int i);
	void facturar(int tiempo);
	void incrementarFacturacion(double cantidadFacturada);
};


#endif /* ESTACIONAMIENTO_H_ */
