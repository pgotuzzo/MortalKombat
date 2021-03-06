#ifndef MORTALKOMBAT_MENUMODOJUEGO_H
#define MORTALKOMBAT_MENUMODOJUEGO_H

#include "../Pantalla.h"
#include <vector>
#include "../../../utils/GameUtils.h"

class PantallaMenuModoJuego : public Pantalla {
private:
    Ttexture mTextBackground;
    Ttexture mTextSelector;
    Trect mRectSelector;

public:
    PantallaMenuModoJuego(Tdimension dimPixels, Tdimension dimUl);

    vector<Trect>getCuadradoModos();
    void update(EmodeSelection mode);
    void print();

    virtual ~PantallaMenuModoJuego();
};


#endif //MORTALKOMBAT_MENUMODOJUEGO_H
