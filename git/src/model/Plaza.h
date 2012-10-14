#ifndef PLAZA_H_
#define PLAZA_H_

#include "time.h"
#include "../util/Lock.h"

class Plaza {
private:
	int id;
	int horaIngreso;
	int tiempoEstadia;
	bool ocupado;

public:
	Plaza();
	Plaza(int id);

	int getHoraIngreso();
	int getId();

	int getTiempoEstadia();
	bool getOcupado();
	void setHoraIngreso(int horaIngreso);
	void setId(int id);
	void setOcupado(bool ocupado);
	void ocupar(int tiempoStadia, int horaDeIngreso);
	bool deseaIrse();
	void incializar();

};

#endif /* PLAZA_H_ */
