#ifndef MORTALKOMBAT_MENUPLAYERS_H
#define MORTALKOMBAT_MENUPLAYERS_H


#include "../../utils/Common.h"

class MenuPlayers {
private:
//    EmodeSelection mSelection;
    bool mSelectionConfirmed[2];

    void updateSelection(TinputMovimiento direction);

public:
    MenuPlayers();

//    EmodeSelection update(Tinput input);
    bool selectionComplete();
};


#endif //MORTALKOMBAT_MENUPLAYERS_H
