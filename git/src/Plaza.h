/*
 * Plaza.h
 *
 *  Created on: 09/10/2012
 *      Author: miriamquintero
 */

#ifndef PLAZA_H_
#define PLAZA_H_

#include "util/Mutex.h"

class Plaza {
private:
	int id;
	int horaIngreso;
	boolean ocupado;
	Mutex llaveOcupado;

public:

	Plaza(int id) {
		this->id = id;
		this->ocupado = false;
		//TODO ver tema horaIngreso
	}

	int getHoraIngreso() const {
		return horaIngreso;
	}

	int getId() const {
		return id;
	}

	boolean getOcupado() const {

		boolean resultado;

		llaveOcupado.lock();
		resultado =  ocupado;
		llaveOcupado.unlock();

		return resultado;
	}

	void setHoraIngreso(int horaIngreso) {
		this->horaIngreso = horaIngreso;
	}

	void setId(int id) {
		this->id = id;
	}

	void setOcupado(boolean ocupado) {

		llaveOcupado.lock();
		this->ocupado = ocupado;
		llaveOcupado.unlock();
	}

	/**
	 * Devuelve True si pudo ocupar la plaza
	 */
	boolean ocupar() {

		boolean resultado = false;

		llaveOcupado.lock();

		if (!this->ocupado) {
			this->ocupado = true;
			resultado = true;
		}

		llaveOcupado.unlock();

		return resultado;
	}
};

#endif /* PLAZA_H_ */
