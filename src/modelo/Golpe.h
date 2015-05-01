

#ifndef MORTALKOMBAT_GOLPE_H
#define MORTALKOMBAT_GOLPE_H

#include "../Common.h"
#include "ObjetoColisionable.h"

class Golpe: public ObjetoColisionable{

public:
    float danio;

    Golpe();

    Golpe(Posicion posicionGolpe, float anchoGolpe, float alturaGolpe,float danio);


    void solucionColision(vector<ObjetoColisionable*>  objetosProximos);
    void determinarAccionPorColision(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto);

    void solucionarColision(ObjetoColisionable* enemigo);

   virtual ~Golpe();


};


#endif //MORTALKOMBAT_GOLPE_H
