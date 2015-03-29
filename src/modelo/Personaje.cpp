/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#include "../modelo/Personaje.h"

#include <stdio.h>
#include <stdlib.h>
const float Default_pos_Y = 50.0;
const float Default_pos_X = 50.0;
const int Default_index_Z = 3;


Personaje::Personaje() {
	pos = Posicion(Default_pos_X,Default_pos_Y);
}

void Personaje::realizarAccion(int orden){

	switch (orden){
		case (1):
				//Salto vertical
				break;
		case (2):
				//Agacharse
				break;
		case (3):
				//Caminar a la derecha
				break;
		case (4):
				//Caminar a la izquierda
				break;
		case (5):
				//Salto oblicuo a la derecha
				break;
		case (6):
				//Salto oblicuo a la izquierda
				break;

		default:
			break;

	}





}




Posicion Personaje::get_Posicion(){
	return pos;
}




Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

