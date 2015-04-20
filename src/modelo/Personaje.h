#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "math.h"
#include <tr1/unordered_map>
#include "Accion.h"
#include "../Common.h"


using namespace std;

class Personaje {

public:

	bool parado;
	Posicion pos;
	Posicion posEnemigo;
	bool direccion;
	bool sentido;
	float alturaDelPersonaje;
	float anchoDelPersonaje;
	float altoEscenario;
	float yPiso;
	float distanciaMaxEnemigo;
	TestadoPersonaje estado;
	Accion* accionesEnCurso[4];

	Posicion verificarPuntoEnX(Posicion posicionActual,float anchoEscenario);
	Posicion verificarPuntoEnY(Posicion posicionActual);

	void ejecutarAcionesActivadas(Accion **accionesEnCurso,float anchoEscenario);


	Personaje(bool direccion,Posicion posInicial,float alto,float ancho,float nuevoAltoEscenario, float distMaxEnemigo);
	void realizarAccion(Tinput orden,float anchoEscenario);

	Posicion getPosicion();
	TestadoPersonaje getEstado();
	float getAlturaPersonaje();
	float getAnchoPersonaje();
	bool getDireccion();
	bool getSentido();

	virtual ~Personaje();

};
#endif /* PERSONAJE_H_ */
