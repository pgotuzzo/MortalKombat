#ifndef MORTALKOMBAT_OBJETOCOLISIONABLE_H
#define MORTALKOMBAT_OBJETOCOLISIONABLE_H

#include "Personaje.h"
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

};


#endif //MORTALKOMBAT_OBJETOCOLISIONABLE_H



