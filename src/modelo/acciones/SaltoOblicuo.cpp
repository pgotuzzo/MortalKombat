#include <iostream>
#include "SaltoOblicuo.h"

using namespace std;

// Constantes para regular el salto oblicuo
const float alturaSaltoDefault = 70;
const float longitudSaltoDefault = 70;
const float intervaloSaltoDefault = 3; // longitudSalto / intervaloSalto = numero de loops = numero de puntos


SaltoOblicuo::SaltoOblicuo(float altura) {
	estado = false;
	alturaPJ = altura;

	alturaSalto = alturaSaltoDefault;
	longitudSalto = longitudSaltoDefault;
	intervaloSalto = intervaloSaltoDefault;
}

void SaltoOblicuo::setConfiguracion(float alturaSalto, float longitudSalto, float intervaloSalto) {
	this->alturaSalto = alturaSalto;
	this->longitudSalto = longitudSalto;
	this->intervaloSalto = intervaloSalto;

}

void SaltoOblicuo::setConfiguracionDefault() {
	alturaSalto = alturaSaltoDefault;
	longitudSalto = longitudSaltoDefault;
	intervaloSalto = intervaloSaltoDefault;
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
	primeraVez = true;
}

bool SaltoOblicuo::getEstado() {
	return estado;
}

void SaltoOblicuo::setEstado(bool nuevoEstado) {
	estado = nuevoEstado;
}

/*
 * Se devuelve la posicion del personaje luego de un intervalo de salto hecho.
 */
Posicion SaltoOblicuo::realizarAccion(Posicion pos,bool EnCaida){

	float x = posImg.getX() + (coeficiente * intervaloSalto);
	float y = posInicial.getY() - (-a * (x - posInicial.getX()) * (x - posFinal.getX()));
	posImg.setX(x);
	posImg.setY(y);
	if(!EnCaida){
		//Representa la altura del pj dado que ahora tomamos su cabeza como referencia.
		// y al evaluar el x en la funcion parabolica
		// Si se llega al piso o mas abajo desactivo el salto y devuelvo la posicion final del personaje.
		if (posImg.getY() >= posInicial.getY()){
			estado = false;
			return posFinal;
		}
		return posImg;
	}
	else{
		if(primeraVez){
			posCaida = pos;
			primeraVez = false;
		}
		if (posImg.getY() >= posInicial.getY()){
			estado = false;
			primeraVez = false;
			return Posicion(posCaida.getX(),posFinal.getY());
		}
		return Posicion(posCaida.getX(),posImg.getY());
	}

}


SaltoOblicuo::~SaltoOblicuo() {}