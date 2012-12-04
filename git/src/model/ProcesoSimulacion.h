#ifndef PROCESOSIMULACION_H_
#define PROCESOSIMULACION_H_

#include "Proceso.h"
#include <string>
#include <unistd.h>
#include <vector>
#include "../signals/EventHandler.h"
#include "../signals/SignalHandler.h"
#include "../signals/SIGINT_Handler.h"
#include "../util/Log.h"
#include "../model/AdministracionCliente.h"

#define CANTIDAD_ENTRADAS 3
#define CANTIDAD_SALIDAS 2

using namespace std;

class ProcesoSimulacion : public Proceso {
private:
	int tiempoEjecucion;
	std::vector<pid_t> idsAFinalizar;
	AdministracionCliente* administracionCliente;
public:

	ProcesoSimulacion(int tiempoEjecucion, AdministracionCliente* administracionCliente, std::vector<pid_t> &idsAFinalizar);
	virtual ~ProcesoSimulacion();
	virtual void ejecutar();
};

#endif /* PROCESOSIMULACION_H_ */
