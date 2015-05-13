#include "Poder.h"

//Constantes Poder

//Divisores del ancho y alto del Pj para calcular el ancho y alto del poder
const float divisorAnchoPoder = 2;
const float divisorAltoPoder = 4;

//Divisor de la altura del pj para calcular la posicion y del poder
const float divisorYPoder = 4;


Poder::Poder(float anchoPJ, float altoPJ) {


    this->anchoPJ = anchoPJ;
    this->altoPJ = altoPJ;

    estadoPoder = DESACTIVADO;

    ancho = anchoPJ / divisorAnchoPoder;

    altura = altoPJ / divisorAltoPoder;

    this->estado = false;


}

void Poder::activar(Posicion posPJ,float direccion, float danio, bool nuevoEstado) {

    float pos_x,pos_y;


    estadoPoder = ACTIVADO;

    //pos_y = posPJ.getY();
    pos_y = posPJ.getY();
    if (direccion) {
        pos_x = posPJ.getX() + anchoPJ;
        posFinalX = pos_x + 200;
    }
    else {
        pos_x = posPJ.getX() -ancho;
        posFinalX = pos_x - 200;
    }
    pos = Posicion(pos_x,pos_y);
    this->danio = danio;
    posInicialX =pos_x;
    this->direccion = direccion;

    this->estado = nuevoEstado;
}

void Poder::avanzar(float avance) {
    pos.mostrarPar();
    if(estado && estadoPoder == ACTIVADO) {
        if (direccion){
            cout<<"Costado derecho poder: "<<pos.getX()+ancho/2<<endl;
            pos = pos + Posicion(avance, 0);
            if (pos.getX() >= posFinalX){
                estado = false;
                estadoPoder = DESACTIVADO;
            }
        }
        else{
            cout<<"Costado izquierdo poder: "<<pos.getX()-ancho/2<<endl;
            pos = pos - Posicion(avance, 0);
            if (pos.getX() <= posFinalX){
                estado = false;
                estadoPoder = DESACTIVADO;
            }
        }
    }
}


float Poder::getAltura() {
    return altura;
}



Poder::~Poder() {



}