/*
 * Accion.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../modelo/Accion.h"

Accion::Accion() {

}

Accion::~Accion() {
}

bool Accion::getEstado() {
    return estado;
}

void Accion::setEstado(bool nuevoEstado) {

}

void Accion::setEstado(bool nuevoEstado, bool orientacion) {

}

Posicion Accion::realizarAccion(Posicion pos, bool dir) {
    return Posicion();
}

Posicion Accion::realizarAccion(Posicion posActual) {
    return Posicion();
}

void Accion::setEstado(bool nuevoEstado, Posicion nuevaPosicion) {

}

void Accion::setEstado(bool nuevoEstado, Posicion nuevaPosicion, bool orientacionSalto) {

}
