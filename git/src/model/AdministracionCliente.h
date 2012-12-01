/*
 * AdministracionCliente.h
 *
 *  Created on: Dec 1, 2012
 *      Author: gsosarolon
 */

#ifndef ADMINISTRACIONCLIENTE_H_
#define ADMINISTRACIONCLIENTE_H_

class Auto;

class AdministracionCliente {
public:
	AdministracionCliente();
	virtual ~AdministracionCliente();

	bool solicitarLugar(int estacionamiento);
	bool tomarEntrada(int estacionamiento);
	bool liberarEntrada(int estacionamiento);
	bool ocuparPlaza(int estacionamiento);
	bool tomarSalida(int estacionamiento);
	bool liberarSalida(int estacionamiento);
	bool salir(Auto* automovil);
};

#endif /* ADMINISTRACIONCLIENTE_H_ */
