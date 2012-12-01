#ifndef ADMINISTRACIONCLIENTE_H_
#define ADMINISTRACIONCLIENTE_H_

#include "../util/Cola.h"
#include "Mensaje.h"
#include <vector>

class Auto;
using namespace std;

class AdministracionCliente {
public:
	static const char* PATH_TOKEN_MEMORIA_COMPARTIDA;

private:
	vector<Cola<Mensaje::Mensaje>* > colaEntrada;
	vector<Cola<Mensaje::Mensaje>* > colaSalida;
	int tamanio;
	int cantidadEntradas;
	int cantidadSalidas;
public:
	AdministracionCliente(int tamanio = 1, int cantidadEntradas = 3, int cantidadSalidas = 2);
	virtual ~AdministracionCliente();

	bool solicitarLugar(int estacionamiento);
	bool solicitarEntrada(int estacionamiento);
	bool liberarEntrada(int estacionamiento);
	bool ocuparPlaza(int estacionamiento);
	bool solicitarSalida(int estacionamiento);
	bool liberarSalida(int estacionamiento);
	bool salir(Auto* automovil);
};

#endif /* ADMINISTRACIONCLIENTE_H_ */
