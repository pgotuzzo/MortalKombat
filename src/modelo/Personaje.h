#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "math.h"
#include <string>
#include <tr1/unordered_map>
#include "../Common.h"
#include "ObjetoColisionable.h"
#include "Poder.h"
#include "Golpe.h"
#include "Accionador.h"


using namespace std;

class Personaje: public ObjetoColisionable{
public:

	string nombre;
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
	Personaje(string nombre,Tdireccion direccionInicial,Trect cuerpo,float anchoPantalla);

	Trect getRectangulo();
	void modificarPosicion(Posicion nuevaPosicion);

	void realizarAccion(Tinput orden);
	void reducirVida(float danio);
	void empujado(float desplazamiento, Tdireccion direccion);
	void setPosicion(Posicion posicion);
	~Personaje();

	void verificarDireccion(Tinput tinput);

	bool estadoActualContinuaElAnterior();

	bool seguirLaPinia();
};

#endif /* PERSONAJE_H_ */