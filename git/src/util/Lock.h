#ifndef LOCK_H_
#define LOCK_H_

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

class Lock {

private:

	struct flock fl;
	int fd;
	char nombre[255];

public:

	Lock(char* nombre);
	virtual ~Lock();

	int tomarLock();
	int liberarLock();
	int escribir(char* buffer, int buffsize);
};

#endif /* LOCK_H_ */
