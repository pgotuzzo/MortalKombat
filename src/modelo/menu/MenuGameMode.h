#ifndef MORTALKOMBAT_MENUGAMEMODE_H
#define MORTALKOMBAT_MENUGAMEMODE_H


#include "../../utils/GameUtils.h"
#include "../../utils/Common.h"

class MenuGameMode {
private:
    EmodeSelection mSelection;
    bool mSelectionConfirmed;

    bool seleccionandoConMouse;

    void updateSelection(Tdireccion direction);

    bool dentroDelModo(Posicion posMouse,Trect modo);


public:
    MenuGameMode();

    EmodeSelection update(Tinput input);
    EmodeSelection update(Tinput input,Posicion coordenadasMouse,vector<Trect> modos);

    bool selectionComplete();
};


#endif //MORTALKOMBAT_MENUGAMEMODE_H
