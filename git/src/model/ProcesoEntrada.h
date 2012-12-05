/*
 * ProcesoEntrada.h
 *
 *  Created on: 04/12/2012
 *      Author: maxi
 */

#ifndef PROCESOENTRADA_H_
#define PROCESOENTRADA_H_

#include "ProcesoPuerta.h"

class ProcesoEntrada: public ProcesoPuerta {
public:
	ProcesoEntrada(int cantidadEntradas, char* path, char key, int nroEstacinamiento);
	virtual ~ProcesoEntrada();

protected:
	virtual void terminarEjecucion();
	virtual std::string getNombre();
};

#endif /* PROCESOENTRADA_H_ */
