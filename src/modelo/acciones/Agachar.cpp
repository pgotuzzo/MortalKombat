#include "Agachar.h"
#include <cmath>

using namespace std;

/*
 * Se recibe el yPiso para que no se pase al agacharse y calcular la posicion del personaje.
 * Se recibe un puntero a la altura del personaje para modificarla ( necesaria para achicar el sprite)
 *
 * Agachar se mantiene activado si se mantiene activada la tecla de agachar, sino dura un gameloop.
 */
Agachar::Agachar(float* altura,float nuevoYPiso){
	alturaPJ = *altura;
	pAlturaPJ = altura;
    yPiso = nuevoYPiso;
    alturaAgachado = (2 * alturaPJ/3); // Se definio que se va a achicar solo un tercio de su altura.
    estado = false;
    }

void Agachar::setEstado(bool nuevoEstado,Posicion pos) {
    estado = nuevoEstado;
    posInicial = pos;
}

bool Agachar::getEstado() {
    return estado;
}


Posicion Agachar::realizarAccion(Posicion posActual) {
    //Si el estado agachar esta desactivado y sigue en posicion de agachado, lo paro
    if(( floor(yPiso - posActual.getY()) == floor(alturaAgachado)) && (!estado)){
        Posicion nuevaPosicion;
        nuevaPosicion.setY(yPiso-alturaPJ);
        *pAlturaPJ = alturaPJ;
        nuevaPosicion.setX(posActual.getX());
        return nuevaPosicion;
    }

    //entra cuando el personaje no esta agachado y debe agacharse
	if ( (floor(yPiso-posActual.getY()) == floor(alturaPJ)) &&(estado)){
        Posicion nuevaPosicion;
        nuevaPosicion.setY(yPiso-alturaAgachado);
        nuevaPosicion.setX(posActual.getX());
        *pAlturaPJ = alturaAgachado;
        estado = false;
        return nuevaPosicion;
	}
    //entra cuando el personaje esta agachado y debe permanecer agachado
    if (( floor(yPiso - posActual.getY()) == floor(alturaAgachado) && (estado))) {
        estado = false;
        *pAlturaPJ = alturaAgachado;
        return posActual;
    }

    estado = false;
    return posActual;
}



Agachar::~Agachar(){

}


