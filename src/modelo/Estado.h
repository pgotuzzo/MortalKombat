/*
 * Estado.h
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#ifndef ESTADO_H_
#define ESTADO_H_

#include <iostream>
#include "../modelo/Accion.h"
#include "../modelo/Direccion.h"
#include "../modelo/Orientacion.h"

using namespace std;

class Estado {
public:
	Orientacion orientacion;
	Direccion dir;



	Estado();
	virtual ~Estado();
};

#endif /* ESTADO_H_ */
