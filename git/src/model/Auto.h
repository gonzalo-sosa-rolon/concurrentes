#ifndef AUTO_H_
#define AUTO_H_

#include "Estacionamiento.h"

class Auto {
private:
	Estacionamiento* estacionamiento;
public:
	Auto(Estacionamiento* estacionamiento);
	virtual ~Auto();

    bool solicitarLugar();
	void entrar();
    bool solicitarPlaza();
    void dirigirseAPlaza();
    void aparcar();
    void dirigirseASalida();
    void salir();
};

#endif /* AUTO_H_ */
