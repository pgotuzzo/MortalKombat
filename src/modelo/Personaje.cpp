#include "Personaje.h"


const float vidaInicial = 100;

Personaje::Personaje(string nombre,Tdireccion direccionInicial,Trect cuerpo, float anchoPantalla,Tcombos combos) {

	this->nombre = nombre;

	posInicial = cuerpo.p;

	rectanguloPj = cuerpo;
	posicionAnterior = cuerpo.p;

	this->anchoPantalla = anchoPantalla;
	yPiso = rectanguloPj.p.getY() + rectanguloPj.d.h;

	estadoActual = MOV_PARADO;
	estadoAnterior = MOV_PARADO;
	direccionPj = direccionInicial;
	sentidoPj = ADELANTE;

	poder = new Poder(nombre);
	golpe = new Golpe();

	crearCombosdelPersonaje(combos);

	vida = vidaInicial;

	llevarACabo.initialize(rectanguloPj,anchoPantalla,yPiso,poder,golpe);
	countLoops = 0;
	debuff = 0;
	estadoFatality = false;
	colisionando = false;
}

void Personaje::crearCombosdelPersonaje(Tcombos combos) {

	TComboData datosPoder,datosFatality,datosFatality2;

	datosPoder.nombre = "Poder";
	datosPoder.teclas = combos.poder;
	datosPoder.tiempoMaximo = (unsigned int) combos.tiempo * 1000;
	datosPoder.tolerancia = combos.errores;

	datosFatality.nombre = "Fatality";
	datosFatality.teclas = combos.fatality;
	datosFatality.tiempoMaximo = (unsigned int) combos.tiempo * 1000;
	datosFatality.tolerancia = combos.errores;

	datosFatality2.nombre = "Fatality2";
	datosFatality2.teclas = combos.fatality2;
	datosFatality2.tiempoMaximo = (unsigned int) combos.tiempo * 1000;
	datosFatality2.tolerancia = combos.errores;

	comboPoder = new Combo(datosPoder);
	comboFatality = new Combo(datosFatality);
	comboFatality2 = new Combo(datosFatality2);

}



void Personaje::realizarAccion(Tinput orden) {

	if((estadoActual != REA_FAT_FUEGO && estadoAnterior == REA_FAT_FUEGO)||
	   (estadoActual != REA_FAT_ARCADE && estadoAnterior == REA_FAT_ARCADE)||
	   (estadoActual != REA_FAT_LEVANTA && estadoAnterior == REA_FAT_LEVANTA)||
	   (estadoActual != REA_FAT_BRUTALITY_SUBZERO && estadoAnterior == REA_FAT_BRUTALITY_SUBZERO)) vida--;

	verificarEstadoFatality();
	TestadoPersonaje estadoCompuesto = generarEstado(orden);
	verificarDebuff();

	if (puedoRealizarAccion(estadoCompuesto)) {
		estadoAnterior = estadoActual;
		estadoActual = estadoCompuesto;
		verificarDireccion(orden);
		if (estadoActualContinuaElAnterior())countLoops++;
		else if(realizarsegundaPinia()) countLoops = countLoops--;
		else countLoops = 1;
	}
	else {
		if (estadoActual == REA_GOLPE_FUERTE && estadoAnterior != REA_GOLPE_FUERTE) countLoops = 0;
		if (estadoActual == REA_CONGELADO && estadoAnterior!= REA_CONGELADO) countLoops =0 ;
		estadoAnterior = estadoActual;
		countLoops++;
	}

	if (loopsPara(estadoActual) < countLoops) {
		if (estadoActual == ACC_PINIA_BAJA_AGACHADO) estadoActual = MOV_AGACHADO;
		else if(estadoActual == ACC_PATADA_AGACHADO)estadoActual = MOV_AGACHADO;
		else{
			estadoAnterior =estadoActual;
			estadoActual = MOV_PARADO;
		}
	}

	comboPoder->actualizar(orden);
	if(comboPoder->puedoRealizarCombo()){
		estadoAnterior = MOV_PARADO;
		estadoActual = ACC_PODER;
	}
	comboFatality->actualizar(orden);
	if(comboFatality->puedoRealizarCombo() && estadoFatality){
		estadoAnterior = estadoActual;
		if(nombre.compare("liukang") == 0) estadoActual = FAT_ARCADE;
		if(nombre.compare("subzero") == 0) estadoActual = FAT_FUEGO;
		if(nombre.compare("ermac") == 0) estadoActual = FAT_LEVANTA;
		countLoops = 1;
	}
	comboFatality2->actualizar(orden);
	if(comboFatality2->puedoRealizarCombo() && estadoFatality){
		estadoAnterior = estadoActual;
		if(nombre.compare("liukang") == 0) estadoActual = FAT_ARCADE;
		if(nombre.compare("subzero") == 0) {
			if(colisionando) estadoActual = FAT_BRUTALITY_SUBZERO;
		}
		if(nombre.compare("ermac") == 0) estadoActual = FAT_LEVANTA;
		countLoops = 1;
	}
	posicionAnterior = rectanguloPj.p;
	if (poder->estado == ACTIVADO) poder->avanzar(velocidadDelPoder);
	rectanguloPj = llevarACabo.laAccion(estadoActual, countLoops, rectanguloPj.p, sentidoPj, direccionPj);
	if (poder->estado == COLISION) poder->setEstado(DESACTIVADO);
}

