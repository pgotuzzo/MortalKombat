#ifndef MORTALKOMBAT_PANTALLAMENUPLAYERS_H
#define MORTALKOMBAT_PANTALLAMENUPLAYERS_H


#include <array>
#include "../Pantalla.h"

class PantallaMenuPlayers : public Pantalla {
private:
    Ttexture mTextBackground;
    Ttexture mTextSelector[2];
    Trect mRectSelector[2];

public:
    PantallaMenuPlayers(Tdimension dimPixels, Tdimension dimUl);
    void update(array<EtipoPersonaje, 2> players);
    void print();

    virtual ~PantallaMenuPlayers();
};


#endif //MORTALKOMBAT_PANTALLAMENUPLAYERS_H
