/*
 * ProcesoGeneradorAutos.h
 *
 *  Created on: Nov 24, 2012
 *      Author: gsosarolon
 */

#ifndef PROCESOGENERADORAUTOS_H_
#define PROCESOGENERADORAUTOS_H_

#include "Proceso.h"

class ProcesoGeneradorAutos : Proceso {
public:
	static const int TIEMPO_ENTRE_AUTOS;
	ProcesoGeneradorAutos();
	virtual ~ProcesoGeneradorAutos();
	virtual void ejecutar();
};

#endif /* PROCESOGENERADORAUTOS_H_ */
