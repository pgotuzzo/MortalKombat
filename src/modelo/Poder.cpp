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

void Poder::solucionColision(vector<ObjetoColisionable*>  objetosProximos){

}

void Poder::determinarAccionPorColision(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto){



}

void Poder::solucionarColision(ObjetoColisionable* enemigo) {
    this->estado = false;
    cout<<"PODERRRR"<<endl;
    float distancia;
    if(direccion){
        distancia = enemigo->pos.getX() - pos.getX() - enemigo->ancho/2 - ancho/2;
    }
    else distancia = pos.getX() - enemigo->pos.getX() - enemigo->ancho/2 - ancho/2;

    pos = Posicion(pos.getX()+distancia,pos.getY());

    //Lo congela al enemigo


}