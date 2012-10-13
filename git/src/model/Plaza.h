#ifndef PLAZA_H_
#define PLAZA_H_

#include "../util/Lock.h"

class Plaza {
private:
	int id;
	int horaIngreso;
	bool ocupado;

public:
	Plaza();
	Plaza(int id);

	int getHoraIngreso();
	int getId();
	bool getOcupado();
	void setHoraIngreso(int horaIngreso);
	void setId(int id);
	void setOcupado(bool ocupado);
	void ocupar();
};

#endif /* PLAZA_H_ */
