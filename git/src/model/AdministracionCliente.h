#ifndef ADMINISTRACIONCLIENTE_H_
#define ADMINISTRACIONCLIENTE_H_

#include "../util/Cola.h"
#include "Estacionamiento.h"
#include "Mensaje.h"
#include <vector>

class Auto;
using namespace std;

class AdministracionCliente {
public:
	static const char* PATH_TOKEN_MEMORIA_COMPARTIDA;

private:
	vector<Cola<Mensaje::Mensaje>* > colasEntrada;
	vector<Cola<Mensaje::Mensaje>* > colasSalida;
	Cola<Mensaje::Mensaje> colaServidor;
	vector<Estacionamiento*> estacionamientos;

	int tamanio;
	int cantidadEntradas;
	int cantidadSalidas;
	int cantidadEstacionamientos;
public:
	AdministracionCliente(int cantidadEstacionamientos, int tamanio, int precio, int cantidadEntradas = 3, int cantidadSalidas = 2);
	virtual ~AdministracionCliente();

	bool solicitarLugar(Auto* automovil);
	bool solicitarEntrada(Auto* automovil);
	bool liberarEntrada(Auto* automovil);
	bool ocuparPlaza(Auto* automovil);
	bool descocuparLugar(Auto* automovil);
	bool solicitarSalida(Auto* automovil);
	bool liberarSalida(Auto* automovil);
	bool salir(Auto* automovil);

private:
	Mensaje::Mensaje prepararMensajeServidor(int estacionamiento);
};

#endif /* ADMINISTRACIONCLIENTE_H_ */
