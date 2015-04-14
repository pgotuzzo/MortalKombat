#include <iostream>
#include "SaltoOblicuo.h"

using namespace std;

// Constantes para regular el salto oblicuo
const float alturaSalto = 60;
const float longitudSalto = 60;
const float intervaloSalto = 3; // longitudSalto / intervaloSalto = numero de loops = numero de puntos


SaltoOblicuo::SaltoOblicuo(float altura) {
	estado = false;
	alturaPJ = altura;
}

/*
 * Se setea el estado del salto oblicuo, la posicion.
 * Saltara para el lado que indique la direccion.
 * El recorrido del salto se realiza mediante una funcion parabolica de la
 * forma y = a*(x-x1)*(x-x2) donde x1 y x2 son el x inicial y final del personaje.
 */
void SaltoOblicuo::setEstado(bool nuevoEstado,Posicion nuevaPosicion,bool sentidoSalto) {
    estado = nuevoEstado;
    posInicial = nuevaPosicion;
	posImg = nuevaPosicion; // Para que no se pase del margen.
    if (sentidoSalto) {
    	posFinal = posInicial + Posicion(longitudSalto,0);
    	coeficiente = 1.0; // este coeficiente sirve para saber si le tengo que restar o sumar a la posicion en x.
    }
    else{
    	posFinal = posInicial - Posicion(longitudSalto,0);
    	coeficiente = -1.0;
    }
    float b = pow(posInicial.getX()+posFinal.getX(),2) / 4;
    float c = posInicial.getX() * posFinal.getX();
    a = alturaSalto/ (b - c); // a de la funcion parabolica para que se respete el maximo y ancho que se quiere.
}

bool SaltoOblicuo::getEstado() {
    return estado;
}

/*
 * Se devuelve la posicion del personaje luego de un intervalo de salto hecho.
 */
Posicion SaltoOblicuo::realizarAccion(Posicion pos){

	float x = posImg.getX() + (coeficiente * intervaloSalto);

	//Representa la altura del pj dado que ahora tomamos su cabeza como referencia.
	// y al evaluar el x en la funcion parabolica
	float y = posInicial.getY() - (-a * (x - posInicial.getX()) * (x - posFinal.getX()));
	posImg.setX(x);
	posImg.setY(y);

	// Si se llega al piso o mas abajo desactivo el salto y devuelvo la posicion final del personaje.
	if (posImg.getY() >= posInicial.getY()){
			estado = false;
			return posFinal;
		}
	return posImg;
}


SaltoOblicuo::~SaltoOblicuo() {
}

