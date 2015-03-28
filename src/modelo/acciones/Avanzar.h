/*
 * Avanzar.h
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#ifndef AVANZAR_H_
#define AVANZAR_H_

#include "../../modelo/Accion.h"

class Avanzar : public Accion{
public:
	float ini_pos_x;
	float ini_pos_y;
	bool activado;
	Avanzar();
	float darunPaso(float pos_x,float pos_y);


	virtual ~Avanzar();
};

#endif /* AVANZAR_H_ */
