/*
 * Personaje.h
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <stdio.h>
#include <iostream>
#include <list>
#include <tr1/unordered_map>

#include "../modelo/Accion.h"
#include "../modelo/Posicion.h"
#include "../modelo/Orientacion.h"
#include "../modelo/Direccion.h"

using namespace std;

class Personaje {
public:
	Posicion pos;
	Orientacion orientacion;
	Direccion dir;
	Accion accion;

	Personaje();
	bool puedoRealizarAccion(Accion accion);
	void realizarAccion(int orden);
	void p_saltar();
	Posicion get_Posicion();

	virtual ~Personaje();
};

#endif /* PERSONAJE_H_ */
