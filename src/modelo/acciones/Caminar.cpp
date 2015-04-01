/*
 * Caminar.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../../modelo/acciones/Caminar.h"
#include <iostream>

using namespace std;

const float ancho_paso = 2;

Caminar::Caminar() {
	estado = false;
	//Orientacion true = orientacion derecha
	orientacion = true;
}

void Caminar::setEstado(bool nuevoEstado,bool nuevaOrtientacion){
	orientacion = nuevaOrtientacion;
	estado = nuevoEstado;
}

bool Caminar::getEstado(){
	return estado;
}

Posicion Caminar::realizarAccion(Posicion pos, bool dir){
	Posicion p = Posicion(ancho_paso, 0);
	if (dir){
		estado = false;
		cout<<"ESTA ES LA POSICION pos:"<<pos.getX()<<"-"<<pos.getY()<<endl;
		cout<<"ESTA ES LA POSICION p:"<<p.getX()<<"-"<<p.getY()<<endl;
		return pos + p;
	}
	cout<<"ESTA ES LA POSICION pos:"<<pos.getX()<<"-"<<pos.getY()<<endl;
	cout<<"ESTA ES LA POSICION p:"<<p.getX()<<"-"<<p.getY()<<endl;
	estado = false;
	return pos - p;
}

Caminar::~Caminar() {
}

