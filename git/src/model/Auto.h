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
    void aparcar();
    void dirigirseAPlaza();
    void dirigirseASalida();
};

#endif /* AUTO_H_ */
