#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "math.h"
#include <tr1/unordered_map>
#include "../Common.h"
#include "ObjetoColisionable.h"
#include "Poder.h"
#include "Golpe.h"
#include "Accionador.h"


using namespace std;

class Personaje: public ObjetoColisionable{
public:
	TestadoPersonaje estadoActual;
	TestadoPersonaje estadoAnterior;

	Posicion posicionAnterior;
	Trect rectanguloPj;

	Tdireccion direccionPj;
	Tsentido sentidoPj;


	float vida;

	float yPiso;
	float anchoPantalla;
	int countLoops;

	Accionador llevarACabo;

	Poder* poder;

	//-----------------------------------------------------------------------------
	bool puedoRealizarAccion(TestadoPersonaje accion);
	TestadoPersonaje generarEstado(Tinput orden);
	Personaje(Tdireccion direccionInicial,Trect cuerpo,float anchoPantalla);

	Trect getRectangulo();

	void realizarAccion(Tinput orden);
	~Personaje();

};

#endif /* PERSONAJE_H_ */