bool Personaje::puedoRealizarAccion(TestadoPersonaje accion) {

	if(estadoActual == ACC_PINIA_ALTA)
		return accion == ACC_PINIA_ALTA;
	if(estadoActual == ACC_PINIA_BAJA)
		return accion == ACC_PINIA_BAJA;

	if(poder->estado==ACTIVADO){
		if(accion == ACC_PODER_SALTO || accion == ACC_PODER) return false;
	}
	//si se esta protegiendo solo puede agacharse
	if(estadoActual == ACC_PROTECCION||estadoActual == ACC_PROTECCION_AGACHADO){
		return accion == ACC_PROTECCION || accion == MOV_AGACHADO ||accion == ACC_PROTECCION_AGACHADO;
	}
	//porque si esta en esos estados puede hacer cualquier cosa
	if(estadoActual == MOV_PARADO || estadoActual == MOV_CAMINANDO) return true;

	//Mientras salta solo puede pegar patada salto y pinia salto
	if(estadoActual == MOV_SALTANDO_OBLICUO){
		if(accion == ACC_PATADA_ALTA || accion == ACC_PATADA_BAJA ){
			estadoAnterior = estadoActual;
			estadoActual = ACC_PATADA_SALTO;
		}
		if(accion == ACC_PINIA_ALTA || accion == ACC_PINIA_BAJA ){
			estadoAnterior = estadoActual;
			estadoActual = ACC_PINIA_SALTO;
		}
	}
	if(estadoActual == MOV_SALTANDO_OBLICUO){
		return accion == ACC_PINIA_SALTO|| accion == ACC_PATADA_SALTO;
	}

	//Mientras salta verticalmente solo puede hacer una patada salto vertical
	if(estadoActual == MOV_SALTANDO_VERTICAL){
		if(accion == ACC_PATADA_ALTA || accion == ACC_PATADA_BAJA ){
			estadoAnterior = estadoActual;
			estadoActual = ACC_PATADA_SALTO_VERTICAL;
		}
		if(accion == ACC_PINIA_ALTA || accion == ACC_PINIA_BAJA ){
			estadoAnterior = estadoActual;
			estadoActual = ACC_PINIA_SALTO_VERTICAL;
		}
		if(accion == ACC_PODER){
			estadoAnterior = estadoActual;
			estadoActual = ACC_PODER_SALTO;
		}
	}
	if(estadoActual == MOV_SALTANDO_VERTICAL){
		return accion == ACC_PATADA_SALTO_VERTICAL|| accion == ACC_PINIA_SALTO_VERTICAL;
	}
	//mientras esta agachado solo puede pegar pinias altas y bajas patada agachado y proteccion agachado
	if(estadoActual == MOV_AGACHADO){
		return accion == MOV_AGACHADO || accion == ACC_PROTECCION_AGACHADO ||accion == ACC_PATADA_AGACHADO
			   ||accion == ACC_PINIA_ALTA_AGACHADO || accion == ACC_PINIA_BAJA_AGACHADO;
	}

	//si no esta haciendo ninguna de las enteriores
	//quiere decir que esta haciendo alguna patada pinia o poder, las cuales no se puede interrumpir o combinar con nada
	return false;
}

Trect Personaje::getRectangulo() {
	return rectanguloPj;
}

void Personaje::modificarPosicion(Posicion nuevaPosicion) {
	rectanguloPj.p = nuevaPosicion;
}

