#include "SaltoVertical.h"

// Constantes para que se regule el salto vertical
const float altura_salto = 70;
const float intervalo_salto =7; // altura_salto / intervalo_salto = numero de loops


SaltoVertical::SaltoVertical() {
 	estado = false;
	subiendo = true; // Cuando se comienza a hacer el salto tiene que subir
}

bool SaltoVertical::getEstado() {
	return estado;
}

/*
 * Se activan el estado del salto y se setea la posicion del personaje antes de realizar el salto.
 */
void SaltoVertical::setEstado(bool nuevoEstado, Posicion nuevaPosicion) {

	estado = nuevoEstado;
	subiendo = nuevoEstado;
	posIni = nuevaPosicion;
	posImg = nuevaPosicion; // Para que no se pase del piso.

}

/*
 * Devuelve la posicion del personaje luego de un intervalo de salto hecho.
 */
Posicion SaltoVertical::realizarAccion(Posicion posActual){
	// Se fija si el salto esta activado para realizarlo.
	if (estado){
		// Condicion para que siga subiendo. La idea es que no se pase del y maximo.
		if ((posImg.getY() > posIni.getY() - altura_salto ) && (subiendo)){
			posImg.setY(posImg.getY() - intervalo_salto);
			return posImg;
		}
		// Condicion para que empieze a bajar.
		else{
			subiendo = false; // Esta bajando
			if (posImg.getY() < posIni.getY()){
				posImg.setY(posImg.getY() + intervalo_salto);
				return posImg;
			}
		}
	}
	estado = false; // se termino con el salto vertical.
	return posImg;
}

SaltoVertical::~SaltoVertical() {
}


