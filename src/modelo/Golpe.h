

#ifndef MORTALKOMBAT_GOLPE_H
#define MORTALKOMBAT_GOLPE_H

//#include "../Common.h"
#include "ObjetoColisionable.h"

class Golpe: public ObjetoColisionable{

public:
    Trect rectangulo;
    float danio;
    bool estado;
    TestadoPersonaje efectoSobreOponente;
    Golpe();
    ~Golpe();
    void setGolpe(float danio,bool estado, Trect rectangulo, TestadoPersonaje nuevoEstado);
    Trect getRectangulo();

};


#endif //MORTALKOMBAT_GOLPE_H