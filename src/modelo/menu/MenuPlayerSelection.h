#ifndef MORTALKOMBAT_MENUPLAYERSELECTION_H
#define MORTALKOMBAT_MENUPLAYERSELECTION_H

#include <array>
#include "../../utils/Common.h"
#include "../../utils/PersonajeUtils.h"
#include "../../Musica.h"

class MenuPlayerSelection {
public:
    static const int ROWS = 3;
    static const int COLUMNS = 4;

private:
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

    static const int MAX_LENGTH = 15;

    enum class State {
        PLAYER_1_CHARACTER,
        PLAYER_1_NAME,
        PLAYER_2_CHARACTER,
        PLAYER_2_NAME,
        COMPLETE
    };

    State mState;

    Musica* mMusic;
    array<Posicion, 2> mSelection;
    array<string, 2> mNames;

    bool updateSelectionKeyboard(TinputMovimiento movimiento, int jugador);
    bool updateSelectionMouse(Posicion mousePosition, int jugador);

public:
    MenuPlayerSelection();

    TmenuPlayerChanges update(Tinput inputs, Posicion mouse);
    bool selectionComplete();
    bool firstPlayerSelected();

    ~MenuPlayerSelection();
};


#endif //MORTALKOMBAT_MENUPLAYERSELECTION_H
