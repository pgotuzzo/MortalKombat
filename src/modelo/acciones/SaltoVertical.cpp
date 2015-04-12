#include "SaltoVertical.h"

const float altura_salto = 60;
const float intervalo_salto =5;


SaltoVertical::SaltoVertical() {
 	estado = false;
	subiendo = true;
}
bool SaltoVertical::getEstado() {
	return estado;
}

void SaltoVertical::setEstado(bool nuevoEstado, Posicion nuevaPosicion) {

	estado = nuevoEstado;
	subiendo = nuevoEstado;
	cout<<"ENTRA CON   "<<nuevaPosicion.getY()<<endl;
	posIni = nuevaPosicion;
	posImg = nuevaPosicion;

}

Posicion SaltoVertical::realizarAccion(Posicion posActual){

	if (estado){
		if ((posImg.getY() > posIni.getY() - altura_salto ) && (subiendo)){
			posImg.setY(posImg.getY() - intervalo_salto);
			cout<<"SUBIENDO  "<<posImg.getY()<<endl;
			return posImg;
		}
		else{
			subiendo = false;
			if (posImg.getY() < posIni.getY()){
				posImg.setY(posImg.getY() + intervalo_salto);
				cout<<"BAJANDO  "<<posImg.getY()<<endl;
				return posImg;
			}
		}
	}
	estado = false;
	cout<<"TERMINO  "<<posImg.getY()<<endl;
	return posImg;
}

SaltoVertical::~SaltoVertical() {
}


