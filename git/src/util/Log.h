#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include "Lock.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Log {
private:
	static Log* instancia;
	static Lock* lock;
	static fstream* archivo;
	static const bool LOG_CONSOLA = false;
	static const bool LOG_ARCHIVO = true;

public:

	static const char* LOG_FILE_NAME;

	static Log* getLog();
	void logMensaje(const string mensaje);
	void logError(const string& error);

	~Log();
private:
	Log();
	string getTimeStamp();
};

#endif /* LOG_H_ */
