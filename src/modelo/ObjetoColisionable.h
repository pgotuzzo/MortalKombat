#ifndef MORTALKOMBAT_OBJETOCOLISIONABLE_H
#define MORTALKOMBAT_OBJETOCOLISIONABLE_H


#include <vector>
#include "../Common.h"

class ObjetoColisionable {
public:

    Posicion pos;
    Posicion posAnt;
    float altura;
    float ancho;

    virtual void solucionColision(vector<ObjetoColisionable*>  objetosProximos) = 0;
    virtual void determinarAccionPorColision(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto)= 0;
    virtual ~ObjetoColisionable() {}
    virtual void solucionarColision(ObjetoColisionable* enemigo) = 0;

};


#endif //MORTALKOMBAT_OBJETOCOLISIONABLE_H



