

#ifndef MORTALKOMBAT_DETECTORDECOLISIONES_H
#define MORTALKOMBAT_DETECTORDECOLISIONES_H


#include "ObjetoColisionable.h"
#include "Personaje.h"
#include "Poder.h"
#include "Golpe.h"

class DetectorDeColisiones {

private:
    float anchoPantalla;
    float anchoEscenario;



    float distanciaColisionadaenX(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2);
    bool detectarColisionenY(ObjetoColisionable* objeto1, ObjetoColisionable* objeto2);
    float distancia(ObjetoColisionable* objeto1, ObjetoColisionable* objeto2);

    void colisionar(Personaje* personaje1, Personaje* personaje2);
    void colisionar(Personaje* personaje1, Golpe* golpe);
    void colisionar(Personaje* PJ, Poder* poder);
    void colisionar(Poder* poder1, Poder* poder2);


    void resolverColision(Personaje* PJ1, Personaje* PJ2);
    void resolverColision(Personaje* PJ,Golpe* golpe);
    void resolverColisionYAgarre(Personaje* personaje1,Personaje* personaje2);
    void resolverColisionconEscenario(Personaje* PJ);
    void resolverColisionconPantalla(Personaje* PJ1,Personaje* PJ2);

    bool verificarEstadosAnterioresAlChoque(Personaje* PJ);

    void separarPersonajes(Personaje* PJ1, Personaje* PJ2);

public:
    DetectorDeColisiones();
    DetectorDeColisiones(float anchoPantalla, float anchoEscenario);
    void resolverColisiones(Personaje* personaje1, Personaje* personaje2);
    bool detectarColision(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2);
};


#endif //MORTALKOMBAT_DETECTORDECOLISIONES_H
