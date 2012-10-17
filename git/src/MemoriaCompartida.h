#ifndef MEMORIACOMPARTIDA_H_
#define MEMORIACOMPARTIDA_H_

#define SHM_OK 			 0
#define ERROR_FTOK 		-1
#define ERROR_SHMGET 	-2
#define	 ERROR_SHMAT 	-3

#include	<sys/types.h>
#include	<sys/ipc.h>
#include	<sys/shm.h>
#include <iostream>

using namespace std;

template<class T> class MemoriaCompartida {

private:

	int shmId;
	T* ptrDatos;

	int cantidadProcesosAdosados();

public:

	MemoriaCompartida();
	~MemoriaCompartida();
	int crear(const char *archivo, char letra, int cant_registros);
	void liberar();
	void escribir(int pos, T dato);
	T leer(int pos);
	void imprimirError(int error);
};

template<class T> MemoriaCompartida<T>::MemoriaCompartida() {
	this->shmId = 0;
	this->ptrDatos = NULL;
}

template<class T> MemoriaCompartida<T>::~MemoriaCompartida() {
}

template<class T> int MemoriaCompartida<T>::crear(const char *archivo, char letra, int cant_registros) {

	// generacion de la clave
	key_t clave = ftok(archivo, letra);
	if (clave == -1) {
		return ERROR_FTOK;
	} else {
		// creacion de la memoria compartida
		this->shmId = shmget(clave, sizeof(T) * cant_registros, 0644 | IPC_CREAT);

		if (this->shmId == -1)
			return ERROR_SHMGET;
		else {
			// attach del bloque de memoria al espacio de direcciones del proceso
			void* ptrTemporal = shmat(this->shmId, NULL, 0);

			if (ptrTemporal == (void *) -1) {
				return ERROR_SHMAT;
			} else {
				this->ptrDatos = (T *) ptrTemporal;
				return SHM_OK;
			}
		}
	}
}

template<class T> void MemoriaCompartida<T>::liberar() {
	// detach del bloque de memoria
	shmdt((void *) this->ptrDatos);

	int procAdosados = this->cantidadProcesosAdosados();

	if (procAdosados == 0) {
		shmctl(this->shmId, IPC_RMID, NULL);
	}
}

template<class T> void MemoriaCompartida<T>::escribir(int pos, T dato) {
	*(this->ptrDatos + pos) = dato;
}

template<class T> T MemoriaCompartida<T>::leer(int pos) {
	return (*(this->ptrDatos + pos));
}

template<class T> int MemoriaCompartida<T>::cantidadProcesosAdosados() {
	shmid_ds estado;
	shmctl(this->shmId, IPC_STAT, &estado);
	return estado.shm_nattch;
}

#endif /* MEMORIACOMPARTIDA_H_ */
