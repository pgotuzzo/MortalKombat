//
// Created by ven on 29/03/15.
//

#include "Agachar.h"


Agachar::Agachar(){
    estado = false;
    }

void Agachar::setEstado(bool nuevoEstado,Posicion pos) {
    estado = nuevoEstado;
    posInicial = pos;
}

Posicion Agachar::realizarAccion(Posicion posActual) {
	if ( posActual.getY() == posInicial.getY()/2){
		estado = false;
		return posInicial;
	}
    Posicion nuevaPosicion;
    nuevaPosicion.setY(posActual.getY()/2);
    nuevaPosicion.setX(posActual.getX());
    //estado = false;
    return nuevaPosicion;
}

bool Agachar::getEstado() {
    return estado;
}

Agachar::~Agachar(){

}
