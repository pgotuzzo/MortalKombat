/*
 * SaltoVertical.cpp
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#include "../../modelo/acciones/SaltoVertical.h"

const float altura_salto = 50;
const float intervalo_salto = 5;


SaltoVertical::SaltoVertical() {
	estado = false;
	subiendo = true;
}
bool SaltoVertical::getEstado() {
	return estado;
}

void SaltoVertical::setEstado(bool nuevoEstado, Posicion nuevaPosicion) {

	estado = nuevoEstado;
	subiendo = nuevoEstado;
	posIni = nuevaPosicion;

}



Posicion SaltoVertical::realizarAccion(Posicion posActual){
	float yActual = posActual.getY();
	float yIni = posIni.getY();
	if (estado){
		if ( (yActual > yIni - altura_salto ) && (subiendo)){
			return Posicion(posActual.getX(),yActual - intervalo_salto);
		}
		else{
			subiendo = false;
			if (yActual < yIni){
				return Posicion(posActual.getX(),yActual + intervalo_salto);
			}
		}
	}
	estado = false;
	return Posicion(posActual.getX(),yActual);
}

SaltoVertical::~SaltoVertical() {
}


