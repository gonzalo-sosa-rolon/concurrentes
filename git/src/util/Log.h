#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include "Lock.h"
#include <string>
#include <sstream>
#include <fstream>

#define ARCHIVO_LOG "log.txt"

#define LOG_CONSOLA true
#define LOG_ARCHIVO true

using namespace std;

class Log {
private:
	static Log* instancia;
	static Lock* lock;
	static fstream* archivo;

public:
	static Log* getLog();
	void logMensaje(const string mensaje);
	void logError(const string& error);

	~Log();
private:
	Log();
	string getTimeStamp();
};

#endif /* LOG_H_ */
