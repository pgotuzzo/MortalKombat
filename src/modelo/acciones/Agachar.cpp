#include "Agachar.h"
#include <cmath>

using namespace std;

Agachar::Agachar(float* altura,float nuevoYPiso){
	alturaPJ = *altura;
	pAlturaPJ = altura;
    yPiso = nuevoYPiso;
    alturaAgachado = (2 * alturaPJ)/3;
    estado = false;
    }

void Agachar::setEstado(bool nuevoEstado,Posicion pos) {
    estado = nuevoEstado;
    posInicial = pos;
}

Posicion Agachar::realizarAccion(Posicion posActual) {
    //Si el estado agachar esta desactivado y sigue en posicion de agachado, lo paro
    if(( floor(yPiso - posActual.getY()) == floor(alturaAgachado)) && (!estado)){
        Posicion nuevaPosicion;
        nuevaPosicion.setY(yPiso-alturaPJ);
        *pAlturaPJ = alturaPJ;
        nuevaPosicion.setX(posActual.getX());
        nuevaPosicion.mostrarPar();
        cout<<endl<<"NO SE AGACHA MAS  "<<nuevaPosicion.getY()<<endl;
        return nuevaPosicion;
    }

    //entra cuando el personaje no esta agachado y debe agacharse
	if ( (yPiso-posActual.getY() == alturaPJ) &&(estado)){
        Posicion nuevaPosicion;
        nuevaPosicion.setY(yPiso-alturaAgachado);
        nuevaPosicion.setX(posActual.getX());
        *pAlturaPJ = alturaAgachado;
        estado = false;
        cout<<endl<<"SE AGACHA  "<<nuevaPosicion.getY()<<endl;
        return nuevaPosicion;
	}
    //entra cuando el personaje esta agachado y debe permanecer agachado
    if (( floor(yPiso - posActual.getY()) == floor(alturaAgachado) && (estado))) {
        estado = false;
        *pAlturaPJ = alturaAgachado;
        cout<<endl<<"SE SIGUE AGACHANDO  "<<posActual.getY()<<endl;
        return posActual;
    }

    estado = false;
    return posActual;
}



Agachar::~Agachar(){

}

bool Agachar::getEstado() {
    return estado;
}
