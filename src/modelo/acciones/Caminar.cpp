/*
 * Caminar.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../../modelo/acciones/Caminar.h"
#include <iostream>

using namespace std;

const float ancho_paso = 2;

Caminar::Caminar() {
	estado = false;
	//Orientacion true = orientacion derecha
	direccion = true;
}

void Caminar::setEstado(bool nuevoEstado,bool nuevaDireccion){
	direccion = nuevaDireccion;
	estado = nuevoEstado;
}

bool Caminar::getEstado(){
	return estado;
}

Posicion Caminar::realizarAccion(Posicion pos){
	Posicion p = Posicion(ancho_paso, 0);
	if (direccion){
		estado = false;
		return pos + p;
	}
	estado = false;
	return pos - p;
}

Caminar::~Caminar() {
}

