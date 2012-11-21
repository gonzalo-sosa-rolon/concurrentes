/*
 * Semaforo.h
 *
 *  Created on: 21/11/2012
 *      Author: maxi
 */

#ifndef SEMAFORO_H_
#define SEMAFORO_H_

# include <sys/ipc.h>
# include <sys/sem.h>
# include <sys/types.h>

class Semaforo {
public:
	Semaforo(char * nombre, int valorInicial);
	virtual ~Semaforo();
	int p();
	int v();
	void eliminar();

private:
	int id;
	int valorInicial;
	int inicializar();
};

#endif /* SEMAFORO_H_ */
