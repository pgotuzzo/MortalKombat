/*
 * Caminar.h
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#ifndef ACCIONES_CAMINAR_H_
#define ACCIONES_CAMINAR_H_

#include "../../modelo/Posicion.h"
#include "../../modelo/Accion.h"

class Caminar : public Accion{
public:
	bool estado;
	bool direccion;
	//Orientacion true = orientacion derecha
	Caminar();
	bool getEstado();
	void setEstado(bool nuevoEstado, bool NuevaOrientacion);
	Posicion realizarAccion(Posicion pos);
	virtual ~Caminar();
};

#endif /* ACCIONES_CAMINAR_H_ */
