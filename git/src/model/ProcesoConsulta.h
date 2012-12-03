#ifndef PROCESOCONSULTA_H_
#define PROCESOCONSULTA_H_

#include "Proceso.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../model/Estacionamiento.h"
#include "../signals/EventHandler.h"
#include "../signals/SignalHandler.h"
#include "../signals/SIGINT_Handler.h"


using namespace std;

class ProcesoConsulta: public Proceso {
private:
	SIGINT_Handler sigint_handler;
	int cantidadEstacionamientos;
public:
	ProcesoConsulta(int cantidadEstacionamientos);
	virtual ~ProcesoConsulta();
	void ejecutar();

private:
	void imprimirOpciones();
	string leerOpcion();
	int leerEstacionamiento();
	void ejecutarOpcion(string opcion);

	void consultarCantidadDeAutos(int estacionamiento);
	void consultarMontoFacturado(int estacionamiento);
};

#endif /* PROCESOCONSULTA_H_ */
