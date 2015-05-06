#include "Poder.h"



Poder::Poder() {
    estado = false;

}


Poder::Poder(Posicion posPJ,float anchoPJ, float altoPJ) {

    float pos_x,pos_y;

    pos_y = posPJ.getY() + altoPJ / 2;
    if (direccion) pos_x = posPJ.getX() + anchoPJ / 2 + anchoPJ/4;
    else pos_x = posPJ.getX() - anchoPJ / 2 - anchoPJ / 4;
    pos = Posicion(pos_x,pos_y);

    ancho = anchoPJ / 2;

    altura = altoPJ / 2;


}

void Poder::activar(float direccion, float danio, bool nuevoEstado) {
    this->danio = danio;

    this->direccion = direccion;

    this->estado = nuevoEstado;
}

void Poder::avanzar(float avance) {
    if(estado) {
        if (direccion)pos = pos + Posicion(avance, 0);
        else pos = pos - Posicion(avance, 0);
    }
    //pos.mostrarPar();
}



Poder::~Poder() {



}
