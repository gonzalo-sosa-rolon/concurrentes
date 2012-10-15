#include "Log.h"

Log* Log::instancia = NULL;
Lock* Log::lock = NULL;
fstream* Log::archivo = NULL;

Log* Log::getLog() {

	if (!instancia) {
		instancia = new Log();
		lock = new Lock((char*) ARCHIVO_LOG);
		archivo = new fstream();
		archivo->open(ARCHIVO_LOG, fstream::out | fstream::app);
	}

	return instancia;
}

string Log::getTimeStamp(){
        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];

        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        strftime (buffer,80,"[%d/%m/%y %H:%M:%S] ",timeinfo);
        std::string mensaje = buffer;

        return mensaje;
}

void Log::logMensaje(const string mensaje) {

	this->lock->tomarLock();

	if (LOG_CONSOLA) {
		cout << getTimeStamp() << "INFO: " << mensaje << endl;
		cout.flush();
	}

	if (LOG_ARCHIVO) {

		*this->archivo << getTimeStamp() << "INFO: " << mensaje << "\n";
		this->archivo->flush();
	}

	this->lock->liberarLock();
}

void Log::logError(const string& error) {

	this->lock->tomarLock();
	if (LOG_CONSOLA) {
		cerr << getTimeStamp() << "ERROR: " << error << endl;
		cerr.flush();
	}

	if (LOG_ARCHIVO) {
		*this->archivo << getTimeStamp() << "ERROR: " << error << "\n";
		this->archivo->flush();
	}

	this->lock->liberarLock();
}

Log::Log() {

}

Log::~Log() {

	if (instancia) {
		delete lock;
		delete instancia;
		archivo->close();
	}
	instancia = NULL;
}
