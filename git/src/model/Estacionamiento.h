#ifndef ESTACIONAMIENTO_H_
#define ESTACIONAMIENTO_H_

#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "Plaza.h"
#include "../MemoriaCompartida.h"
#include "../util/Cola.h"
#include "../util/Log.h"
#include "../util/ParserParametros.h"

class Auto;

using namespace std;

class Estacionamiento {

public:

	static const char* PATH_TOKEN_MEMORIA_COMPARTIDA;
	static const char* PATH_TOKEN_COLAS;

	Estacionamiento(int tamanio, int precio, int cantidadEntradas = 3, int cantidadSalidas = 2);
	virtual ~Estacionamiento();

	int getCantidadDeAutos();

	int getCantidadFacturado();
	bool estaLLeno();
	bool estaVacio();
	int getTamanio();
	void initPlazas();

	bool ocuparPlaza(int pos, int tiempo, long autoId);
	long desocuparLugar(int posicion);

	Plaza* getPlaza(int pos);
	bool solicitarLugar();
	int seleccionarPlaza(int tiempo, long autoId);

	void salirDelEstacionamiento();
private:
	int tamanio;
	int precio;
	int cantidadEntradas;
	int cantidadSalidas;

	int cantidadFacturado;
	int cantidadDeAutos;

	vector<Plaza*> plazas;

	char* getNombreLockPlaza(int i);
	void facturar(int segundos);
	void incrementarFacturacion(int cantidadFacturada);
	void sumarUnAuto();
	void restarUnAuto();
	void imprimirError(int error);
	void logOcupePlaza(int nroPlaza, int idAuto);
};



#endif /* ESTACIONAMIENTO_H_ */
