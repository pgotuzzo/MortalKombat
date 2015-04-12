#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <tr1/unordered_map>
#include "Accion.h"
#include "../Common.h"


using namespace std;

class Personaje {
public:
	bool parado;
	Posicion pos;
	bool orientacion;
	bool direccion;
	float alturaDelPersonaje;
	float anchoDelPersonaje;
	float altoEscenario;
	TestadoPersonaje estado;
	Accion* accionesEnCurso[4];

	Personaje(bool Orientacion,Posicion posInicial,float alto,float ancho,float nuevoAltoEscenario);
	void realizarAccion(int orden,float anchoEscenario);
	Posicion verificarPunto(Posicion posicionActual,float anchoEscenario);
	void ejecutarAcionesActivadas(Accion **accionesEnCurso,float anchoEscenario);
	Posicion getPosicion();
	TestadoPersonaje getEstado();
	float getAlturaPersonaje();
	float getAnchoPersonaje();
	bool getOrientacion();
	bool getDireccion();

	virtual ~Personaje();
};
#endif /* PERSONAJE_H_ */
