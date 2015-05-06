
#include "Golpe.h"
#include "Colisionador.h"


//Constantes de los golpes

    // Divisores que dividen al ancho del PJ para tener el ancho del golpe
const float divisorAnchoPiniaAlta = 2;
const float divisorAnchoPiniaBaja = 2;
const float divisorAnchoPatadaAlta = 1;
const float divisorAnchoPatadaBaja = 1;

    // Divisores que dividen a la alutra del PJ para tener el alto del golpe (grosor)
const float divisorAltoPiniaAlta = 6;
const float divisorAltoPiniaBaja = 6;
const float divisorAltoPatadaAlta = 5;
const float divisorAltoPatadaBaja = 5;

    // Multiplicadores fraccionales de la posicion en y del golpe
const float multiplicadorYPiniaAlta = 1;
const float multiplicadorYPiniaBaja = 1;
const float multiplicadorYPatadaAlta = 1;
const float multiplicadorYPatadaBaja = 1;

Golpe::Golpe(float anchoPJ, float altoPJ){
    this->anchoPJ = anchoPJ;
    this->altoPJ = altoPJ;
}

void Golpe::activar(TestadoPersonaje tipoDeGolpe, Posicion posPJ,bool direccion){

    switch (tipoDeGolpe){

        case (PINIA_ALTA):
            ancho = anchoPJ / divisorAnchoPiniaAlta;
            altura = altoPJ / divisorAltoPiniaAlta;
            pos.setY(posPJ.getY() * multiplicadorYPiniaAlta);
            danio = 10;
            //danio
            break;
        case (PINIA_BAJA):
            ancho = anchoPJ / divisorAnchoPiniaBaja;
            altura = altoPJ / divisorAltoPiniaBaja;
            pos.setY(posPJ.getY() * multiplicadorYPiniaBaja);
            danio = 7;
            break;
        case (PATADA_ALTA):
            ancho = anchoPJ / divisorAnchoPatadaAlta;
            altura = altoPJ / divisorAltoPatadaAlta;
            pos.setY(posPJ.getY() * multiplicadorYPatadaAlta);
            danio = 15;
            break;
        case (PATADA_BAJA):
            ancho = anchoPJ / divisorAnchoPatadaBaja;
            altura = altoPJ / divisorAltoPatadaBaja;
            pos.setY(posPJ.getY() * multiplicadorYPatadaBaja);
            danio = 12;
            break;
        default:
            break;
    }

    if (direccion) pos.setX(posPJ.getX() + anchoPJ /2 + ancho /2);
    else pos.setX(posPJ.getX() - anchoPJ / 2 - ancho / 2);
}

float Golpe::getAltura() {
    return altura;
}

Golpe::~Golpe() {
}