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

bool SaltoVertical::darUnSalto(float pos_x,float pos_y){
	if (activado == true ) return false; //No puede saltar mientras esta saltando
	ini_pos_x = pos_x;
	ini_pos_y = pos_y;
	activado = true;
	subiendo = true;
	return activado;
}

float SaltoVertical::get_posicion(float actual_pos_y){
	if ( activado == true ){
		if ( (actual_pos_y > ini_pos_y - altura_salto ) && (subiendo == true)){
			return actual_pos_y - intervalo_salto;
		}
		else{
			subiendo = false;
			if (actual_pos_y < ini_pos_y){
				return actual_pos_y + intervalo_salto;
			}

		}
	}
	activado = false;
	return actual_pos_y;
}

SaltoVertical::~SaltoVertical() {
	// TODO Auto-generated destructor stub
}

