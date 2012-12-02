#ifndef ADMINISTRACIONSERVIDOR_H_
#define ADMINISTRACIONSERVIDOR_H_

#include <vector>
#include "Proceso.h"
#include "Mensaje.h"
#include "../util/Cola.h"

class Estacionamiento;

using namespace std;

class AdministracionServidor : public Proceso {
private:
	int cantidadEstacionamientos;
	int tamanio;
	int precio;
	vector<Estacionamiento*> estacionamientos;
	Cola<Mensaje::Mensaje> colaDeMensajes;
public:
	AdministracionServidor(int cantidadEstacionamientos, int tamanio, int precio);
	virtual ~AdministracionServidor();
	virtual void ejecutar();

private:
	void crearEstacionamientos();
};

#endif /* ADMINISTRACIONSERVIDOR_H_ */
