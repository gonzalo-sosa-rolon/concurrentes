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
	void procesarMensaje(Mensaje::Mensaje &mensaje);
	bool estacionamientosVacios();

	void procesarSolicitarLugar(Mensaje::Mensaje mensaje);
	void procesarLiberarPlaza(Mensaje::Mensaje mensaje);
	void procesarOcuparPlaza(Mensaje::Mensaje mensaje);
	void procesarSalir(Mensaje::Mensaje mensaje);
	void procesarEstacionamientosVacios(Mensaje::Mensaje mensaje);

	void consultaCantidadDeAutos(Mensaje::Mensaje mensaje);
	void consultaMontoFacturado(Mensaje::Mensaje mensaje);

};

#endif /* ADMINISTRACIONSERVIDOR_H_ */
