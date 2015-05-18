

#ifndef MORTALKOMBAT_DETECTORDECOLISIONES_H
#define MORTALKOMBAT_DETECTORDECOLISIONES_H


#include "ObjetoColisionable.h"
#include "Personaje.h"
#include "Poder.h"
#include "Golpe.h"

class DetectorDeColisiones {

private:
    bool detectarColision(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2);
    float distanciaColisionadaenX(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2);
    bool detectarColisionenY(ObjetoColisionable* objeto1, ObjetoColisionable* objeto2);

    void colisionar(Personaje* personaje1, Personaje* personaje2);
    void colisionar(Personaje* personaje1, Golpe* golpe);
    void colisionar(Personaje* personaje1, Poder* poder);
    void colisionar(Poder* poder1, Poder* poder2);


    void resolverColision(Personaje* PJ1, Personaje* PJ2);
    void resolverColision(Personaje* PJ,Golpe* golpe);
    void resolverColision(Personaje* PJ, Poder* poder);
    void resolverColision(Poder* poder1,Poder* poder2);

    bool hayEfectoTunel(ObjetoColisionable* objeto1, ObjetoColisionable* objeto2);

    bool verificarEstadosAnterioresAlChoque(Personaje* PJ);

    void separarPersonajes(Personaje* PJ1, Personaje* PJ2);

public:
    void resolverColisiones(Personaje* personaje1, Personaje* personaje2);
};


#endif //MORTALKOMBAT_DETECTORDECOLISIONES_H
