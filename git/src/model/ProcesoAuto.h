#ifndef PROCESOAUTO_H_
#define PROCESOAUTO_H_

#include "Proceso.h"
#include "Auto.h"
#include "Estacionamiento.h"

class ProcesoAuto : public Proceso {
private:
	Auto *autoDelProceso;
	Estacionamiento *estacionamiento;
public:
	ProcesoAuto(Estacionamiento *estacionamiento);
	virtual ~ProcesoAuto();
	virtual void ejecutar();
};

#endif /* PROCESOAUTO_H_ */
