#include "Log.h"

Log* Log::instancia = NULL;
Lock* Log::lock = NULL;

Log* Log::getLog() {

	if (!instancia) {
		instancia = new Log();
		lock = new Lock((char*) ARCHIVO_LOG);
	}

	return instancia;
}

string Log::getTimeStamp(){
        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];

        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        strftime (buffer,80,"[%d/%m/%y %H:%M:%S]\t",timeinfo);
        std::string mensaje = buffer;

        return mensaje;
}

void Log::logMensaje(const string mensaje) {

	this->lock->tomarLock();

	if (LOG_CONSOLA) {
		cout << getTimeStamp() << " INFO: " << mensaje << endl;
		cout.flush();
	}
	this->lock->liberarLock();
}

void Log::logError(const string& error) {

	this->lock->tomarLock();
	if (LOG_CONSOLA) {
		cerr << getTimeStamp() << " ERROR: " << error << endl;
		cerr.flush();
	}
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
