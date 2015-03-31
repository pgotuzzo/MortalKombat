/*
 * SaltoOblicuo.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../../modelo/acciones/SaltoOblicuo.h"

const float alturaSalto = 50;
const float longitudSalto = 20;
const float intervaloSalto = 1;


SaltoOblicuo::SaltoOblicuo() {
	estado = false;
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
    a = alturaSalto / (b - c);
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
	float y = -a * (x - posInicial.getX()) * (x - posFinal.getX());
	pos.setX(x);
	pos.setY(y);
	if (pos.getY() <= posInicial.getY()){
			estado = false;
			return posFinal;
		}
	return pos;
}


SaltoOblicuo::~SaltoOblicuo() {
}

