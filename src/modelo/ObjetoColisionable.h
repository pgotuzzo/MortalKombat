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

    void solucionColision(vector<ObjetoColisionable*>  objetosProximos);
    void determinarAccionPorColision(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto);
    void solucionarColision(ObjetoColisionable* enemigo);

    virtual ~ObjetoColisionable() {}

};


#endif //MORTALKOMBAT_OBJETOCOLISIONABLE_H



