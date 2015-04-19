#ifndef MORTALKOMBAT_AGACHAR_H
#define MORTALKOMBAT_AGACHAR_H

#include "../Accion.h"

class Agachar : public Accion {

private:
    bool estado;
    Posicion posInicial;
    float alturaPJ;
    float yPiso;
    float* pAlturaPJ;
    float alturaAgachado;

public:
    Agachar(float* alturaPJ,float yPiso);

    bool getEstado();
    void setEstado(bool nuevoEstado,Posicion pos);

    Posicion realizarAccion(Posicion posActual);

    virtual~Agachar();
};


#endif //MORTALKOMBAT_AGACHAR_H
