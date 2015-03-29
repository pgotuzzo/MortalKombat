/*
 * Caminar.h
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#ifndef ACCIONES_CAMINAR_H_
#define ACCIONES_CAMINAR_H_

#include "../../modelo/Direccion.h"
#include "../../modelo/Posicion.h"
#include "../../modelo/Accion.h"

class Caminar : public Accion{
public:

	Caminar();
	Posicion dar_un_paso(Posicion pos,Direccion dir);
	virtual ~Caminar();
};

#endif /* ACCIONES_CAMINAR_H_ */
