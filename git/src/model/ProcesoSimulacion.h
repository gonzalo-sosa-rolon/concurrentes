#ifndef PROCESOSIMULACION_H_
#define PROCESOSIMULACION_H_

#include "Proceso.h"
#include <string>
#include <unistd.h>
#include "../signals/EventHandler.h"
#include "../signals/SignalHandler.h"
#include "../signals/SIGINT_Handler.h"
#include "../util/Log.h"
#include "../model/Estacionamiento.h"

#define CANTIDAD_ENTRADAS 3
#define CANTIDAD_SALIDAS 2

using namespace std;

class ProcesoSimulacion : public Proceso {
private:
	int tiempoEjecucion;
	pid_t entradas[CANTIDAD_ENTRADAS], salidas[CANTIDAD_SALIDAS];
	pid_t consulta;
	Estacionamiento* estacionamiento;
public:

	ProcesoSimulacion(int tiempoEjecucion, Estacionamiento* estacionamiento, pid_t* entradas, pid_t* salidas, pid_t consulta);
	virtual ~ProcesoSimulacion();
	virtual void ejecutar();
};

#endif /* PROCESOSIMULACION_H_ */
