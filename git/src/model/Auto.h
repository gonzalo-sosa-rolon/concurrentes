#ifndef AUTO_H_
#define AUTO_H_

#include "Estacionamiento.h"

class Auto {
private:
	static const int TIEMPO_ENTRAR;
	static const int TIEMPO_SALIR;
	static const int TIEMPO_LLEGAR_PLAZA;
	static const int TIEMPO_LLEGAR_SALIDA;
	Estacionamiento* estacionamiento;
	long id;
	int tiempo;
	int numeroPlaza;
public:
	Auto(Estacionamiento* estacionamiento);
	virtual ~Auto();

    bool solicitarLugar();
	void entrar();
    bool ocuparPlaza();
    bool liberarPlaza();
    void dirigirseAPlaza();
    void aparcar();
    void dirigirseASalida();
    void salir();

    void setId(long id);
    long getId();
    int getTiempo();

    void setNumeroPlaza(int numeroPlaza);
    int getNumeroPlaza();
};

#endif /* AUTO_H_ */
