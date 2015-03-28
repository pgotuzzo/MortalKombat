/*
 * Avanzar.cpp
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#include "../../modelo/acciones/Avanzar.h"

const float ancho_avance = 10;

Avanzar::Avanzar() {
	// TODO Auto-generated constructor stub

}

float Avanzar::darunPaso(float pos_x,float pos_y){
	return ancho_avance + pos_x;
}

Avanzar::~Avanzar() {
	// TODO Auto-generated destructor stub
}

