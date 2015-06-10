#ifndef MORTALKOMBAT_MENUPLAYERSELECTION_H
#define MORTALKOMBAT_MENUPLAYERSELECTION_H

#include <array>
#include "../../utils/Common.h"
#include "../../utils/PersonajeUtils.h"

class MenuPlayerSelection {

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

    void updateSelection(TinputMovimiento movimiento, int jugador);

public:
    MenuPlayerSelection();
    EtipoPersonaje getType(Posicion p);

    EtipoPersonaje personajesElegidos[2];

    vector<Posicion> update(vector<Tinput> inputs);
    bool selectionComplete();


};


#endif //MORTALKOMBAT_MENUPLAYERSELECTION_H
