/*
 * Posicion.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../modelo/Posicion.h"
#include <iostream>

using namespace std;

Posicion::Posicion(float pos_x,float pos_y) {
	x = pos_x;
	y = pos_y;
}

float Posicion::getX(){
	return x;
}

float Posicion::getY(){
	return y;
}

Posicion Posicion::operator=(Posicion p){
	x = p.getX();
	y = p.getY();
	return p;
}
Posicion Posicion::operator+(Posicion p){
	return Posicion(x + p.getX(), y + p.getY());
}
Posicion Posicion::operator-(Posicion p){
	return Posicion(x - p.getX(), y - p.getY());
}
bool Posicion::operator==(Posicion p){
	if ( (p.getX() == x) && (p.getY() == y) )
		return true;
	return false;
}


void Posicion::setX(float pos_x){
	x = pos_x;
}

void Posicion::setY(float pos_y){
	y = pos_y;
}

Posicion::~Posicion() {
	// TODO Auto-generated destructor stub
}

Posicion::Posicion(){
	x = 0;
	y = 0;
}
void Posicion::mostrarPar(){
	cout<<"ESTA ES LA POSICION"<<endl;
	cout<<"X: "<<x<<" - "<<"Y: "<<y<<endl;
}

