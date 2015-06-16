#include "MenuGameMode.h"

MenuGameMode::MenuGameMode() {
    mSelection = EmodeSelection::MULTIPLAYER;
    mSelectionConfirmed = false;
    seleccionandoConMouse = false;
    select = new Musica();
    click = new Musica();
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

void MenuGameMode::update(Tinput input) {
    if(!mSelectionConfirmed) {
        switch (input.movimiento) {
            case TinputMovimiento::KEY_DERECHA:
            case TinputMovimiento::KEY_ARRIBA_DERECHA:
                select->selecciona();
                updateSelection(DERECHA);
                break;
            case TinputMovimiento::KEY_IZQUIERDA:
            case TinputMovimiento::KEY_ARRIBA_IZQUIERDA:
                select->selecciona();
                updateSelection(IZQUIERDA);
                break;
            default:;
        }

        if (input.game == TinputGame::KEY_ENTER || input.accion == TinputAccion::KEY_PINIA_ALTA) {
            click->clickConDelay();
            mSelectionConfirmed = true;
        }
    }
}


void MenuGameMode::update(Tinput input,Posicion coordenadasMouse,vector<Trect> modos) {

    if(!mSelectionConfirmed) {
        if (dentroDelModo(coordenadasMouse, modos[0])) {
            if (mSelection != EmodeSelection::MULTIPLAYER)
                select->selecciona();
            mSelection = EmodeSelection::MULTIPLAYER;

        }
        else if (dentroDelModo(coordenadasMouse, modos[1])) {
            if (mSelection != EmodeSelection::ARCADE)
                select->selecciona();
            mSelection = EmodeSelection::ARCADE;

        }
        else if (dentroDelModo(coordenadasMouse, modos[2])) {

            if (mSelection != EmodeSelection::PRACTICE)
                select->selecciona();

            mSelection = EmodeSelection::PRACTICE;

        }

        else seleccionandoConMouse = false;

        if (input.game == TinputGame::CLICK_IZQ_MOUSE && seleccionandoConMouse) {
            click->clickConDelay();
            mSelectionConfirmed = true;
        }
    }
}

EmodeSelection MenuGameMode::getSelection() {
    return mSelection;
}

bool MenuGameMode::selectionComplete() {
    return mSelectionConfirmed;
}


bool MenuGameMode::dentroDelModo(Posicion posMouse, Trect modo) {
    if (posMouse.x < (modo.p.x + modo.d.w) && (posMouse.x >= modo.p.x)) {
        if(posMouse.y >= modo.p.y){
            seleccionandoConMouse = true;
            return true;
        }
    }
    return false;
}

MenuGameMode::~MenuGameMode() {
    delete select;
    delete click;
}
