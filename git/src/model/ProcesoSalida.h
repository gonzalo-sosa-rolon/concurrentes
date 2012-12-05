/*
 * ProcesoSalida.h
 *
 *  Created on: 04/12/2012
 *      Author: maxi
 */

#ifndef PROCESOSALIDA_H_
#define PROCESOSALIDA_H_

#include "ProcesoPuerta.h"
#include "AdministracionCliente.h"

class ProcesoSalida: public ProcesoPuerta {
public:
	ProcesoSalida(int cantidadEntradas, char* path, char key,
				AdministracionCliente* administracionCliente, int nroEstacionamiento);
	virtual ~ProcesoSalida();

protected:
	virtual void terminarEjecucion();
	virtual std::string getNombre();

private:
	AdministracionCliente* adminCliente;
	int getCantidadAutos();

};

#endif /* PROCESOSALIDA_H_ */
