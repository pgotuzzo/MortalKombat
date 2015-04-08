#include <iostream>
#include "SaltoOblicuo.h"

using namespace std;

const float alturaSalto = 60;
const float longitudSalto = 60;
const float intervaloSalto = 3;


SaltoOblicuo::SaltoOblicuo(float altura) {
	estado = false;
	alturaPJ = altura;
}


void SaltoOblicuo::setEstado(bool nuevoEstado,Posicion nuevaPosicion,bool direccionSalto,float anchoPantalla) {
    estado = nuevoEstado;
	this->anchoPantalla = anchoPantalla;
    posInicial = nuevaPosicion;
    if (direccionSalto) {
    	posFinal = posInicial + Posicion(longitudSalto,0);
    	coeficiente = 1.0;
    }
    else{
    	posFinal = posInicial - Posicion(longitudSalto,0);
    	coeficiente = -1.0;
    }
    float b = pow(posInicial.getX()+posFinal.getX(),2) / 4;
    float c = posInicial.getX() * posFinal.getX();
    a = alturaSalto/ (b - c);
}

bool SaltoOblicuo::getEstado() {
    return estado;
}

/* Direccion
 * True ---> derecha
 * False---> izquierda
 */
Posicion SaltoOblicuo::realizarAccion(Posicion pos){
	float x = pos.getX() + (coeficiente * intervaloSalto);
	//Representa la altura del pj
	// dado que ahora tomamos su cabeza como referencia.
	float y = posInicial.getY() - (-a * (x - posInicial.getX()) * (x - posFinal.getX()));
	pos.setX(x);
	pos.setY(y);
	if (pos.getY() >= posInicial.getY()){
			estado = false;
			return posFinal;
		}
	return pos;
}


SaltoOblicuo::~SaltoOblicuo() {
}

