/*
 * main.cpp
 *
 *  Created on: 09/10/2012
 *      Author: miriamquintero
 */

#include <iostream>
#include <stdlib.h>
#include "../src/MemoriaCompartida.h"


using namespace std;

struct Pepe {
	int dia;
	int id;
};

struct Lugar {
	char ocupado;
	int id;
	int horaIngreso;
};

int main2(int argc, char **argv) {

	/*
	 * Prueba con template de memoria que recibe entero
	 */

	cout<<"Prueba 1: template recibe entero"<<endl;
	cout<<"--------------------------------"<<endl<<endl;
	MemoriaCompartida<int> memoria;
	memoria.inicializar(ftok("testMemoria.cpp",'4'),4,IPC_CREAT | 0666);
	int state = memoria.reservarMemoria();
	cout<<"state init: "<<state<<endl;
	(*memoria) = 2;
	cout<<(*memoria)<<endl;
	int statefinal= memoria.liberarRecursos();
	cout<<"Final state: "<<statefinal<<endl<<endl;

//	/*
//	 * Prueba con una estructura y 2 procesos hijos que manipulan la memoria
//	 */
//	MemoriaCompartida<Pepe> mipepe;
//	cout<<"Prueba 2: una estructura y 2 procesos hijos "<<endl;
//	cout<<"--------------------------------------------"<<endl<<endl;
//	mipepe.inicializar(ftok("testMemoria.cpp",'a'),sizeof(Pepe), IPC_CREAT | 0666);
//	state = mipepe.reservarMemoria();
//	mipepe->dia = 1;
//	mipepe->id = 11;
//	cout<<mipepe->dia <<" "<<mipepe->id<<endl;
//
//
//	pid_t unHijoPid = fork();
//	if (unHijoPid == 0) {
//		mipepe->dia = 2;
//		mipepe->id = 2345;
//		cout<<"soy un hijo. Modifique pepe: "<<mipepe->dia<<endl;
//		exit(0);
//	}
//	pid_t otroHijoPid = fork();
//	if (otroHijoPid==0) {
//		mipepe->dia = 5;
//		cout<<"soy otro hijo. Modifique pepe: "<<mipepe->dia<<endl;
//		cout<<"soy otro hijo y leo el id "<<mipepe->id<<endl;
//		exit(0);
//	}
//	wait();
//	statefinal=mipepe.liberarRecursos();
//	cout<< "state: " <<state<<" final state: "<<statefinal<<endl<<endl;


	/*
	 * Prueba con array de estructuras y 2 procesos hijos
	 */

	MemoriaCompartida<Lugar*> park;
	cout<<"Prueba 3: array de estructuras y 2 procesos hijos"<<endl;
	cout<<"-------------------------------------------------"<<endl<<endl;
	park.inicializar(ftok("testMemoria.cpp",'a'),sizeof(Lugar)*4, IPC_CREAT | 0666);
	state = park.reservarMemoria();
	Lugar* lug =(Lugar*)(void*)park;
	lug[1].id=1;
	lug[1].ocupado='0';
	cout<<"Inicializo lugares. Id: "<<lug[1].id<<" Ocupado: "<<lug[1].ocupado<<endl;

	pid_t unHijoPid1 = fork();
	if (unHijoPid1 == 0) {
		Lugar* place =(Lugar*)(void*)park;
		//Begin SC
		place[1].id = 55;
		place[1].ocupado='1';
		cout<<"Soy un hijo. Modifique id y ocupado de lugar. Id: "<<place[1].id<<" Ocupado: "<<place[1].ocupado<<endl;
		//END SC
		exit(0);
	}
	pid_t otroHijoPid1 = fork();
	if (otroHijoPid1==0) {
		Lugar* pl =(Lugar*)(void*)park;
		//aqui habria que poner una seccion critica porque es posible que
		//se ejecute la primera instruccion , se pase a otro proceso que cambie los valores, y luego ejecutar
		//la segunda instruccion. Eso es malo!
		//Begin SC
		pl[1].id=96;
		cout<<"Soy otro hijo. Modifique id pero no ocupado de lugar: Id: "<<pl[1].id<<" Ocupado: "<<pl[1].ocupado<<endl;
		cout<<"Soy otro hijo y leo lugar. Id: "<<pl[1].id<<" Ocupado: "<<pl[1].ocupado<<endl;
		//End SC
		exit(0);
	}
	wait();
	statefinal=park.liberarRecursos();
	cout<< "state: " <<state<<" final state: "<<statefinal<<endl<<endl;

	return 0;
}
