#ifndef PROCESOPUERTA_H_
#define PROCESOPUERTA_H_

#include <iostream>
#include <sstream>
#include <errno.h>

#include "Proceso.h"
#include "Mensaje.h"
#include "../util/NumberUtil.h"
#include "../util/Log.h"
#include "../util/Cola.h"

using namespace std;

class ProcesoPuerta: public Proceso {

public:
	ProcesoPuerta(int numeroDeEntrada, char* path, char key);
	virtual ~ProcesoPuerta();
	virtual void ejecutar();

protected:
	int cantidadEntradas;
	int cantidadEntradasOcupadas;
	Cola<Mensaje::Mensaje> colaDeAutos;


	void liberarPuerta(Mensaje::Mensaje &msg);
	void ocuparPuerta(Mensaje::Mensaje &msg);
	Mensaje::Mensaje leerMensaje(int mtype);

	Mensaje::Mensaje leerTomarOLiberar();
	Mensaje::Mensaje leerLiberar();

	/*
	 * Metodo q se ejecuta despues de recibir la señal
	 */
	virtual void terminarEjecucion() = 0;
	virtual string getNombre();

	void procesarIngresoOEgreso();
	void procesarEgreso();

};

#endif /* PROCESOPUERTA_H_ */
