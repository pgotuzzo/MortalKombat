/*
 * Caminar.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../../modelo/acciones/Caminar.h"

const float ancho_paso = 2;

Caminar::Caminar() {
	estado = false;
	//Orientacion true = orientacion derecha
	orientacion = true;
}

void Caminar::setEstado(bool nuevoEstado,bool nuevaOrtientacion){
	orientacion = nuevaOrtientacion;
	estado = nuevoEstado;
}

Posicion Caminar::realizarAccion(Posicion pos, Direccion dir){
	Posicion p = Posicion(ancho_paso, 0);
	if (dir.getDireccion()){
		estado = false;
		return pos + p;
	}
	estado = false;
	return pos - p;
}

Caminar::~Caminar() {
}

