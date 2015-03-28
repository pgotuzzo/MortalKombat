/*
 * Orientacion.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../modelo/Orientacion.h"

const bool orientacion_default = true;

Orientacion::Orientacion() {
	derecha = orientacion_default;
}

// Derecha = True
// Izquierda = False
bool Orientacion::getOrientacion(){
	return derecha;
}

Orientacion::~Orientacion() {
	// TODO Auto-generated destructor stub
}

