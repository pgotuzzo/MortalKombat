/*
 * Accion.h
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#ifndef ACCION_H_
#define ACCION_H_

#include "../modelo/Posicion.h"

class Accion{
public:
	bool accion_activada;
	Posicion pos_inicial;

	Accion();
	bool puedoAccionar();
	Posicion accionar(Posicion pos_ini);

	virtual ~Accion();
};

#endif /* ACCION_H_ */
