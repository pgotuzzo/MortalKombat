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

    virtual float getAltura() = 0;

    virtual ~ObjetoColisionable() {}

};


#endif //MORTALKOMBAT_OBJETOCOLISIONABLE_H


