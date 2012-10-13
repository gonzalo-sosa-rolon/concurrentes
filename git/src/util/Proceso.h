#ifndef PROCESO_H_
#define PROCESO_H_

class Proceso {
public:
	Proceso();
	virtual ~Proceso();

	virtual void ejecutar() = 0;
};

#endif /* PROCESO_H_ */
