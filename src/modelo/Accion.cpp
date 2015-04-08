#include "Accion.h"

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

void Accion::setEstado(bool nuevoEstado, Posicion nuevaPosicion) {

}

void Accion::setEstado(bool nuevoEstado, Posicion nuevaPosicion, bool orientacionSalto,float anchoPantalla) {

}

Posicion Accion::realizarAccion(Posicion posActual) {
	return posActual;
}

Posicion Accion::realizarAccion(Posicion pos, bool dir) {
	return pos;
}


