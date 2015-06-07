#include "PantallaMenuPlayers.h"

const string PATH_BACKGROUND = "./resources/menus/seleccion_personajes/background.png";
const string PATH_SELECTOR_1 = "./resources/menus/seleccion_personajes/selector_1.png";
const string PATH_SELECTOR_2 = "./resources/menus/seleccion_personajes/selector_2.png";

const float RELATIVE_WIDTH = 0.31;
const float RELATIVE_HEIGHT = 0.4;

PantallaMenuPlayers::PantallaMenuPlayers(Tdimension dimPixels, Tdimension dimUl) : Pantalla(dimPixels, dimUl) {
    mTextBackground = mUtils->loadTexture(PATH_BACKGROUND);
    mTextBackground.d = dimUl;
    mTextSelector[0] = mUtils->loadTexture(PATH_SELECTOR_1);
    mTextSelector[0].d = {
            mTextBackground.d.w * RELATIVE_WIDTH,
            mTextBackground.d.h * RELATIVE_HEIGHT
    };
    mTextSelector[1] = mUtils->loadTexture(PATH_SELECTOR_2);
    mTextSelector[1].d = {
            mTextBackground.d.w * RELATIVE_WIDTH,
            mTextBackground.d.h * RELATIVE_HEIGHT
    };
    array<EtipoPersonaje, 2> initialPlayers = {
            EtipoPersonaje::SUBZERO,
            EtipoPersonaje::ERMAC
    };
//    update(initialPlayers);
}

void PantallaMenuPlayers::update(array<EtipoPersonaje, 2> players) {

}

void PantallaMenuPlayers::print() {

}

PantallaMenuPlayers::~PantallaMenuPlayers() {

}
