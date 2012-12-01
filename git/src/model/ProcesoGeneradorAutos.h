/*
 * ProcesoGeneradorAutos.h
 *
 *  Created on: Nov 24, 2012
 *      Author: gsosarolon
 */

#ifndef PROCESOGENERADORAUTOS_H_
#define PROCESOGENERADORAUTOS_H_

#include <unistd.h>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include "Proceso.h"
#include "../util/NumberUtil.h"
#include "ProcesoAuto.h"
#include "../util/Log.h"

class Estacionamiento;
class AdministracionCliente;

class ProcesoGeneradorAutos : Proceso {
private:
	Estacionamiento *estacionamiento;
	AdministracionCliente* administracionCliente;
public:
	static const int TIEMPO_ENTRE_AUTOS;
	ProcesoGeneradorAutos(Estacionamiento *estacionamiento, AdministracionCliente* administracionCliente);
	virtual ~ProcesoGeneradorAutos();
	virtual void ejecutar();
};

#endif /* PROCESOGENERADORAUTOS_H_ */
