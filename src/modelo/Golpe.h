

#ifndef MORTALKOMBAT_GOLPE_H
#define MORTALKOMBAT_GOLPE_H

#include "../Common.h"
#include "ObjetoColisionable.h"

class Golpe: public ObjetoColisionable{

public:
    float danio;
    bool estado;

    float anchoPJ;
    float altoPJ;


    Golpe(float anchoPJ, float altoPJ);

    void activar(TestadoPersonaje tipoDeGolpe, Posicion posPJ,bool direccion);

    virtual ~Golpe();


};


#endif //MORTALKOMBAT_GOLPE_H
