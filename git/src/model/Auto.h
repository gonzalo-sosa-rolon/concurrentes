#ifndef AUTO_H_
#define AUTO_H_

#include "Estacionamiento.h"

class AdministracionCliente;

class Auto {
private:
	static const int TIEMPO_ENTRAR;
	static const int TIEMPO_SALIR;
	static const int TIEMPO_LLEGAR_PLAZA;
	static const int TIEMPO_LLEGAR_SALIDA;
	static const int TIEMPO_APARCAR;

	Estacionamiento* estacionamiento;
	AdministracionCliente* administracionCliente;
	long id;
	int tiempo;
	int numeroPlaza;
	int estacionamientoS; //TODO rename

public:
	Auto(Estacionamiento* estacionamiento, AdministracionCliente* administracionCliente, int estacionamientoS = 0);
	virtual ~Auto();

    bool solicitarLugar();

    bool ocuparPlaza();
    long desocuparPlaza();

    int tomarEntrada();
    int liberarEntrada();
    int tomarSalida();
    int liberarSalida();

    void setId(long id);
    long getId();
    int getTiempo();

    void setNumeroPlaza(int numeroPlaza);
    int getNumeroPlaza();

    void entrar();
    void salir();
    void aparcar();

};

#endif /* AUTO_H_ */
