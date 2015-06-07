#ifndef MORTALKOMBAT_MENUPLAYERS_H
#define MORTALKOMBAT_MENUPLAYERS_H


#include <array>
#include "../../utils/Common.h"
#include "../../utils/PersonajeUtils.h"

class MenuPlayers {
private:
    static const int ROWS = 3;
    static const int COLUMNS = 4;
    /**
     *  Este sera el menu de selección, gráficamente.
     *  //==========================\\
     *  || SZ  || SZg || SZr || SZy ||
     *  ||=====||=====||=====||=====||
     *  || ER  || ERb || ERg || ERy ||
     *  ||=====||=====||=====||=====||
     *  || LK  || LKb || LKg || LKy ||
     *  \\==========================//
     */

    Posicion mSelection[2];
    bool mSelectionConfirmed[2];

    EtipoPersonaje getType(Posicion p);
    void updateSelection(TinputMovimiento movimientos[2]);

public:
    MenuPlayers();

    vector<EtipoPersonaje> update(vector<Tinput> inputs);
    bool selectionComplete();
};


#endif //MORTALKOMBAT_MENUPLAYERS_H
