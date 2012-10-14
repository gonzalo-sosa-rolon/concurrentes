#include "Log.h"

Log* Log::instancia = NULL;
Lock* Log::lock = NULL;

Log* Log::getLog() {

	if (!instancia) {
		instancia = new Log();
		lock = new Lock((char*)ARCHIVO_LOG);
	}

	return instancia;
}

void Log::logMensaje(const string mensaje) {

	this->lock->tomarLock();
	cout << "Info: " << mensaje << endl;
	cout.flush();
	this->lock->liberarLock();
}

void Log::logError(const string& error) {

	this->lock->tomarLock();
	cerr << "Error: " << error << endl;
	cerr.flush();
	this->lock->liberarLock();
}

Log::Log() {

}

Log::~Log() {

	if (instancia) {
		delete lock;
		delete instancia;
	}
	instancia = NULL;
}
