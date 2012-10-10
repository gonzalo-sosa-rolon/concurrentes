#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

class Mutex {
public:
	Mutex();
	virtual ~Mutex();

	int lock();
	int unlock();

	pthread_mutex_t& getMutex();
private:
	 pthread_mutex_t mutex;
};

#endif /* MUTEX_H_ */
