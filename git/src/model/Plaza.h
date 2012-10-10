/*
 * Plaza.h
 *
 *  Created on: 09/10/2012
 *      Author: miriamquintero
 */

#ifndef PLAZA_H_
#define PLAZA_H_

#include "../util/Mutex.h"

class Plaza {
private:
	int id;
	int horaIngreso;
	bool ocupado;
	Mutex llaveOcupado;

public:

	Plaza() {
		this->id = 0;
		this->ocupado = false;
	}

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

	bool getOcupado() {

		bool resultado;

		llaveOcupado.lock();
		resultado = ocupado;
		llaveOcupado.unlock();

		return resultado;
	}

	void setHoraIngreso(int horaIngreso) {
		this->horaIngreso = horaIngreso;
	}

	void setId(int id) {
		this->id = id;
	}

	void setOcupado(bool ocupado) {

		llaveOcupado.lock();
		this->ocupado = ocupado;
		llaveOcupado.unlock();
	}

	/**
	 * Devuelve True si pudo ocupar la plaza
	 */
	bool ocupar() {

		bool resultado = false;

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
