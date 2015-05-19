#include "Poder.h"

//Constantes Poder

const float anchoPoder = 20;
const float altoPoder = 20;
const float proporcionPosYPoder = 0.2;
const float proporcionPosXPoder = 0.52;
const float danioPoder = 5;

Poder::Poder() {
    estado = DESACTIVADO;
    rectanguloPoder.d.w = anchoPoder;
    rectanguloPoder.d.h = altoPoder;
    danio = danioPoder;
}

void Poder::activar(Trect rectPJ,Tdireccion direccion,float anchoPantalla) {

    estado = ACTIVADO;

    rectanguloPoder.p.y = rectPJ.p.getY() + rectPJ.d.h * proporcionPosYPoder;
    if (direccion == DERECHA) {
        rectanguloPoder.p.x = rectPJ.p.getX() + rectPJ.d.w;
        posFinalX = rectPJ.p.x + anchoPantalla;
    }
    else {
        rectanguloPoder.p.x = rectPJ.p.getX();
        posFinalX = rectPJ.p.x - anchoPantalla;
    }
    this->danio = danio;
    this->direccion = direccion;
}

void Poder::avanzar(float avance) {
    TestadoPoder estadoPoder = this->estado;
    if(estadoPoder == ACTIVADO) {
        if (direccion == DERECHA){
            //cout<<"Costado derecho poder: "<<pos.getX()+ancho/2<<endl;
            rectanguloPoder.p.x = rectanguloPoder.p.x + avance;
            if (rectanguloPoder.p.getX() >= posFinalX){
                this->estado = DESACTIVADO;
            }
        }
        else{
            //cout<<"Costado izquierdo poder: "<<pos.getX()-ancho/2<<endl;
            rectanguloPoder.p.x = rectanguloPoder.p.x - avance;
            if (rectanguloPoder.p.getX() <= posFinalX){
                this->estado = DESACTIVADO;
            }
        }
    }
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