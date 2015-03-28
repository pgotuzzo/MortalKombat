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
	//if (p == null){
		pos = Posicion(Default_pos_X,Default_pos_Y);

	/*}else {
	 * Valores pasados por el parser
	 * }*/


}

Posicion Personaje::get_Posicion(){
	return pos;
}


Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

