/*
 * Direccion.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../modelo/Direccion.h"


Direccion::Direccion() {
	// TODO Auto-generated constructor stub

}

// True = derecha
// False = izquierda
void Direccion::set_Direccion(bool dir){
	derecha = dir;
}

bool Direccion::get_Direccion(){
	return derecha;
}

Direccion::~Direccion() {
	// TODO Auto-generated destructor stub
}

