#ifndef MORTALKOMBAT_MENUGAMEMODE_H
#define MORTALKOMBAT_MENUGAMEMODE_H


#include "../../utils/GameUtils.h"
#include "../../utils/Common.h"

class MenuGameMode {
private:
    EmodeSelection mSelection;
    bool mSelectionConfirmed;

    void updateSelection(Tdireccion direction);

public:
    MenuGameMode();

    EmodeSelection update(Tinput input);
    bool selectionComplete();
};


#endif //MORTALKOMBAT_MENUGAMEMODE_H