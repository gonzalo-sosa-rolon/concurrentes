#include "Proceso.h"
#include <iostream>
Proceso::Proceso() {
	// se registra el event handler declarado antes
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);
}

Proceso::~Proceso() {

}

sig_atomic_t Proceso::terminarProceso() {
	return this->sigint_handler.getGracefulQuit();
}
