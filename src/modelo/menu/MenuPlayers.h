#ifndef MORTALKOMBAT_MENUPLAYERS_H
#define MORTALKOMBAT_MENUPLAYERS_H


#include <array>
#include "../../utils/Common.h"
#include "../../utils/PersonajeUtils.h"

class MenuPlayers {
private:
    static const int ROWS = 4;
    static const int COLUMNS = 3;
    /**
     *  Este sera el menu de selección, gráficamente.
     *  //===================\\
     *  || SZ  || ER  || LK  ||
     *  ||=====||=====||=====||
     *  || SZg || ERg || LKb ||
     *  ||=====||=====||=====||
     *  || SZr || ERr || LKg ||
     *  ||=====||=====||=====||
     *  || SZy || ERy || LKy ||
     *  \\===================//
     */

    Posicion mSelection[2];
    bool mSelectionConfirmed[2];

    EtipoPersonaje getType(Posicion p);
    void updateSelection(TinputMovimiento movimientos[2]);

public:
    MenuPlayers();

    array<EtipoPersonaje, 2> update(array<Tinput, 2> inputs);
    bool selectionComplete();
};


#endif //MORTALKOMBAT_MENUPLAYERS_H
