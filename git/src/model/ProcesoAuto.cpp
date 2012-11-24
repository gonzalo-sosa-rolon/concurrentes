/*
 * ProcesoAuto.cpp
 *
 *  Created on: Nov 24, 2012
 *      Author: gsosarolon
 */

#include "ProcesoAuto.h"

ProcesoAuto::ProcesoAuto(Estacionamiento *estacionamiento) {
	this->autoDelProceso = new Auto(estacionamiento);
	this->estacionamiento = estacionamiento;
}

ProcesoAuto::~ProcesoAuto() {

}

void ProcesoAuto::ejecutar() {

}
