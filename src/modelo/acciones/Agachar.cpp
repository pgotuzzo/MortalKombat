//
// Created by ven on 29/03/15.
//

#include "Agachar.h"


Agachar::Agachar(){
    estado = false;
    }

void Agachar::setEstado(bool nuevoEstado) {
    estado = nuevoEstado;
}

Posicion Agachar::realizarAccion(Posicion posActual) {
    Posicion nuevaPosicion;
    nuevaPosicion.setY(posActual.getY()/2);
    estado = false;
    return nuevaPosicion;
}

bool Agachar::getEstado() {
    return estado;
}

Agachar::~Agachar(){

}