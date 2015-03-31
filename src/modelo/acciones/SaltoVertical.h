/*
 * SaltoVertical.h
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#ifndef SALTOVERTICAL_H_
#define SALTOVERTICAL_H_

#include "../../modelo/Accion.h"
#include "../../modelo/Posicion.h"

class SaltoVertical : public Accion{
public:
	Posicion posIni;
	bool estado;
	bool subiendo;


	SaltoVertical();
	bool getEstado();
	void setEstado(bool nuevoEstado, Posicion nuevaPosicion);

	Posicion realizarAccion(Posicion pos_actual);
	virtual ~SaltoVertical();
};

#endif /* SALTOVERTICAL_H_ */
