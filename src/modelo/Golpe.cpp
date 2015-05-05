

#include "Golpe.h"
#include "Colisionador.h"

Golpe::Golpe(){

}

Golpe::Golpe(Posicion posicionGolpe, float anchoGolpe, float alturaGolpe,float danio) {
    pos = posicionGolpe;
    posAnt = pos;
    ancho = anchoGolpe;
    altura = alturaGolpe;
    this->danio = danio;
}


void Golpe::solucionColision(vector<ObjetoColisionable*>  objetosProximos){


}

void Golpe::determinarAccionPorColision(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto){

}

void Golpe::solucionarColision(ObjetoColisionable* enemigo) {

}

Golpe::~Golpe() {
}