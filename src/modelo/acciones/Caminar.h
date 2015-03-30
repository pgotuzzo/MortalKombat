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
	bool estado;
	bool orientacion;
	//Orientacion true = orientacion derecha
	Caminar();
	void setEstado(bool nuevoEstado, bool NuevaOrientacion);
	Posicion darUnPaso(Posicion pos,Direccion dir);
	virtual ~Caminar();
};

#endif /* ACCIONES_CAMINAR_H_ */
