#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "math.h"
#include <string>
#include <tr1/unordered_map>
#include "../utils/PersonajeUtils.h"
#include "ObjetoColisionable.h"
#include "Poder.h"
#include "Golpe.h"
#include "Accionador.h"
#include "Combo.h"


using namespace std;

class Personaje: public ObjetoColisionable{
public:

	string nombre;

	Posicion posInicial;

	TestadoPersonaje estadoActual;
	TestadoPersonaje estadoAnterior;

	Posicion posicionAnterior;
	Trect rectanguloPj;

	Tdireccion direccionPj;
	Tsentido sentidoPj;

	Combo* comboPoder;
	Combo* comboFatality;
	Combo* comboFatality2;

	float vida;

	float yPiso;
	float anchoPantalla;
	int countLoops;

	Accionador llevarACabo;

	int debuff;

	Poder* poder;
	Golpe* golpe;

	bool estadoFatality;
	//-----------------------------------------------------------------------------
	bool puedoRealizarAccion(TestadoPersonaje accion);
	TestadoPersonaje generarEstado(Tinput orden);
	Personaje(string nombre,Tdireccion direccionInicial,Trect cuerpo,float anchoPantalla,Tcombos combos);

	Trect getRectangulo();
	void modificarPosicion(Posicion nuevaPosicion);

	void realizarAccion(Tinput orden);
	void reducirVida(float danio,TestadoPersonaje reaccion);
	void empujado(float desplazamiento, Tdireccion direccion);
	void setPosicion(Posicion posicion);
	~Personaje();

	void reinicializar(TestadoPersonaje nuevoEstado);

	void verificarDireccion(Tinput tinput);

	bool estadoActualContinuaElAnterior();

	bool realizarsegundaPinia();

	void crearCombosdelPersonaje(Tcombos combos);

	void verificarDebuff();


	void verificarEstadoFatality();
};

#endif /* PERSONAJE_H_ */