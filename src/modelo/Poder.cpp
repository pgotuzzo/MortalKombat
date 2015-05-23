#include "Poder.h"

//Constantes Poder

const float anchoPoder = 20;
const float altoPoder = 10;
const float proporcionPosYPoder = 0.2;
const float proporcionPosXPoder = 0.52;
const float danioPoder = 5;

Poder::Poder() {
    estado = DESACTIVADO;
    rectanguloPoder.d.w = anchoPoder;
    rectanguloPoder.d.h = altoPoder;
    danio = danioPoder;
    primerLoop = false;
}

void Poder::activar(Trect rectPJ,Tdireccion direccion,float anchoPantalla) {

    if(estado == DESACTIVADO){
        estado = ACTIVADO;
        primerLoop = true;
        rectanguloPoder.p.y = (float) (rectPJ.p.getY() + rectPJ.d.h /2 - rectanguloPoder.d.h-0.1);
        if (direccion == DERECHA) {
            rectanguloPoder.p.x = rectPJ.p.getX() + rectPJ.d.w;
            posFinalX = rectPJ.p.x + anchoPantalla;
        }
        else {
            rectanguloPoder.p.x = rectPJ.p.getX() - rectanguloPoder.d.w;
            posFinalX = rectPJ.p.x - anchoPantalla;
        }
        this->danio = danio;
        this->direccion = direccion;
        }
}

void Poder::avanzar(float avance) {
    if(estado == ACTIVADO && !primerLoop) {
        if (direccion == DERECHA){
            rectanguloPoder.p.x = rectanguloPoder.p.x + avance;
            if (rectanguloPoder.p.getX() >= posFinalX){
                this->estado = DESACTIVADO;
            }
        }
        else{
            rectanguloPoder.p.x = rectanguloPoder.p.x - avance;
            if (rectanguloPoder.p.getX() <= posFinalX){
                this->estado = DESACTIVADO;
            }
        }
    }
    primerLoop = false;
}

void Poder::setEstado(TestadoPoder nuevoEstado) {
    estado = nuevoEstado;
}

Trect Poder::getRectangulo() {
    return rectanguloPoder;
}

void Poder::modificarPosicion(Posicion nuevaPosicion) {
    rectanguloPoder.p = nuevaPosicion;
}


Poder::~Poder() {



}