
#ifndef MORTALKOMBAT_PODER_H
#define MORTALKOMBAT_PODER_H


#include "ObjetoColisionable.h"

class Poder: public ObjetoColisionable {

public:
    float danio;
    bool direccion;
    bool estado;

    Poder();
    Poder(Posicion posPJ,float anchoPJ, float altoPJ);

    void activar(float direccion,float danio,bool nuevoEstado);

    void avanzar(float avance);

    void solucionColision(vector<ObjetoColisionable*>  objetosProximos);
    void determinarAccionPorColision(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto);
    void solucionarColision(ObjetoColisionable* enemigo);

    ~Poder();

};


#endif //MORTALKOMBAT_PODER_H
