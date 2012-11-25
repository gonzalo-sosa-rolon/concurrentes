#ifndef ESTACIONAMIENTO_H_
#define ESTACIONAMIENTO_H_

#include <sstream>
#include <string>
#include <iostream>
#include "Plaza.h"
#include "../MemoriaCompartida.h"
#include "../util/Lock.h"
#include "../util/Log.h"
#include "../util/ParserParametros.h"

using namespace std;

class Estacionamiento {

public:

	static const char* PATH_TOKEN_MEMORIA_COMPARTIDA;

	Estacionamiento(int tamanio, int precio);
	virtual ~Estacionamiento();

	int getCantidadDeAutos();

	int getCantidadFacturado();
	bool estaLLeno();
	bool estaVacio();
	int getTamanio();
	void initPlazas();

	bool ocuparPlaza(int pos, int tiempo, long autoId);
	long desocuparLugar(int posicion);

	Plaza getPlaza(int pos);
	Lock* getLockPlaza(int pos);
	bool solicitarLugar();
private:
	int tamanio;
	int precio;

	MemoriaCompartida<double> cantidadFacturado;
	Lock* lockCantidadFacturado;

	MemoriaCompartida<int> cantidadDeAutos;
	Lock* lockCantidadDeAutos;

	MemoriaCompartida<Plaza> plazas;
	Lock** lockPlazas;

	void innitLocks();
	char* getNombreLockPlaza(int i);
	void facturar(int segundos);
	void incrementarFacturacion(int cantidadFacturada);
	void sumarUnAuto();
	void restarUnAuto();
	void eliminarLocks();
	void imprimirError(int error);
	void imprimirErrorLock();

};



#endif /* ESTACIONAMIENTO_H_ */
