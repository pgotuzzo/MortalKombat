/*
 * Accion.h
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#ifndef ACCION_H_
#define ACCION_H_

#include "../modelo/Estado.h"

class Accion : public Estado{
public:
	Accion();
	bool puedoAccionar();

	virtual ~Accion();
};

#endif /* ACCION_H_ */
