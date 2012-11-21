/*
 * Semaforo.cpp
 *
 *  Created on: 21/11/2012
 *      Author: maxi
 */

#include "Semaforo.h"

Semaforo::Semaforo(char * nombre, int valorInicial) {
	this->valorInicial = valorInicial;
	key_t clave = ftok(nombre, 'a');
	this->id = semget(clave, 1, 0666 | IPC_CREAT);
	this->inicializar();
}

Semaforo::~Semaforo() {
	// TODO Auto-generated destructor stub
}

int Semaforo::inicializar() {
	union semnum {
		int val;
		struct semid_ds * buf;
		ushort * array;
	};

	semnum init;
	init.val = this->valorInicial;
	int resultado = semctl(this->id, 0, SETVAL, init);
	return resultado;
}

int Semaforo::p() {
	struct sembuf operacion;
	operacion.sem_num = 0; // numero de s e m a f o r o
	operacion.sem_op = -1; // restar 1 al s e m a f o r o
	operacion.sem_flg = SEM_UNDO;
	int resultado = semop(this->id, &operacion, 1);
	return resultado;
}

int Semaforo::v() {
	struct sembuf operacion;
	operacion.sem_num = 0; // numero de s e m a f o r o
	operacion.sem_op = 1; // sumar 1 al s e m a f o r o
	operacion.sem_flg = SEM_UNDO;
	int resultado = semop(this->id, &operacion, 1);
	return resultado;
}

void Semaforo::eliminar() {
	semctl(this->id, 0, IPC_RMID);
}
