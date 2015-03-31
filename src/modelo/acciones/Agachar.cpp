//
// Created by ven on 29/03/15.
//

#include "Agachar.h"


Agachar::Agachar(){
    estado = false;
    }
bool Agachar::getEstado(){
    return estado;
}
void Agachar::setEstado(bool nuevoEstado) {
    estado = nuevoEstado;
}
Agachar::~Agachar(){

}


Posicion Agachar::realizarAccion(Posicion posActual) {
    Posicion nuevaPosicion;
    nuevaPosicion.setX(posActual.getX()/2);
    nuevaPosicion.setY(posActual.getY()/2);
    estado = false;
    return nuevaPosicion;
}
