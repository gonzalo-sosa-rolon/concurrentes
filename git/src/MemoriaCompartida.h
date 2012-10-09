/*
 * MemoriaCompartida.h
 *
 *  Created on: 09/10/2012
 *      Author: miriamquintero
 */

#ifndef MEMORIACOMPARTIDA_H_
#define MEMORIACOMPARTIDA_H_


#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string>

#define ERROR_SHMGET 1
#define ERROR_SHMAT 2
#define ERROR_SHMCTL 3
#define ERROR_SHMDT 4


template <typename T>
class MemoriaCompartida {

	private:
		int id;
		key_t clave;
		int size;
		int flags;
		T* dato;

	public:

		MemoriaCompartida(key_t clave=0,int size=0,int flags=0){
			this->clave = clave;
			this->size = size;
			this->flags = flags;
		};

		void setClave(key_t clave) {
			this->clave = clave;
		}

		void setSize(int size){
			this->size = size;
		}

		void setFlags(int flags){
			this->flags = flags;
		}

		void inicializar(key_t clave,int size,int flags) {
			this->clave = clave;
			this->flags = flags;
			this->size = size;
		}

		int reservarMemoria() {
			if ((this->id = shmget(this->clave, this->size, this->flags)) == -1)
				return ERROR_SHMGET;

			if ((this->dato = (T*)shmat(this->id, NULL, 0)) == (T *) -1)
				return ERROR_SHMAT;
			return 0;
		}

		int liberarRecursos(){
			if(shmctl(this->id, IPC_RMID ,NULL)==-1)
				return ERROR_SHMCTL;
			if(shmdt((T*) this->dato)== -1)
				return ERROR_SHMDT;
			return 0;
		}

		T& operator*() {
			return *(this->dato);
		}

		T* operator->() {
			return this->dato;
		}

		operator void*() {
			return (void*)dato;
		}

		operator T*() {
			return (T*)dato;
		}
};

#endif /* MEMORIACOMPARTIDA_H_ */
