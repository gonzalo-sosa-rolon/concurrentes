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
	static const char* PATH_TOKEN_COLAS;
private:
	Cola<Mensaje> colaEntrada;
	Cola<Mensaje> colaSalida;

public:
	AdministracionCliente();
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
