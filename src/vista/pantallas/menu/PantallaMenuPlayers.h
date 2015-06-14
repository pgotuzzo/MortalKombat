#ifndef MORTALKOMBAT_PANTALLAMENUPLAYERS_H
#define MORTALKOMBAT_PANTALLAMENUPLAYERS_H


#include <array>
#include "../Pantalla.h"
#include "../../personajes/PersonajeVista.h"

class PantallaMenuPlayers : public Pantalla {
private:
    Ttexture mTextBackground;
    int filaPers1,filaPers2;
    Ttexture mTextSelector[2];
    Trect mRectSelector[2];
    PersonajeVista mPersonajes[2];

public:
    void InicializarPersonaje(Tpersonaje personaje,int index);
    PantallaMenuPlayers(Tdimension dimPixels, Tdimension dimUl);
    vector<Trect> getCuadradoPlayers();
    void update(vector<Posicion> players);
    void print();

    virtual ~PantallaMenuPlayers();
};


#endif //MORTALKOMBAT_PANTALLAMENUPLAYERS_H
