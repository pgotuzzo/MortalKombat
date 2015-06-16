#include "MenuPlayerSelection.h"

MenuPlayerSelection::MenuPlayerSelection() {
    mState = State::PLAYER_1_CHARACTER;
    mMusic = new Musica();
    mSelection[0] = Posicion(0,0);
    mSelection[1] = Posicion(-1,-1);

//    seleccionandoConMouse[0] = false;
//    seleccionandoConMouse[1] = false;

}

bool MenuPlayerSelection::selectionComplete() {
    return mState == State::COMPLETE ;
}

bool MenuPlayerSelection::firstPlayerSelected() {
    return mState == State::PLAYER_2_CHARACTER;
}

array<Posicion, 2> MenuPlayerSelection::update(Tinput inputs, Posicion mouse) {
    switch (mState){
        case State::PLAYER_1_CHARACTER: {
            // muevo el cuadro de seleccion
            if ( updateSelectionKeyboard(inputs.movimiento, 0) || updateSelectionMouse(mouse, 0) )
                mMusic->selecciona();

            // verifico los clicks/enters
            if (    inputs.game == TinputGame::KEY_ENTER ||
                    ( inputs.game == TinputGame::CLICK_IZQ_MOUSE && mouse == mSelection[0] )
                    ) {
                mMusic->click();
                mNames[0] = getInfoPersonaje(getType(mSelection[0])).defaulName;
                mState = State::PLAYER_1_NAME;
            }
            break;
        }
        case State::PLAYER_1_NAME:
//            switch (inputs.)
//                mNames[0]
            mState = State::PLAYER_2_CHARACTER;
            mSelection[1] = Posicion(0, 0);
            break;
        case State::PLAYER_2_CHARACTER:{
            // muevo el cuadro de seleccion
            if (    updateSelectionKeyboard(inputs.movimiento, 1) || updateSelectionMouse(mouse, 1) )
                mMusic->selecciona();

            // verifico los clicks/enters
            if (    inputs.game == TinputGame::KEY_ENTER ||
                    ( inputs.game == TinputGame::CLICK_IZQ_MOUSE && mouse == mSelection[1] )
                    ) {
                mMusic->click();
                mState = State::PLAYER_2_NAME;
            }
            break;
        };
        case State::PLAYER_2_NAME:
            mState = State::COMPLETE;
            break;
        default:;
    };
    return mSelection;
}

bool MenuPlayerSelection::updateSelectionKeyboard(TinputMovimiento movimiento, int jugador) {
    bool changed = false;

    switch ( movimiento ){
        case TinputMovimiento::KEY_ABAJO:{
            if (mSelection[jugador].y < ROWS-1){
                mSelection[jugador].y++;
                changed = true;
            }
            break;
        };
        case TinputMovimiento::KEY_ARRIBA:{
            mMusic->selecciona();
            if (mSelection[jugador].y > 0){
                mSelection[jugador].y--;
                changed = true;
            }
            break;
        };
        case TinputMovimiento::KEY_DERECHA:{
            if (mSelection[jugador].x < COLUMNS-1){
                mSelection[jugador].x++;
                changed = true;
            }
            break;
        };
        case TinputMovimiento::KEY_IZQUIERDA:{
            if (mSelection[jugador].x > 0){
                mSelection[jugador].x--;
                changed = true;
            }
            break;
        };
        case TinputMovimiento::KEY_ARRIBA_DERECHA:{
            if (mSelection[jugador].x < COLUMNS-1) {
                mSelection[jugador].x++;
                changed = true;
            }
            if (mSelection[jugador].y > 0){
                mSelection[jugador].y--;
                changed = true;
            }
            break;
        };
        case TinputMovimiento::KEY_ARRIBA_IZQUIERDA:{
            if (mSelection[jugador].x > 0) {
                mSelection[jugador].x--;
                changed = true;
            }
            if (mSelection[jugador].y > 0){
                mSelection[jugador].y--;
                changed = true;
            }
            break;
        };
        default:;
    }
    return changed;
}

bool MenuPlayerSelection::updateSelectionMouse(Posicion mousePosition, int jugador) {
    if (    mousePosition.x < 0             ||
            mousePosition.y < 0             ||
            mousePosition.x > COLUMNS  - 1  ||
            mousePosition.y > ROWS - 1      ||
            mousePosition == mSelection[jugador]
            )
        return false;
    else {
        mSelection[jugador] = mousePosition;
        return true;
    }
}

MenuPlayerSelection::~MenuPlayerSelection() {
    delete mMusic;
}


/* SE COMENTA POR SI SE LLEGA A NECESITAR ALGO DE LA LOGICA QUE HAY...PERO EN LO QUE HICE NO SE USA

vector<Posicion> MenuPlayerSelection::update(vector<Tinput> inputs, Posicion coordenadasMouse, vector<Trect> players) {

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
        updateSelectionKeyboard(movimiento1, 0);

        if (inputs[0].accion == TinputAccion::KEY_PINIA_ALTA) {
            mMusic->click();
            mSelectionConfirmed[0] = true;
            personajesElegidos[0] = this->getType(mSelection[0]);

        }
    }
    else if(mSelectionConfirmed[0] && !mSelectionConfirmed[1]){
        updateSelectionKeyboard(movimiento2,1);
        if (inputs[1].accion == TinputAccion::KEY_PINIA_ALTA){
            mMusic->click();
            mSelectionConfirmed[1] = true;
            personajesElegidos[1] = this->getType(mSelection[1]);
        }
    }

    return { mSelection[0], mSelection[1]};
};


vector<Posicion> MenuPlayerSelection::updateConAleatorio(vector<Tinput> inputs) {
    TinputMovimiento movimiento1 = (mSelectionConfirmed[0]) ? TinputMovimiento::KEY_NADA : inputs.at(0).movimiento;

    if(!mSelectionConfirmed[0] && !mSelectionConfirmed[1]) {
        updateSelectionKeyboard(movimiento1, 0);

        if (inputs[0].accion == TinputAccion::KEY_PINIA_ALTA) {
            mMusic->click();
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
*/
