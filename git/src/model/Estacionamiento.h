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
#include "../util/Semaforo.h"

class Auto;

using namespace std;

class Estacionamiento {

public:

	static const char* PATH_TOKEN_MEMORIA_COMPARTIDA;
	static const char* PATH_TOKEN_SEMAFORO;

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

	Plaza getPlaza(int pos);
	Lock* getLockPlaza(int pos);
	bool solicitarLugar();
	bool ocuparPlaza(Auto *automovil);
	bool liberarPlaza(Auto *automovil);
	bool solicitarEntrada();
	bool liberarEntrada();
	bool solicitarSalida();
	bool liberarSalida();
private:
	int tamanio;
	int precio;
	int cantidadEntradas;
	int cantidadSalidas;

	MemoriaCompartida<double> cantidadFacturado;
	Lock* lockCantidadFacturado;

	MemoriaCompartida<int> cantidadDeAutos;
	Lock* lockCantidadDeAutos;

	MemoriaCompartida<Plaza> plazas;
	Lock** lockPlazas;
	Semaforo *semaforoEntrada, *semaforoSalida;

	void innitLocks();
	void innitSemaforos();
	char* getNombreLockPlaza(int i);
	void facturar(int segundos);
	void incrementarFacturacion(int cantidadFacturada);
	void sumarUnAuto();
	void restarUnAuto();
	void eliminarLocks();
	void imprimirError(int error);
	void imprimirErrorLock();
	Lock* tomarLockPlaza(int nroDePlaza);
	void liberarLockPlaza(int nroDePlaza, Lock* lockPlaza);
	void logOcupePlaza(int nroPlaza, int idAuto);
};



#endif /* ESTACIONAMIENTO_H_ */
