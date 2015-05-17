#include "../Common.h"
#include "Personaje.h"


Personaje::Personaje(Tdireccion direccionInicial,Trect cuerpo, float anchoPantalla) {

	rectanguloPj = cuerpo;

	this->anchoPantalla = anchoPantalla;
	yPiso = rectanguloPj.p.getY() + rectanguloPj.d.h;

	estadoActual = MOV_PARADO;
	estadoAnterior = MOV_PARADO;
	direccionPj = direccionInicial;
	sentidoPj = ADELANTE;

	poder = new Poder();
	vida = 100;

	llevarACabo.initialize(rectanguloPj,anchoPantalla,yPiso);
}


void Personaje::realizarAccion(Tinput orden) {

	if(estadoActual == MOV_AGACHADO) rectanguloPj.d.w = rectanguloPj.d.w *2;



	TestadoPersonaje estadoCompuesto = generarEstado(orden);

	if(puedoRealizarAccion(estadoCompuesto)){
		estadoAnterior = estadoActual;
		estadoActual = estadoCompuesto;
	}else{
		estadoAnterior = estadoActual;
	}

	posicionAnterior = rectanguloPj.p;

	rectanguloPj = llevarACabo.laAccion(estadoActual,countLoops, rectanguloPj.p,sentidoPj,direccionPj);

	// if(poder.estado == ACTIVADO) poder.avanzar();
	// poersonaje.getPoder.posicion

	if(loopsPara(estadoActual)==countLoops) estadoActual = MOV_PARADO;

	//Si el estado anterior es salto oblicuo y el nuevo estado es una patada o una pinia durante ese salto
	// el contador de loops no se reinicia. Lo mismo para el salto vertical

	bool accionDuranteOblicuo = (estadoAnterior == MOV_SALTANDO_OBLICUO &&(estadoActual==ACC_PINIA_SALTO||estadoActual==ACC_PATADA_SALTO));
	bool accionDuranteVertical = (estadoAnterior == MOV_SALTANDO_VERTICAL &&(estadoActual==ACC_PATADA_SALTO_VERTICAL));
	if((estadoAnterior != estadoActual) && (!accionDuranteOblicuo)&&(!accionDuranteVertical)) countLoops = 0;
	else countLoops++;
}

bool Personaje::puedoRealizarAccion(TestadoPersonaje accion) {


	//porque si esta en esos estados puede hacer cualquier cosa
	if(estadoActual == MOV_PARADO || estadoActual == MOV_CAMINANDO) return true;

	//Mientras salta solo puede pegar patada salto y pinia salto
	if(estadoActual == MOV_SALTANDO_OBLICUO){
		return accion == ACC_PINIA_ALTA ||accion == ACC_PINIA_BAJA || accion == ACC_PATADA_ALTA|| accion == ACC_PATADA_BAJA;
	}
	//Mientras salta verticalmente solo puede hacer una patada salto vertical
	if(estadoActual == MOV_SALTANDO_VERTICAL){
		return accion == ACC_PATADA_ALTA ||accion == ACC_PATADA_BAJA || accion == ACC_PODER;
	}
	//mientras esta agachado solo puede pegar pinias altas y bajas patada agachado y proteccion agachado
	if(estadoActual == MOV_AGACHADO){
		return accion == ACC_PINIA_ALTA || accion == ACC_PINIA_BAJA ||accion == ACC_PATADA_ALTA||accion == ACC_PATADA_BAJA || accion == ACC_PROTECCION;
	}
	//si se esta protegiendo solo puede agacharse
	if(estadoActual == ACC_PROTECCION){
		return accion == MOV_AGACHADO;
	}
	if(estadoActual == ACC_PROTECCION_AGACHADO){
		return accion == MOV_AGACHADO;
	}
	//si no esta haciendo ninguna de las enteriores
	//quiere decir que esta haciendo alguna patada pinia o poder, las cuales no se puede interrumpir o combinar con nada
	return false;
}

Trect Personaje::getRectangulo() {
	return rectanguloPj;
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
		case TinputMovimiento::KEY_IZQUIERDA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return MOV_CAMINANDO;
				case TinputAccion::KEY_PATADA_ALTA:
					return ACC_PATADA_ALTA;
				case TinputAccion::KEY_PATADA_BAJA:
					return ACC_PATADA_BAJA; // TODO: Ver mas tarde (patada baja atras), lo mismo con la alta
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
					return MOV_SALTANDO_VERTICAL;
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
					return MOV_SALTANDO_OBLICUO;
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
					return MOV_SALTANDO_OBLICUO;
				case TinputAccion::KEY_PODER:
					return MOV_SALTANDO_OBLICUO;
			}
			break;
	}
}


Personaje::~Personaje() {

}
