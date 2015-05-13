
#ifndef MORTALKOMBAT_PODER_H
#define MORTALKOMBAT_PODER_H


#include "ObjetoColisionable.h"

class Poder: public ObjetoColisionable {

public:
    float danio;
    bool direccion;
    bool estado;

    float posInicialX;
    float posFinalX;

    TestadoPoder estadoPoder;

    float altoPJ;
    float anchoPJ;

    Poder(float anchoPJ, float altoPJ);

    void activar(Posicion posPJ,float direccion,float danio,bool nuevoEstado);

    void avanzar(float avance);

    float getAltura();

    void solucionColision(vector<ObjetoColisionable*>  objetosProximos);
    void determinarAccionPorColision(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto);
    void solucionarColision(ObjetoColisionable* enemigo);

    ~Poder();

};


#endif //MORTALKOMBAT_PODER_H