#include "Agachar.h"

using namespace std;

Agachar::Agachar(float* altura,float nuevoYPiso){
	alturaPJ = *altura;
	pAlturaPJ = altura;
    yPiso = nuevoYPiso;
    estado = false;
    }

void Agachar::setEstado(bool nuevoEstado,Posicion pos) {
    estado = nuevoEstado;
    posInicial = pos;
}

Posicion Agachar::realizarAccion(Posicion posActual) {
    //Si el estado agachar esta desactivado y sigue en posicion de agachado, lo paro

	if(( yPiso - posActual.getY()  == alturaPJ/2) && (!estado)){
        Posicion nuevaPosicion;
        nuevaPosicion.setY(yPiso-alturaPJ);
        *pAlturaPJ = alturaPJ;
        nuevaPosicion.setX(posActual.getX());
        return nuevaPosicion;
    }

    //ese 200 representa la altura de la pantalla
	if ( (yPiso-posActual.getY() == alturaPJ) &&(estado)){
        Posicion nuevaPosicion;
        nuevaPosicion.setY(yPiso-alturaPJ);
        nuevaPosicion.setX(posActual.getX());
        *pAlturaPJ = alturaPJ/2;
        estado = false;
        return nuevaPosicion;
	}

    if ((yPiso-posActual.getY() == alturaPJ/2) && (estado)) {
        estado = false;
        return posActual;
    }
    return posActual;
}



Agachar::~Agachar(){

}

bool Agachar::getEstado() {
    return estado;
}
