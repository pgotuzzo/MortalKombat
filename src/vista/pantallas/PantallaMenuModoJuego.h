#ifndef MORTALKOMBAT_MENUMODOJUEGO_H
#define MORTALKOMBAT_MENUMODOJUEGO_H

#include "Pantalla.h"
#include "../../utils/GameUtils.h"

class PantallaMenuModoJuego : public Pantalla {
private:
    Ttexture mTextBackground;
    Ttexture mTextSelector;
    Trect mRectSelector;

public:
    PantallaMenuModoJuego(Tdimension dimPixels, Tdimension dimUl);
    void update(EmodeSelection mode);
    void print();

    virtual ~PantallaMenuModoJuego();
};


#endif //MORTALKOMBAT_MENUMODOJUEGO_H
