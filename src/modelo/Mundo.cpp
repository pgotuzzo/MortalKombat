/*
 * Mundo.cpp
 *
 *  Created on: 3/4/2015
 *      Author: miguel
 */

#include "Mundo.h"

const float Default_ancho_ventana = 200;
const float Default_alto_ventana = 150;
const float Default_alto_piso = 20;
const float Default_Altura_PJ = 35;
const float Default_Ancho_PJ = 20;


const float Default_pos_Y = Default_alto_ventana - Default_alto_piso - Default_Altura_PJ;
const float Default_pos_X = Default_ancho_ventana/2;


Mundo::Mundo() {
	personaje1 = new Personaje(Posicion(Default_pos_X,Default_pos_Y),Default_Altura_PJ,Default_Ancho_PJ, Default_alto_ventana);
	ancho_ventana = Default_ancho_ventana;
	alto_ventana = Default_alto_ventana;
	alto_piso = Default_alto_piso;
}

Personaje* Mundo::getPersonaje(){
	return personaje1;
}

Mundo::~Mundo() {
	// TODO Auto-generated destructor stub
}

