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

bool SaltoVertical::darUnSalto(Posicion pos){
	if (estado) return false; //No puede saltar mientras esta saltando
	pos_ini = pos;
	//ini_pos_x = pos_x;
	//ini_pos_y = pos_y;
	estado = true;
	subiendo = true;
	return estado;
}

Posicion SaltoVertical::get_posicion(Posicion pos_actual){
	float y_actual = pos_actual.getY();
	float y_ini = pos_ini.getY();
	if (estado){
		if ( (y_actual > y_ini - altura_salto ) && (subiendo)){
			return Posicion(pos_actual.getX(),y_actual - intervalo_salto);
		}
		else{
			subiendo = false;
			if (y_actual < y_ini){
				return Posicion(pos_actual.getX(),y_actual + intervalo_salto);
			}

		}
	}
	estado = false;
	return Posicion(pos_actual.getX(),y_actual);
}

SaltoVertical::~SaltoVertical() {
	// TODO Auto-generated destructor stub
}

bool SaltoVertical::getEstado() {
	return estado;
}
