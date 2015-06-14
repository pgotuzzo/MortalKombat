#include "MenuPlayerSelection.h"
#include <cstdlib>

MenuPlayerSelection::MenuPlayerSelection() {
    mSelectionConfirmed[0] = false;
    mSelectionConfirmed[1] = false;
    seleccionandoConMouse[0] = false;
    seleccionandoConMouse[1] = false;
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

vector<Posicion> MenuPlayerSelection::update(vector<Tinput> inputs, Posicion coordenadasMouse,vector<Trect> players) {

    if(!mSelectionConfirmed[0] && !mSelectionConfirmed[1]){
        actualizarSeleccion(coordenadasMouse,players,0);
        if (inputs[0].game == TinputGame::CLICK_IZQ_MOUSE && seleccionandoConMouse[0]){
            mSelectionConfirmed[0] = true;
            personajesElegidos[0] = this->getType(mSelection[0]);
        }
    }

    else if(mSelectionConfirmed[0] && !mSelectionConfirmed[1]){
        actualizarSeleccion(coordenadasMouse,players,1);
        if (inputs[0].game == TinputGame::CLICK_IZQ_MOUSE && seleccionandoConMouse[1]){
            mSelectionConfirmed[1] = true;
            personajesElegidos[1] = this->getType(mSelection[1]);
        }
    }

    return { mSelection[0], mSelection[1]};

}

vector<Posicion> MenuPlayerSelection::update(vector<Tinput> inputs) {
    TinputMovimiento movimiento1 = (mSelectionConfirmed[0]) ? TinputMovimiento::KEY_NADA : inputs.at(0).movimiento;
    TinputMovimiento movimiento2 = (mSelectionConfirmed[1]) ? TinputMovimiento::KEY_NADA : inputs.at(1).movimiento;


    if(!mSelectionConfirmed[0] && !mSelectionConfirmed[1]) {
        updateSelection(movimiento1, 0);

        if (inputs[0].accion == TinputAccion::KEY_PINIA_ALTA) {
            seleccion->click();
            mSelectionConfirmed[0] = true;
            personajesElegidos[0] = this->getType(mSelection[0]);

        }
    }
    else if(mSelectionConfirmed[0] && !mSelectionConfirmed[1]){
        updateSelection(movimiento2,1);
        if (inputs[1].accion == TinputAccion::KEY_PINIA_ALTA){
            seleccion->click();
            mSelectionConfirmed[1] = true;
            personajesElegidos[1] = this->getType(mSelection[1]);
        }
    }

    return { mSelection[0], mSelection[1]};
};


vector<Posicion> MenuPlayerSelection::updateConAleatorio(vector<Tinput> inputs) {
    TinputMovimiento movimiento1 = (mSelectionConfirmed[0]) ? TinputMovimiento::KEY_NADA : inputs.at(0).movimiento;

    if(!mSelectionConfirmed[0] && !mSelectionConfirmed[1]) {
        updateSelection(movimiento1, 0);

        if (inputs[0].accion == TinputAccion::KEY_PINIA_ALTA) {
            seleccion->click();
            mSelectionConfirmed[0] = true;
            personajesElegidos[0] = this->getType(mSelection[0]);
        }
    }
    else if(mSelectionConfirmed[0] && !mSelectionConfirmed[1]){
        mSelection[1] = Posicion(rand() % 4,rand() %3);
        personajesElegidos[1] = this->getType(mSelection[1]);
        mSelectionConfirmed[1] = true;
    }

    return { mSelection[0], mSelection[1]};
}


vector<Posicion> MenuPlayerSelection::updateConAleatorio(vector<Tinput> inputs, Posicion coordenadasMouse,vector<Trect> players) {
    if(!mSelectionConfirmed[0] && !mSelectionConfirmed[1]){
        actualizarSeleccion(coordenadasMouse,players,0);
        if (inputs[0].game == TinputGame::CLICK_IZQ_MOUSE && seleccionandoConMouse[0]){
            mSelectionConfirmed[0] = true;
            personajesElegidos[0] = this->getType(mSelection[0]);
        }
    }
    else if(mSelectionConfirmed[0] && !mSelectionConfirmed[1]){
        int y = rand() % 3;
        if(y == mSelection[0].y){
            if(y == 0) y++;
            else if (y==1) y++;
            else y--;
        }
        mSelection[1] = Posicion(rand() % 4,y);
        personajesElegidos[1] = this->getType(mSelection[1]);
        mSelectionConfirmed[1] = true;
    }

    return { mSelection[0], mSelection[1]};
}

bool MenuPlayerSelection::selectionComplete() {
    return mSelectionConfirmed[0] && mSelectionConfirmed[1];
}

MenuPlayerSelection::~MenuPlayerSelection() {
    delete movimientoSelec;
    delete seleccion;
}

bool MenuPlayerSelection::dentroDeUnPlayer(Posicion posMouse,Trect player,int jugador) {

    if (posMouse.x < (player.p.x + player.d.w) && (posMouse.x >= player.p.x)) {
        if(posMouse.y >= player.p.y && posMouse.y < (player.p.y + player.d.h)){
            seleccionandoConMouse[jugador] = true;
            return true;
        }
    }
    return false;
}

void MenuPlayerSelection::actualizarSeleccion(Posicion coordenadasMouse, vector<Trect> players, int jugador) {

    if(dentroDeUnPlayer(coordenadasMouse,players[0],jugador)) mSelection[jugador] = Posicion(0,0);
    else if(dentroDeUnPlayer(coordenadasMouse,players[1],jugador)) mSelection[jugador] = Posicion(1,0);
    else if(dentroDeUnPlayer(coordenadasMouse,players[2],jugador)) mSelection[jugador] = Posicion(2,0);
    else if(dentroDeUnPlayer(coordenadasMouse,players[3],jugador)) mSelection[jugador] = Posicion(3,0);
    else if(dentroDeUnPlayer(coordenadasMouse,players[4],jugador)) mSelection[jugador] = Posicion(0,1);
    else if(dentroDeUnPlayer(coordenadasMouse,players[5],jugador)) mSelection[jugador] = Posicion(1,1);
    else if(dentroDeUnPlayer(coordenadasMouse,players[6],jugador)) mSelection[jugador] = Posicion(2,1);
    else if(dentroDeUnPlayer(coordenadasMouse,players[7],jugador)) mSelection[jugador] = Posicion(3,1);
    else if(dentroDeUnPlayer(coordenadasMouse,players[8],jugador)) mSelection[jugador] = Posicion(0,2);
    else if(dentroDeUnPlayer(coordenadasMouse,players[9],jugador)) mSelection[jugador] = Posicion(1,2);
    else if(dentroDeUnPlayer(coordenadasMouse,players[10],jugador)) mSelection[jugador] = Posicion(2,2);
    else if(dentroDeUnPlayer(coordenadasMouse,players[11],jugador)) mSelection[jugador] = Posicion(3,2);

    else seleccionandoConMouse[jugador] = false;
}

