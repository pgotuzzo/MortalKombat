#include "MenuPlayerSelection.h"


MenuPlayerSelection::MenuPlayerSelection() {
    mSelectionConfirmed[0] = false;
    mSelectionConfirmed[1] = false;
    mSelection[0] = Posicion(0,0);
    mSelection[1] = Posicion(3,0);
    movimientoSelec = new Musica();
    seleccion = new Musica();
}

EtipoPersonaje MenuPlayerSelection::getType(Posicion p) {
    if (p.getX() == 0 && p.getY() == 0) return EtipoPersonaje::SUBZERO;
    else if (p.getX() == 1 && p.getY() == 0) return EtipoPersonaje::SUBZERO_GREEN;
    else if (p.getX() == 2 && p.getY() == 0) return EtipoPersonaje::SUBZERO_RED;
    else if (p.getX() == 3 && p.getY() == 0) return EtipoPersonaje::SUBZERO_YELLOW;
    else if (p.getX() == 0 && p.getY() == 1) return EtipoPersonaje::ERMAC;
    else if (p.getX() == 1 && p.getY() == 1) return EtipoPersonaje::ERMAC_BLUE;
    else if (p.getX() == 2 && p.getY() == 1) return EtipoPersonaje::ERMAC_GREEN;
    else if (p.getX() == 3 && p.getY() == 1) return EtipoPersonaje::ERMAC_YELLOW;
    else if (p.getX() == 0 && p.getY() == 2) return EtipoPersonaje::LIUKANG;
    else if (p.getX() == 1 && p.getY() == 2) return EtipoPersonaje::LIUKANG_BLUE;
    else if (p.getX() == 2 && p.getY() == 2) return EtipoPersonaje::LIUKANG_GREEN;
    else if (p.getX() == 3 && p.getY() == 2) return EtipoPersonaje::LIUKANG_YELLOW;
    else return EtipoPersonaje::SUBZERO;
}

void MenuPlayerSelection::updateSelection(TinputMovimiento movimiento,int jugador) {
    switch ( movimiento ){
        case TinputMovimiento::KEY_ABAJO:{
            movimientoSelec->selecciona();
            if (mSelection[jugador].y < ROWS-1)
                mSelection[jugador].y++;
            break;
        };
        case TinputMovimiento::KEY_ARRIBA:{
            movimientoSelec->selecciona();
            if (mSelection[jugador].y > 0)
                mSelection[jugador].y--;
            break;
        };
        case TinputMovimiento::KEY_DERECHA:{
            movimientoSelec->selecciona();
            if (mSelection[jugador].x < COLUMNS-1)
                mSelection[jugador].x++;
            break;
        };
        case TinputMovimiento::KEY_IZQUIERDA:{
            movimientoSelec->selecciona();
            if (mSelection[jugador].x > 0)
                mSelection[jugador].x--;
            break;
        };
        case TinputMovimiento::KEY_ARRIBA_DERECHA:{
            movimientoSelec->selecciona();
            if (mSelection[jugador].x < COLUMNS-1)
                mSelection[jugador].x++;
            if (mSelection[jugador].y > 0)
                mSelection[jugador].y--;
            break;
        };
        case TinputMovimiento::KEY_ARRIBA_IZQUIERDA:{
            movimientoSelec->selecciona();
            if (mSelection[jugador].x > 0)
                mSelection[jugador].x--;
            if (mSelection[jugador].y > 0)
                mSelection[jugador].y--;
            break;
        };
    }
}

vector<Posicion> MenuPlayerSelection::update(vector<Tinput> inputs) {
    TinputMovimiento movimiento1 = (mSelectionConfirmed[0]) ? TinputMovimiento::KEY_NADA : inputs.at(0).movimiento;
    TinputMovimiento movimiento2 = (mSelectionConfirmed[1]) ? TinputMovimiento::KEY_NADA : inputs.at(1).movimiento;

    updateSelection(movimiento1,0);

    if (inputs[0].accion == TinputAccion::KEY_PINIA_ALTA){
        seleccion->click();
        mSelectionConfirmed[0] = true;
        personajesElegidos[0] = this->getType(mSelection[0]);

    }
    if(mSelectionConfirmed[0]){
        updateSelection(movimiento2,1);
        if (inputs[1].accion == TinputAccion::KEY_PINIA_ALTA){
            seleccion->click();
            mSelectionConfirmed[1] = true;
            personajesElegidos[1] = this->getType(mSelection[1]);
        }
    }
    vector<Posicion> vector = { mSelection[0], mSelection[1]};

    return vector;
};


bool MenuPlayerSelection::selectionComplete() {
    return mSelectionConfirmed[0] && mSelectionConfirmed[1];
}

MenuPlayerSelection::~MenuPlayerSelection() {
    delete movimientoSelec;
    delete seleccion;
}
