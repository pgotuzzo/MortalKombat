/*
 * Posicion.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../modelo/Posicion.h"

Posicion::Posicion(float pos_x,float pos_y) {
	x = pos_x;
	y = pos_y;
}

float Posicion::get_x(){
	return x;
}

float Posicion::get_y(){
	return y;
}

Posicion Posicion::operator=(Posicion p){
	x = p.get_x();
	y = p.get_y();
	return p;
}
Posicion Posicion::operator+(Posicion p){
	return {x + p.get_x(), y + p.get_y()};
}
Posicion Posicion::operator-(Posicion p){
	return {x - p.get_x(), y - p.get_y()};
}
bool Posicion::operator==(Posicion p){
	if ( (p.get_x() == x) && (p.get_y() == y) )
		return true;
	return false;
}


void Posicion::set_x(float pos_x){
	x = pos_x;
}

void Posicion::set_y(float pos_y){
	y = pos_y;
}

Posicion::~Posicion() {
	// TODO Auto-generated destructor stub
}

Posicion::Posicion() {

}
