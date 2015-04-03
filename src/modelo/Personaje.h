/*
 * Personaje.h
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <tr1/unordered_map>

#include "../modelo/Accion.h"
#include "../modelo/Posicion.h"
#include "../modelo/acciones/SaltoVertical.h"
#include "../modelo/acciones/SaltoOblicuo.h"
#include "../modelo/acciones/Caminar.h"
#include "../modelo/acciones/Agachar.h"



using namespace std;

class Personaje {
public:
	Posicion pos;
	bool orientacion;
	bool dir;
	float alturaDelPersonaje;
	float anchoDelPersonaje;
	Accion* accionesEnCurso[4];

	Personaje(Posicion posInicial,float alto,float ancho,float nuevoAltoEscenario);
	void realizarAccion(int orden,float anchoEscenario);
	Posicion verificarPunto(Posicion posicionActual,float anchoEscenario);
	void ejecutarAcionesActivadas(Accion **accionesEnCurso,float anchoEscenario);
	Posicion getPosicion();

	virtual ~Personaje();
};
#endif /* PERSONAJE_H_ */
