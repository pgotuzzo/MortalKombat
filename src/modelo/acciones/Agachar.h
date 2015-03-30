//
// Created by ven on 29/03/15.
//

#ifndef MORTALKOMBAT_AGACHAR_H
#define MORTALKOMBAT_AGACHAR_H

#include "../../modelo/Accion.h"

class Agachar : public Accion {
    public:
    bool estado;

    Agachar();
    bool getEstado();
    void setEstado(bool nuevoEstado);
    virtual~Agachar();
};


#endif //MORTALKOMBAT_AGACHAR_H
