
#include "Golpe.h"

Golpe::Golpe(){
    efectoSobreOponente = MOV_PARADO;
    rectangulo.d = Tdimension(0,0);
    rectangulo.p = Posicion(0,0);
    estado = false;
    danio = 0;
}

Trect Golpe::getRectangulo() {
    return rectangulo;
}

void Golpe::modificarPosicion(Posicion nuevaPosicion) {
    rectangulo.p = nuevaPosicion;
}


void Golpe::setGolpe(float danio, bool estado, Trect rectan, TestadoPersonaje nuevoEstado) {

    efectoSobreOponente = nuevoEstado;
    rectangulo = rectan;
    this->estado = estado;
    this->danio = danio;
}
void Golpe::setEstado(bool nuevoEstado){
    estado = nuevoEstado;
}
Golpe::~Golpe() {
}