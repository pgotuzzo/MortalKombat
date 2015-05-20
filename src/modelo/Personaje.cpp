#include "../Common.h"
#include "Personaje.h"


Personaje::Personaje(string nombre,Tdireccion direccionInicial,Trect cuerpo, float anchoPantalla) {

	this->nombre = nombre;

	rectanguloPj = cuerpo;
	posicionAnterior = cuerpo.p;

	this->anchoPantalla = anchoPantalla;
	yPiso = rectanguloPj.p.getY() + rectanguloPj.d.h;

	estadoActual = MOV_PARADO;
	estadoAnterior = MOV_PARADO;
	direccionPj = direccionInicial;
	sentidoPj = ADELANTE;

	poder = new Poder();
	vida = 100;

	llevarACabo.initialize(rectanguloPj,anchoPantalla,yPiso,poder);
	countLoops = 0;

}


void Personaje::realizarAccion(Tinput orden) {

	TestadoPersonaje estadoCompuesto = generarEstado(orden);

	if (puedoRealizarAccion(estadoCompuesto)) {
		estadoAnterior = estadoActual;
		estadoActual = estadoCompuesto;
		verificarDireccion(orden);
		if (estadoActualContinuaElAnterior())countLoops++;
		else countLoops = 1;
	}
	else {
		if (estadoActual == REA_GOLPE_FUERTE && estadoAnterior != REA_GOLPE_FUERTE) countLoops = 0;
		estadoAnterior = estadoActual;
		countLoops++;
	}
	// TODO: cambie en generarEstado que devuelvan ACC_PROTECCION cuando este saltando y demas.
	// TODO: con esta linea cada vez que apreto una tecla de mov cuando estoy protegido pasa por el estado parado
	if (loopsPara(estadoActual) < countLoops) {
		if (estadoActual == ACC_PINIA_BAJA_AGACHADO) estadoActual = MOV_AGACHADO;
		else if(estadoActual == ACC_PATADA_AGACHADO)estadoActual = MOV_AGACHADO;
		else{
			estadoAnterior =estadoActual;
			estadoActual = MOV_PARADO;
		}
	}
	//TODO: con esto anda (linea de abajo) de no pasar por el estado parado mientras esta protegido pero si despresiono el boton sigue protegido (probado con joystick)
	//if (loopsPara(estadoActual) < countLoops && estadoActual != ACC_PROTECCION) estadoActual = MOV_PARADO;

	posicionAnterior = rectanguloPj.p;

	rectanguloPj = llevarACabo.laAccion(estadoActual, countLoops, rectanguloPj.p, sentidoPj, direccionPj);


	if (poder->estado == ACTIVADO) poder->avanzar(10);
	if (poder->estado == COLISION) poder->setEstado(DESACTIVADO);

}

bool Personaje::puedoRealizarAccion(TestadoPersonaje accion) {

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
					return ACC_PODER;
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

void Personaje::reducirVida(float danio) {
	if(vida <= danio) vida = 0;
	else vida = vida - danio;
}

Personaje::~Personaje() {

}


void Personaje::caminar(){
	estadoActual = MOV_CAMINANDO;
	llevarACabo.laAccion(estadoActual,0,rectanguloPj.p,ATRAS,direccionPj);
	estadoActual =MOV_PARADO;
}

bool Personaje::estadoActualContinuaElAnterior() {
	return (estadoAnterior == MOV_SALTANDO_OBLICUO && estadoActual == ACC_PINIA_SALTO) ||
	(estadoAnterior == MOV_SALTANDO_OBLICUO && estadoActual == ACC_PATADA_SALTO)||
	//Si el estado anterior era salto oblicuo y el actual patada salto o pinia salto tiene que seguir
	// con los loops del estado anterior
	(estadoAnterior == MOV_SALTANDO_VERTICAL && estadoActual == ACC_PINIA_SALTO)||
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
