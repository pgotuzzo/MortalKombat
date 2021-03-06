
#ifndef MORTALKOMBAT_PODER_H
#define MORTALKOMBAT_PODER_H


#include "ObjetoColisionable.h"
#include "../utils/PersonajeUtils.h"

class Poder: public ObjetoColisionable {

public:
    Trect rectanguloPoder;
    float danio;
    Tdireccion direccion;
    TestadoPoder estado;
    float posFinalX;
    bool primerLoop;
    TestadoPersonaje efecto;
    TestadoPersonaje efectoPoder;
    TestadoPersonaje efectoFatFuego;


    Poder(string creador);
    void activar(Trect rectPJ,Tdireccion direccion,float anchoPantalla,int efectoFat);
    void activar(Trect rectPJ,Tdireccion direccion,float anchoPantalla);
    void avanzar(float avance);
    void setEstado(TestadoPoder nuevoEstado);
    Trect getRectangulo();
    void modificarPosicion(Posicion nuevaPosicion);

    ~Poder();

};


#endif //MORTALKOMBAT_PODER_H