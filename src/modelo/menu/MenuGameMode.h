#ifndef MORTALKOMBAT_MENUGAMEMODE_H
#define MORTALKOMBAT_MENUGAMEMODE_H


#include "../../utils/GameUtils.h"
#include "../../utils/Common.h"
#include "../../Musica.h"
class MenuGameMode {
private:
    EmodeSelection mSelection;
    bool mSelectionConfirmed;

    bool seleccionandoConMouse;

    void updateSelection(Tdireccion direction);

    bool dentroDelModo(Posicion posMouse, Trect modo);

    Musica* musica;

public:
    MenuGameMode();

    void update(Tinput input);
    void update(Tinput input,Posicion coordenadasMouse,vector<Trect> modos);

    EmodeSelection getSelection();
    bool selectionComplete();

    ~MenuGameMode();
};


#endif //MORTALKOMBAT_MENUGAMEMODE_H