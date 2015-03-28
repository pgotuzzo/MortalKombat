/*
 * Caminar.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../../modelo/acciones/Caminar.h"

const float ancho_paso = 2;

Caminar::Caminar() {
	// TODO Auto-generated constructor stub

}

Posicion Caminar::dar_un_paso(Posicion pos, Direccion dir){
	if (dir.get_Direccion() == true) return pos + ancho_paso;
	return pos - ancho_paso;
}

Caminar::~Caminar() {
	// TODO Auto-generated destructor stub
}

