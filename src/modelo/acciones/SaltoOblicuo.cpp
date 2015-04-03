/*
 * SaltoOblicuo.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../../modelo/acciones/SaltoOblicuo.h"
#include <iostream>
using namespace std;

const float alturaSalto = 30;
const float longitudSalto = 30;
const float intervaloSalto = 1;


SaltoOblicuo::SaltoOblicuo(float altura) {
	estado = false;
	alturaPJ = altura;
}


void SaltoOblicuo::setEstado(bool nuevoEstado,Posicion nuevaPosicion,bool direccionSalto) {
    estado = nuevoEstado;
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
	//pos.setY(y- ((altoPantalla - yPiso)- alturaPJ));
	if (pos.getY() >= posInicial.getY()){
			estado = false;
			return posFinal;
		}
	return pos;
}


SaltoOblicuo::~SaltoOblicuo() {
}

