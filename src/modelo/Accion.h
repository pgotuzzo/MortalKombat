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

	virtual bool getEstado();

	virtual void setEstado(bool nuevoEstado);

	virtual void setEstado(bool nuevoEstado, bool orientacion);

	virtual ~Accion();
};

#endif /* ACCION_H_ */
