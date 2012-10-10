#include "Mutex.h"

Mutex::Mutex() {

	pthread_mutex_init(&mutex,NULL);
}

Mutex::~Mutex() {

	pthread_mutex_destroy(&mutex);
}

int Mutex::lock(){

	return pthread_mutex_lock(&mutex);
}

int Mutex::unlock(){

	return pthread_mutex_unlock(&mutex);
}

pthread_mutex_t& Mutex::getMutex(){

	return this->mutex;
}
