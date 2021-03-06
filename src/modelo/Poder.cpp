#include "Poder.h"

//Constantes Poder

const float anchoPoder = 20;
const float altoPoder = 10;
const float proporcionPosYPoder = 0.2;
const float proporcionPosXPoder = 0.52;
const float danioPoder = 5;

Poder::Poder(string creador) {
    estado = DESACTIVADO;
    rectanguloPoder.d.w = anchoPoder;
    rectanguloPoder.d.h = altoPoder;
    danio = danioPoder;
    primerLoop = false;
    if(creador.compare("subzero") == 0) efectoPoder = REA_CONGELADO;
    else if(creador.compare("ermac") == 0)efectoPoder = REA_MALDITO;
    else if(creador.compare("liukang") == 0)efectoPoder = REA_MALDITO;
    else efectoPoder = REA_GOLPE_ALTO;
    efecto = efectoPoder;
    efectoFatFuego = REA_FAT_FUEGO;
}
//Si esfectoFat es 0 el poder se activa con el efecto de la fatality
void Poder::activar(Trect rectPJ,Tdireccion direccion,float anchoPantalla,int efectoFat) {

    if(estado == DESACTIVADO){
        estado = ACTIVADO;
        primerLoop = true;
        rectanguloPoder.p.y = (float) (rectPJ.p.getY()+ rectPJ.d.h /4  - rectanguloPoder.d.h-0.1);
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
    efecto = efectoFatFuego;
}
//Si esfectoFat es 0 el poder se activa con el efecto de la fatality
void Poder::activar(Trect rectPJ,Tdireccion direccion,float anchoPantalla) {

    efecto = efectoPoder;
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