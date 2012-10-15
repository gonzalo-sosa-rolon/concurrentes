#ifndef PROCESOCONSULTA_H_
#define PROCESOCONSULTA_H_

#include "Proceso.h"
#include <iostream>
#include <string>
#include "../model/Estacionamiento.h"
#include "../signals/EventHandler.h"
#include "../signals/SignalHandler.h"
#include "../signals/SIGINT_Handler.h"


using namespace std;

class ProcesoConsulta: public Proceso {
private:
	Estacionamiento* estacionamiento;
	SIGINT_Handler sigint_handler;
public:
	ProcesoConsulta(Estacionamiento* estacionamiento);
	virtual ~ProcesoConsulta();
	void ejecutar();

private:
	void imprimirOpciones();
	string leerOpcion();
	void ejecutarOpcion(string opcion);

	void consultarCantidadDeAutos();
	void consultarMontoFacturado();
};

#endif /* PROCESOCONSULTA_H_ */
