/*
 * Mundo.cpp
 *
 *  Created on: 3/4/2015
 *      Author: miguel
 */

#include "Mundo.h"

const float Default_ancho_escenario = 1000;
const float Default_alto_escenario = 150;
const float Default_alto_piso = 20;
const float Default_Altura_PJ = 35;
const float Default_Ancho_PJ = 20;


const float Default_pos_Y = Default_alto_escenario - Default_alto_piso - Default_Altura_PJ;
const float Default_pos_X = Default_ancho_escenario/2;


Mundo::Mundo() {
	personaje1 = new Personaje(Posicion(Default_pos_X,Default_pos_Y),Default_Altura_PJ,Default_Ancho_PJ, Default_alto_escenario);
	ancho_ventana = Default_ancho_escenario;
	alto_ventana = Default_alto_escenario;
	alto_piso = Default_alto_piso;
}

Personaje* Mundo::getPersonaje(){
	return personaje1;
}

Posicion Mundo::actualizarMundo(int orden){
	personaje1->realizarAccion(orden,Default_ancho_escenario);
	return personaje1->getPosicion();
}

Mundo::~Mundo() {
	// TODO Auto-generated destructor stub
}

