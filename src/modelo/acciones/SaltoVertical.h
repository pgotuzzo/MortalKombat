/*
 * SaltoVertical.h
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#ifndef SALTOVERTICAL_H_
#define SALTOVERTICAL_H_

#include "../../modelo/Accion.h"

class SaltoVertical{
private:
	bool subiendo;
public:
	float ini_pos_x;
	float ini_pos_y;
	bool activado;

	SaltoVertical();
	bool darUnSalto(float pos_x,float pos_y);
	float get_posicion(float actual_pos_y);
	virtual ~SaltoVertical();
};

#endif /* SALTOVERTICAL_H_ */
