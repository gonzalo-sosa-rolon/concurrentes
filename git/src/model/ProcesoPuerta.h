#ifndef PROCESOPUERTA_H_
#define PROCESOPUERTA_H_

#include <iostream>
#include <sstream>
#include <errno.h>

#include "Proceso.h"
#include "Mensaje.h"
#include "../util/NumberUtil.h"
#include "../util/Log.h"
#include "../util/Cola.h"

using namespace std;

class ProcesoPuerta: public Proceso {
private:
	int cantidadEntradas;
	int cantidadEntradasOcupadas;
	Cola<Mensaje::Mensaje> colaDeAutos;
	std::string nombre;


	bool ocuparPlaza();
	void logOcupePlaza(int nroPlaza, int idAuto);
	Lock* tomarLockPlaza(int nroDePlaza);
	void liberarLockPlaza(int nroDePlaza, Lock* lockPlaza);

	void liberarEntrada();
	void ocuparEntrada();

public:
	ProcesoPuerta(int numeroDeEntrada, char* nombre, char* path, char key);
	virtual ~ProcesoPuerta();
	virtual void ejecutar();
};

#endif /* PROCESOPUERTA_H_ */
