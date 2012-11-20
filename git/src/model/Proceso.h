#ifndef PROCESO_H_
#define PROCESO_H_


#include "../signals/EventHandler.h"
#include "../signals/SignalHandler.h"
#include "../signals/SIGINT_Handler.h"

class Proceso {
public:
	Proceso();
	virtual ~Proceso();
	virtual void ejecutar() = 0;

protected:
	virtual sig_atomic_t terminarProceso();

private:
	SIGINT_Handler sigint_handler;

};

#endif /* PROCESO_H_ */
