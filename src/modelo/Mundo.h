/*
 * Mundo.h
 *
 *  Created on: 3/4/2015
 *      Author: miguel
 */

#ifndef SRC_MODELO_MUNDO_H_
#define SRC_MODELO_MUNDO_H_

#include "../modelo/Personaje.h"

class Mundo {
public:
	float ancho_ventana;
	float alto_ventana;
	float alto_piso;
	Personaje* personaje1;

	Mundo();
	Personaje* getPersonaje();
	virtual ~Mundo();
};

#endif /* SRC_MODELO_MUNDO_H_ */
