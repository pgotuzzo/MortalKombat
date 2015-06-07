#include "MenuPlayers.h"

MenuPlayers::MenuPlayers() {
    mSelectionConfirmed[0] = false;
    mSelectionConfirmed[1] = false;
}

EtipoPersonaje MenuPlayers::getType(Posicion p) {
    if (p == Posicion(0, 0)) return EtipoPersonaje::SUBZERO;
    else if (p == Posicion(0, 1)) return EtipoPersonaje::SUBZERO_GREEN;
    else if (p == Posicion(0, 2)) return EtipoPersonaje::SUBZERO_RED;
    else if (p == Posicion(0, 3)) return EtipoPersonaje::SUBZERO_YELLOW;
    else if (p == Posicion(1, 0)) return EtipoPersonaje::ERMAC;
    else if (p == Posicion(1, 1)) return EtipoPersonaje::ERMAC_GREEN;
    else if (p == Posicion(1, 2)) return EtipoPersonaje::ERMAC_RED;
    else if (p == Posicion(1, 3)) return EtipoPersonaje::ERMAC_YELLOW;
    else if (p == Posicion(2, 0)) return EtipoPersonaje::LIUKANG;
    else if (p == Posicion(2, 1)) return EtipoPersonaje::LIUKANG_BLUE;
    else if (p == Posicion(2, 2)) return EtipoPersonaje::LIUKANG_GREEN;
    else if (p == Posicion(2, 3)) return EtipoPersonaje::LIUKANG_YELLOW;
    else return EtipoPersonaje::SUBZERO;
}

void MenuPlayers::updateSelection(TinputMovimiento movimientos[2]) {
    for (int i = 0; i < 2; i++){
        switch ( movimientos[i] ){
            case TinputMovimiento::KEY_ABAJO:{
                if (mSelection[i].y < ROWS)
                    mSelection[i].y++;
            };
            case TinputMovimiento::KEY_ARRIBA:{
                if (mSelection[i].y > 0)
                    mSelection[i].y--;
            };
            case TinputMovimiento::KEY_DERECHA:{
                if (mSelection[i].x < COLUMNS)
                    mSelection[i].x++;
            };
            case TinputMovimiento::KEY_IZQUIERDA:{
                if (mSelection[i].x > 0)
                    mSelection[i].x--;
            };
            case TinputMovimiento::KEY_ARRIBA_DERECHA:{
                if (mSelection[i].x < COLUMNS)
                    mSelection[i].x++;
                if (mSelection[i].y > 0)
                    mSelection[i].y--;
            };
            case TinputMovimiento::KEY_ARRIBA_IZQUIERDA:{
                if (mSelection[i].x > 0)
                    mSelection[i].x--;
                if (mSelection[i].y > 0)
                    mSelection[i].y--;
            };
        }
    }
}

array<EtipoPersonaje, 2> MenuPlayers::update(array<Tinput, 2> inputs) {
    TinputMovimiento movimientos[2] = {
            (mSelectionConfirmed[0]) ? TinputMovimiento::KEY_NADA : inputs.at(0).movimiento,
            (mSelectionConfirmed[1]) ? TinputMovimiento::KEY_NADA : inputs.at(1).movimiento
    };
    updateSelection(movimientos);
    array<EtipoPersonaje, 2> array = {
            getType(mSelection[0]),
            getType(mSelection[1])
    };
    return array;
};

bool MenuPlayers::selectionComplete() {
    return mSelectionConfirmed[0] && mSelectionConfirmed[1];
}
