#ifndef PROCESOAUTO_H_
#define PROCESOAUTO_H_

#include "Auto.h"
#include "Estacionamiento.h"
#include "Proceso.h"
#include "SolicitudPuerta.h"
#include "../util/Cola.h"
#include "../util/Log.h"

class AdministracionCliente;

class ProcesoAuto : public Proceso {
private:
	Auto *autoDelProceso;
	Estacionamiento *estacionamiento;
	AdministracionCliente* administracionCliente;

public:
	ProcesoAuto(Estacionamiento *estacionamiento, AdministracionCliente* administracionCliente);
	virtual ~ProcesoAuto();
	virtual void ejecutar();
};

#endif /* PROCESOAUTO_H_ */
