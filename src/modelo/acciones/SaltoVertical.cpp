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
	activado = false;
	subiendo = true;
}

bool SaltoVertical::darUnSalto(Posicion pos){
	if (activado == true ) return false; //No puede saltar mientras esta saltando
	pos_ini = pos;
	//ini_pos_x = pos_x;
	//ini_pos_y = pos_y;
	activado = true;
	subiendo = true;
	return activado;
}

Posicion SaltoVertical::get_posicion(Posicion pos_actual){
	float y_actual = pos_actual.get_y();
	float y_ini = pos_ini.get_y();
	if ( activado == true ){
		if ( (y_actual > y_ini - altura_salto ) && (subiendo == true)){
			return Posicion(pos_actual.get_x(),y_actual - intervalo_salto);
		}
		else{
			subiendo = false;
			if (y_actual < y_ini){
				return Posicion(pos_actual.get_x(),y_actual + intervalo_salto);
			}

		}
	}
	activado = false;
	return Posicion(pos_actual.get_x(),y_actual);
}

SaltoVertical::~SaltoVertical() {
	// TODO Auto-generated destructor stub
}

