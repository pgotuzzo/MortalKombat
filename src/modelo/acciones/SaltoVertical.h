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
private:
	bool subiendo;
public:
	Posicion pos_ini;
	bool activado;

	SaltoVertical();
	bool darUnSalto(Posicion pos);
	Posicion get_posicion(Posicion pos_actual);
	virtual ~SaltoVertical();
};

#endif /* SALTOVERTICAL_H_ */