void Personaje::verificarDireccion(Tinput orden) {

	switch(orden.movimiento){
		case TinputMovimiento::KEY_DERECHA:
			if(direccionPj == DERECHA) sentidoPj = ADELANTE;
			else sentidoPj = ATRAS;
			break;
		case TinputMovimiento::KEY_IZQUIERDA:
			if(direccionPj == DERECHA) sentidoPj = ATRAS;
			else sentidoPj = ADELANTE;
			break;
		case TinputMovimiento::KEY_ARRIBA_DERECHA:
			if(direccionPj == DERECHA) sentidoPj = ADELANTE;
			else sentidoPj = ATRAS;
			break;
		case TinputMovimiento::KEY_ARRIBA_IZQUIERDA:
			if(direccionPj == DERECHA) sentidoPj = ATRAS;
			else sentidoPj = ADELANTE;
			break;
	}

}

TestadoPersonaje Personaje::generarEstado(Tinput orden) {

	TinputMovimiento movimiento = orden.movimiento;
	TinputAccion accion = orden.accion;

	switch (movimiento){
		case TinputMovimiento::KEY_NADA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return MOV_PARADO;
				case TinputAccion::KEY_PATADA_ALTA:
					return ACC_PATADA_ALTA;
				case TinputAccion::KEY_PATADA_BAJA:
					return ACC_PATADA_BAJA;
				case TinputAccion::KEY_PINIA_ALTA:
					return ACC_PINIA_ALTA;
				case TinputAccion::KEY_PINIA_BAJA:
					return ACC_PINIA_BAJA;
				case TinputAccion::KEY_PROTECCION:
					return ACC_PROTECCION;
				case TinputAccion::KEY_PODER:
					if(estadoFatality)return FAT_LEVANTA;
					return MOV_PARADO;
			}
			break;
		case TinputMovimiento:: KEY_ABAJO:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return MOV_AGACHADO;
				case TinputAccion::KEY_PATADA_ALTA:
					return ACC_PATADA_AGACHADO;
				case TinputAccion::KEY_PATADA_BAJA:
					return ACC_PATADA_AGACHADO;
				case TinputAccion::KEY_PINIA_ALTA:
					return ACC_PINIA_ALTA_AGACHADO;
				case TinputAccion::KEY_PINIA_BAJA:
					return ACC_PINIA_BAJA_AGACHADO;
				case TinputAccion::KEY_PROTECCION:
					return ACC_PROTECCION_AGACHADO;
				case TinputAccion::KEY_PODER:
					return MOV_AGACHADO;
			}
			break;

		case TinputMovimiento::KEY_DERECHA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return MOV_CAMINANDO;
				case TinputAccion::KEY_PATADA_ALTA:
					if(direccionPj == IZQUIERDA) return ACC_PATADA_ALTA_ATRAS;
					return ACC_PATADA_ALTA;
				case TinputAccion::KEY_PATADA_BAJA:
					if(direccionPj == IZQUIERDA) return ACC_PATADA_BAJA_ATRAS;
					return ACC_PATADA_BAJA;
				case TinputAccion::KEY_PINIA_ALTA:
					return ACC_PINIA_ALTA;
				case TinputAccion::KEY_PINIA_BAJA:
					return ACC_PINIA_BAJA;
				case TinputAccion::KEY_PROTECCION:
					return ACC_PROTECCION;
				case TinputAccion::KEY_PODER:
					return ACC_PODER;
			}
			break;
		case TinputMovimiento::KEY_IZQUIERDA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return MOV_CAMINANDO;
				case TinputAccion::KEY_PATADA_ALTA:
					if(direccionPj == DERECHA) return ACC_PATADA_ALTA_ATRAS;
					return ACC_PATADA_ALTA;
				case TinputAccion::KEY_PATADA_BAJA:
					if(direccionPj == DERECHA) return ACC_PATADA_BAJA_ATRAS;
					return ACC_PATADA_BAJA;
				case TinputAccion::KEY_PINIA_ALTA:
					return ACC_PINIA_ALTA;
				case TinputAccion::KEY_PINIA_BAJA:
					return ACC_PINIA_BAJA;
				case TinputAccion::KEY_PROTECCION:
					return ACC_PROTECCION;
				case TinputAccion::KEY_PODER:
					return ACC_PODER;
			}
			break;
		case TinputMovimiento::KEY_ARRIBA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return MOV_SALTANDO_VERTICAL;
				case TinputAccion::KEY_PATADA_ALTA:
					return ACC_PATADA_SALTO_VERTICAL;
				case TinputAccion::KEY_PATADA_BAJA:
					return ACC_PATADA_SALTO_VERTICAL;
				case TinputAccion::KEY_PINIA_ALTA:
					return ACC_PINIA_SALTO;
				case TinputAccion::KEY_PINIA_BAJA:
					return ACC_PINIA_SALTO;
				case TinputAccion::KEY_PROTECCION:
					return ACC_PROTECCION;
				case TinputAccion::KEY_PODER:
					return ACC_PODER; // TODO: Ver cuando salta y tira el poder (nuevo estado?)
			}
			break;
		case TinputMovimiento::KEY_ARRIBA_DERECHA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return MOV_SALTANDO_OBLICUO;
				case TinputAccion::KEY_PATADA_ALTA:
					return ACC_PATADA_SALTO;
				case TinputAccion::KEY_PATADA_BAJA:
					return ACC_PATADA_SALTO;
				case TinputAccion::KEY_PINIA_ALTA:
					return ACC_PINIA_SALTO;
				case TinputAccion::KEY_PINIA_BAJA:
					return ACC_PINIA_SALTO;
				case TinputAccion::KEY_PROTECCION:
					return ACC_PROTECCION;
				case TinputAccion::KEY_PODER:
					return MOV_SALTANDO_OBLICUO;
			}
			break;
		case TinputMovimiento::KEY_ARRIBA_IZQUIERDA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return MOV_SALTANDO_OBLICUO;
				case TinputAccion::KEY_PATADA_ALTA:
					return ACC_PATADA_SALTO;
				case TinputAccion::KEY_PATADA_BAJA:
					return ACC_PATADA_SALTO;
				case TinputAccion::KEY_PINIA_ALTA:
					return ACC_PINIA_SALTO;
				case TinputAccion::KEY_PINIA_BAJA:
					return ACC_PINIA_SALTO;
				case TinputAccion::KEY_PROTECCION:
					return ACC_PROTECCION;
				case TinputAccion::KEY_PODER:
					return MOV_SALTANDO_OBLICUO;
			}
			break;
	}
}

