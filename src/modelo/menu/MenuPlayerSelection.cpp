#include "MenuPlayerSelection.h"

MenuPlayerSelection::MenuPlayerSelection() {
    mState = State::PLAYER_1_CHARACTER;
    mMusic = new Musica();
    mSelection[0] = Posicion(0,0);
    mSelection[1] = Posicion(-1,-1);
}

bool MenuPlayerSelection::selectionComplete() {
    return mState == State::COMPLETE ;
}

bool MenuPlayerSelection::firstPlayerSelected() {
    return mState == State::PLAYER_2_CHARACTER;
}

TmenuPlayerChanges MenuPlayerSelection::update(Tinput inputs, Posicion mouse) {
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
                mState = State::PLAYER_1_NAME;
            }
            // actualizo el nombre
            mNames[0] = getInfoPersonaje(getType(mSelection[0])).defaulName;
            break;
        }
        case State::PLAYER_1_NAME:
            if (inputs.game == TinputGame::KEY_ENTER){
                mState = State::PLAYER_2_CHARACTER;
                mSelection[1] = Posicion(0, 0);
            } else if (inputs.letras.recibe){
                if (inputs.letras.borrado) {
                    if (mNames[0].size() > 0) {
                        mNames[0] = (mNames[0].size() == 1) ?
                                    "" :
                                    mNames[0].substr(0, mNames[0].size() - 1);
                    }
                } else if (mNames[0].size() < MAX_LENGTH) {
                    mNames[0] = mNames[0] + inputs.letras.letra;
                }
            }
            break;
        case State::PLAYER_2_CHARACTER:{
            // muevo el cuadro de seleccion
            if ( updateSelectionKeyboard(inputs.movimiento, 1) || updateSelectionMouse(mouse, 1) )
                mMusic->selecciona();

            // verifico los clicks/enters
            if (    inputs.game == TinputGame::KEY_ENTER ||
                    ( inputs.game == TinputGame::CLICK_IZQ_MOUSE && mouse == mSelection[1] )
                    ) {
                mMusic->click();
                mState = State::PLAYER_2_NAME;
            }
            // actualizo el nombre
            mNames[1] = getInfoPersonaje(getType(mSelection[1])).defaulName;
            break;
        };
        case State::PLAYER_2_NAME:
            if (inputs.game == TinputGame::KEY_ENTER){
                mState = State::COMPLETE;;
            } else if (inputs.letras.recibe){
                if (inputs.letras.borrado) {
                    if (mNames[1].size() > 0) {
                        mNames[1] = (mNames[1].size() == 1) ?
                                    "" :
                                    mNames[1].substr(0, mNames[1].size() - 1);
                    }
                } else if (mNames[1].size() < MAX_LENGTH) {
                    mNames[1] = mNames[1] + inputs.letras.letra;
                }
            }
            break;

        default:;
    };

    // creo la variable de retorno
    TmenuPlayerChanges changes;
    changes.positions = mSelection;
    changes.names = mNames;

    return changes;
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