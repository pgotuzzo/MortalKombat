#include "MenuGameMode.h"

MenuGameMode::MenuGameMode() {
    mSelection = EmodeSelection::MULTIPLAYER;
    mSelectionConfirmed = false;
    seleccionandoConMouse = false;
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

    if (input.game == TinputGame::KEY_ENTER || input.accion == TinputAccion::KEY_PINIA_ALTA){
        mSelectionConfirmed = true;
    }

    return mSelection;
}


EmodeSelection MenuGameMode::update(Tinput input,Posicion coordenadasMouse,vector<Trect> modos) {

    if(dentroDelModo(coordenadasMouse,modos[0])){
        mSelection = EmodeSelection::MULTIPLAYER;
    }
    else if(dentroDelModo(coordenadasMouse,modos[1])){
        mSelection = EmodeSelection::ARCADE;
    }
    else if(dentroDelModo(coordenadasMouse,modos[2])){
        mSelection = EmodeSelection::PRACTICE;
    }

    else seleccionandoConMouse = false;

    if (input.game == TinputGame::CLICK_IZQ_MOUSE && seleccionandoConMouse){

        mSelectionConfirmed = true;
    }

    return mSelection;
}


bool MenuGameMode::selectionComplete() {
    return mSelectionConfirmed;
}


bool MenuGameMode::dentroDelModo(Posicion posMouse,Trect modo) {
    if (posMouse.x < (modo.p.x + modo.d.w) && (posMouse.x >= modo.p.x)) {
        if(posMouse.y >= modo.p.y){
            seleccionandoConMouse = true;
            return true;
        }
    }
    return false;
}
