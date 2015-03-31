/*
 * SaltoOblicuo.h
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#ifndef SALTOOBLICUO_H_
#define SALTOOBLICUO_H_

#include "../../modelo/Accion.h"

class SaltoOblicuo : public Accion{
public:
	bool estado;
	bool orientacion;
	SaltoOblicuo();

	void setEstado(bool nuevoEstado, bool nuevaOrtientacion);
	Posicion realizarAccion(Posicion pos,Direccion dir);
	bool getEstado();
	virtual ~SaltoOblicuo();
};

#endif /* SALTOOBLICUO_H_ */