void Personaje::reducirVida(float danio, TestadoPersonaje reaccion) {
	if(estadoActual == ACC_PROTECCION || estadoActual == ACC_PROTECCION_AGACHADO) danio = danio/2;
	if(vida <= danio) vida = 0;
	else vida = vida - danio;
	if(estadoActual != ACC_PROTECCION && estadoActual != ACC_PROTECCION_AGACHADO) {
		estadoAnterior = estadoActual;
		estadoActual = reaccion;
		countLoops = 1;
	}
}

bool Personaje::estadoActualContinuaElAnterior() {
	return (estadoAnterior == MOV_SALTANDO_OBLICUO && estadoActual == ACC_PINIA_SALTO) ||
		   (estadoAnterior == MOV_SALTANDO_OBLICUO && estadoActual == ACC_PATADA_SALTO)||
		   //Si el estado anterior era salto oblicuo y el actual patada salto o pinia salto tiene que seguir
		   // con los loops del estado anterior
		   (estadoAnterior == MOV_SALTANDO_VERTICAL && estadoActual == ACC_PINIA_SALTO_VERTICAL)||
		   (estadoAnterior == MOV_SALTANDO_VERTICAL && estadoActual == ACC_PATADA_SALTO_VERTICAL);
	//Si el estado anterior era salto vertical y el actual patada salto vertical o pinia salto tiene que seguir
	// con los loops del estado anterior
}

void Personaje::empujado(float desplazamiento, Tdireccion direccion) {
	rectanguloPj.p = llevarACabo.desplazado(desplazamiento,direccion);
}

void Personaje::setPosicion(Posicion posicion) {
	rectanguloPj = llevarACabo.setPosicionPersonaje(posicion);
}
Personaje::~Personaje(){
	delete poder;
	delete golpe;
	delete comboPoder;
	delete comboFatality;
}

bool Personaje::realizarsegundaPinia() {
	return ((estadoAnterior == ACC_PINIA_ALTA && estadoActual == ACC_PINIA_ALTA)||
			(estadoAnterior == ACC_PINIA_BAJA && estadoActual == ACC_PINIA_BAJA));
}

void Personaje::reinicializar(TestadoPersonaje nuevoEstado) {
//	vida = vidaInicial;
	countLoops = 0;
	estadoAnterior = estadoActual;
	estadoActual = nuevoEstado;
}

void Personaje::verificarDebuff() {
	//Activa el debuff y cada 30 loops le saca 1 de vida
	if(estadoActual == REA_MALDITO && debuff == 0) debuff = 150;
	if(debuff>0){
		if(debuff%30 == 0) {
			vida = vida - 1;
		}
		debuff--;
	}
}

void Personaje::verificarEstadoFatality() {
	if(estadoFatality){
		if((estadoActual!= FAT_FUEGO && estadoAnterior == FAT_FUEGO)||
				estadoActual!= FAT_ARCADE && estadoAnterior == FAT_ARCADE){
			if(llevarACabo.resultado == GANO){
				estadoFatality = false;
			}
		}
	}
}
