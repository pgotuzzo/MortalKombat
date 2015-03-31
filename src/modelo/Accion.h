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
	bool estado;

	Accion();

	bool getEstado();

	void setEstado(bool nuevoEstado);
	void setEstado(bool nuevoEstado, bool orientacion);
	void setEstado(bool nuevoEstado, Posicion nuevaPosicion);
	void setEstado(bool nuevoEstado, Posicion nuevaPosicion, bool orientacionSalto);

	Posicion realizarAccion(Posicion posActual);
	Posicion realizarAccion(Posicion pos,bool dir);

	virtual ~Accion();
};

#endif /* ACCION_H_ */
