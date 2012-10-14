#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include "Lock.h"
#include <string>

#define ARCHIVO_LOG "log.txt"

using namespace std;

class Log {
private:
	static Log* instancia;
	static Lock* lock;

public:
	static Log* getLog();
	void logMensaje(const string mensaje);
	void logError(const string& error);

	~Log();
private:
	Log();
};

#endif /* LOG_H_ */
