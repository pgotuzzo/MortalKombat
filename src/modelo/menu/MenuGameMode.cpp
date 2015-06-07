#include "MenuGameMode.h"

MenuGameMode::MenuGameMode() {
    mSelection = EmodeSelection::MULTIPLAYER;
    mSelectionConfirmed = false;
}

void MenuGameMode::updateSelection(Tdireccion direction) {
    switch (mSelection){
        case EmodeSelection::MULTIPLAYER:
            mSelection = (direction == DERECHA) ? EmodeSelection::ARCADE : EmodeSelection::MULTIPLAYER;
            break;
        case EmodeSelection::ARCADE:
            mSelection = (direction == DERECHA) ? EmodeSelection::PRACTICE : EmodeSelection::MULTIPLAYER;
            break;
        case EmodeSelection::PRACTICE:
            mSelection = (direction == DERECHA) ? EmodeSelection::PRACTICE : EmodeSelection::ARCADE;
            break;
    }
}

EmodeSelection MenuGameMode::update(Tinput input) {
    switch (input.movimiento){
        case TinputMovimiento::KEY_DERECHA:
        case TinputMovimiento::KEY_ARRIBA_DERECHA:
            updateSelection(DERECHA);
            break;
        case TinputMovimiento::KEY_IZQUIERDA:
        case TinputMovimiento::KEY_ARRIBA_IZQUIERDA:
            updateSelection(IZQUIERDA);
            break;
        default:;
    }

    if (input.game == TinputGame::KEY_ENTER){
        mSelectionConfirmed = true;
    }

    return mSelection;
}

bool MenuGameMode::selectionComplete() {
    return mSelectionConfirmed;
}
