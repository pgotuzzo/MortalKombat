
#include "CreadorDeGolpes.h"


CreadorDeGolpes::CreadorDeGolpes() {

}


void CreadorDeGolpes::crearGolpe(TestadoPersonaje tipoDeGolpe, Posicion posPJ, float anchoPJ, float altoPJ, bool direccion) {

    float ancho, altura, danio;
    Posicion pos = Posicion();
    switch (tipoDeGolpe){

        case (PINIA_ALTA):
            ancho = anchoPJ / 2;
            altura = altoPJ / 6;
            pos.setY(posPJ.getY());
            danio = 10;
            //danio
            break;
        case (PINIA_BAJA):
            ancho = anchoPJ / 2;
            altura = altoPJ / 6;
            pos.setY(posPJ.getY()+altoPJ / 3);
            danio = 7;
            break;
        case (PATADA_ALTA):
            ancho = anchoPJ;
            altura = altoPJ / 5;
            pos.setY(posPJ.getY());
            danio = 15;
            break;
        case (PATADA_BAJA):
            ancho = anchoPJ;
            altura = altoPJ / 5;
            pos.setY(posPJ.getY()+altoPJ / 3);
            danio = 12;
            break;
        default:
            break;
    }
    if (direccion) pos.setX(posPJ.getX() + anchoPJ /2 + ancho /2);
    else pos.setX(posPJ.getX() - anchoPJ / 2 - ancho / 2);

    golpe = new Golpe(pos,ancho,altura,danio);


}

Golpe* CreadorDeGolpes::getGolpe() {
    return golpe;
}

CreadorDeGolpes::~CreadorDeGolpes() {

}