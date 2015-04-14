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

private:

	bool parado;
	Posicion pos;
	bool direccion;
	bool sentido;
	float alturaDelPersonaje;
	float anchoDelPersonaje;
	float altoEscenario;
	float yPiso;
	TestadoPersonaje estado;
	Accion* accionesEnCurso[4];

	Posicion verificarPuntoEnX(Posicion posicionActual,float anchoEscenario);
	Posicion verificarPuntoEnY(Posicion posicionActual);

	void ejecutarAcionesActivadas(Accion **accionesEnCurso,float anchoEscenario);

public:

	Personaje(bool direccion,Posicion posInicial,float alto,float ancho,float nuevoAltoEscenario);
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
