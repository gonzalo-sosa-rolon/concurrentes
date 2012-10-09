/*
 * Evento.h
 *
 *  Created on: 09/10/2012
 *      Author: miriamquintero
 */

#ifndef EVENTO_H_
#define EVENTO_H_

#include <iostream>
#include "MemoriaCompartida.h"
#include "Plaza.h"

class Evento {

	public:
		Evento() {};
		virtual ~Evento(){};
		virtual void ejecutar()=0;
};

class EventoDeAuto : public Evento {
	protected:
		MemoriaCompartida<Plaza> estacionamiento;
		std::ostream& std_out;
	public:
		EventoDeAuto(const MemoriaCompartida<Plaza>& estacionamiento, std::ostream & out) : std_out(out) {
			this->estacionamiento = estacionamiento;
		}

		~EventoDeAuto(){
		}
};

class EventoLlegadaDeAuto : public EventoDeAuto{
	public:
		EventoLlegadaDeAuto(const MemoriaCompartida<Plaza>& estacionamiento , std::ostream& out) : EventoDeAuto(estacionamiento,out){
		}

		~EventoLLegadaDeAuto(){
		}

		void ejecutar(){
		}
};

//TODO EventoSalidaDeAuto

#endif /* EVENTO_H_ */
