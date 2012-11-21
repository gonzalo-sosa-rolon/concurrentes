/*
 * Auto.h
 *
 *  Created on: 21/11/2012
 *      Author: maxi
 */

#ifndef AUTO_H_
#define AUTO_H_

#include "Proceso.h"

class Auto: public Proceso {
public:
	Auto();
	virtual ~Auto();
	virtual void ejecutar();

};

#endif /* AUTO_H_ */
