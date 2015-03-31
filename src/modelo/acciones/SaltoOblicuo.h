/*
 * SaltoOblicuo.h
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#ifndef SALTOOBLICUO_H_
#define SALTOOBLICUO_H_

#include "../../modelo/Accion.h"
#include <math.h>


class SaltoOblicuo : public Accion{
public:
	bool estado;
	bool orientacion;
	float a;
	Posicion posInicial;
	Posicion posFinal;
	float coeficiente; // Segun este coeficiente sumara o restara x para avanzar y retroceder

	SaltoOblicuo();

	void setEstado(bool nuevoEstado, Posicion nuevaPosicion,bool direccionSalto);
	Posicion realizarAccion(Posicion pos);
	bool getEstado();
	virtual ~SaltoOblicuo();
};

#endif /* SALTOOBLICUO_H_ */
