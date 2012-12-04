#include "ProcesoSimulacion.h"

ProcesoSimulacion::ProcesoSimulacion(int tiempoEjecucion, AdministracionCliente* administracionCliente,
		std::vector<pid_t> &ids, pid_t pidAdminServidor) : idsAFinalizar(ids) {

	this->tiempoEjecucion = tiempoEjecucion;
	this->administracionCliente = administracionCliente;
	this->pidAdminServidor = pidAdminServidor;

}

ProcesoSimulacion::~ProcesoSimulacion() {

}

void ProcesoSimulacion::ejecutar() {
	stringstream info;

	cout << "Comienzo de la ejecucion por " << tiempoEjecucion << " segundos (Pid ProcesoSimulacion=" << getpid() << ")" << endl;
	sleep(tiempoEjecucion);

	info << "Finalizando Ejecucion, enviando seniales a procesos";
	Log::getLog()->logMensaje(info.str());
	info.str("");

	for (unsigned int i = 0; i < this->idsAFinalizar.size(); i++) {
		kill(idsAFinalizar[i], SIGINT);
	}

	for (unsigned int i = 0; i < this->idsAFinalizar.size(); i++) {
		wait(0); //TODO ver que onda un wait sin pid
	}
	kill(pidAdminServidor, SIGINT);

	cout << "Finalizacion de la ejecucion" << endl;
}
