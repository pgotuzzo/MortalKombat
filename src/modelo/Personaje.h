/*
 * Personaje.h
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <stdio.h>
#include <list>
#include <tr1/unordered_map>

#include "../modelo/Accion.h"
#include "../modelo/Estado.h"
#include "../modelo/Posicion.h"

using namespace std;

class Personaje {
public:
	Posicion pos;
	Estado estado;
	Posicion pos;


	Personaje();
	void p_saltar();
	Estado get_estado();
	Posicion get_Posicion();

	virtual ~Personaje();
};

#endif /* PERSONAJE_H_ */
