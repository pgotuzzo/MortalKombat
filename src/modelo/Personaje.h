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
#include "ObjetoColisionable.h"
#include "Poder.h"
#include "Golpe.h"


using namespace std;

class Personaje: public ObjetoColisionable {

public:

 	bool enCaida;
	bool parado;
	bool direccion;
	bool sentido;
	float yPiso;
	float alturaParado;
	Posicion posInicial;
	TestadoPersonaje estado;
	Tinput inputAnterior;
	Accion* accionesEnCurso[4];
	float vida;

	int loopsGolpe;
	int loopsPiniaAlta;
	int loopsPiniaBaja;

	bool lanzandoGolpe;
	bool lanzandoPoder;
	bool protegiendose;

	Poder* poder;
	Golpe* golpe;


	void mePegaron(float danioGolpe);

	Posicion verificarPuntoEnX(Posicion posicionActual,float anchoEscenario);
	Posicion verificarPuntoEnY(Posicion posicionActual);

	void ejecutarAcionesActivadas(Accion **accionesEnCurso,float anchoEscenario);

	Personaje(bool direccion,Posicion posInicial,float alto,float ancho);
	void realizarAccion(Tinput orden,float anchoEscenario);
	TestadoPersonaje generarEstado(Tinput input);
	bool seguirPegando(TestadoPersonaje estadoInput);

	Posicion getPosicion();
	TestadoPersonaje getEstado();

	float getAltura();

	void setEstado(TestadoPersonaje estado);
	void setDireccion(bool direccion);
	float getAlturaPersonaje();
	float getAnchoPersonaje();
	bool getDireccion();
	bool getSentido();

	virtual ~Personaje();

	void caminar(bool direc);

	void saltarOblicuamente(bool direc);

	bool puedoRealizarAccion(TestadoPersonaje est);
};
#endif /* PERSONAJE_H_ */
