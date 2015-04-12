#ifndef MORTALKOMBAT_AGACHAR_H
#define MORTALKOMBAT_AGACHAR_H

#include "../Accion.h"

class Agachar : public Accion {
    public:
    bool estado;
    Posicion posInicial;
    float alturaPJ;
    float yPiso;
    float* pAlturaPJ;
    float alturaAgachado;

    Agachar(float* alturaPJ,float yPiso);
    Posicion realizarAccion(Posicion posActual);
    bool getEstado();
    void setEstado(bool nuevoEstado,Posicion pos);
    virtual~Agachar();
};


#endif //MORTALKOMBAT_AGACHAR_H
