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

	AdministracionCliente* administracionCliente;

	long id;
	int tiempo;
	int numeroPlaza;
	int estacionamiento;

public:
	Auto(AdministracionCliente* administracionCliente, int estacionamiento);
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

    int getEstacionamiento();

};

#endif /* AUTO_H_ */
