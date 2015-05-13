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

    ancho = anchoPJ / divisorAnchoPoder;

    altura = altoPJ / divisorAltoPoder;

    this->estado = false;


}

void Poder::activar(Posicion posPJ,float direccion, float danio, bool nuevoEstado) {

    float pos_x,pos_y;

    //pos_y = posPJ.getY();
    pos_y = posPJ.getY();
    if (direccion) pos_x = posPJ.getX() + anchoPJ;
    else pos_x = posPJ.getX() -ancho;
    pos = Posicion(pos_x,pos_y);
    this->danio = danio;

    this->direccion = direccion;

    this->estado = nuevoEstado;
}

void Poder::avanzar(float avance) {
    pos.mostrarPar();
    if(estado) {
        if (direccion){
            cout<<"Costado derecho poder: "<<pos.getX()+ancho/2<<endl;
            pos = pos + Posicion(avance, 0);
        }
        else{
            cout<<"Costado izquierdo poder: "<<pos.getX()-ancho/2<<endl;
            pos = pos - Posicion(avance, 0);
        }
    }

}


float Poder::getAltura() {
    return altura;
}



Poder::~Poder() {



}