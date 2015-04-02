//
// Created by ven on 29/03/15.
//

#ifndef MORTALKOMBAT_AGACHAR_H
#define MORTALKOMBAT_AGACHAR_H

#include "../../modelo/Accion.h"
#include "../../modelo/Posicion.h"

class Agachar : public Accion {
    public:
    bool estado;
    Posicion posInicial;
    float alturaPJ;

    Agachar(float alturaPJ);
    Posicion realizarAccion(Posicion posActual);
    bool getEstado();
    void setEstado(bool nuevoEstado,Posicion pos);
    virtual~Agachar();
};


#endif //MORTALKOMBAT_AGACHAR_H
