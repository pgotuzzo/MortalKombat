#include "PantallaMenuModoJuego.h"

const string PATH_BACKGROUND = "./resources/menus/menu_principal/background.png";
const string PATH_SELECTOR = "./resources/menus/menu_principal/selector.png";

const float RELATIVE_WIDTH = 0.31;
const float RELATIVE_HEIGHT = 0.4;

PantallaMenuModoJuego::PantallaMenuModoJuego(Tdimension dimPixels, Tdimension dimUl) : Pantalla(dimPixels,dimUl) {
    mTextBackground = mUtils->loadTexture(PATH_BACKGROUND);
    mTextBackground.d = dimUl;
    mTextSelector = mUtils->loadTexture(PATH_SELECTOR);
    mTextSelector.d = {
            mTextBackground.d.w * RELATIVE_WIDTH,
            mTextBackground.d.h * RELATIVE_HEIGHT
    };
    update(EmodeSelection::MULTIPLAYER);
};

void PantallaMenuModoJuego::update(EmodeSelection mode) {
    mRectSelector.d = mTextSelector.d;
    mRectSelector.p.y = mTextBackground.d.h - mTextSelector.d.h;
    switch (mode){
        case EmodeSelection::MULTIPLAYER:
            mRectSelector.p.x = 0;
            break;
        case EmodeSelection::ARCADE:
            mRectSelector.p.x = mTextBackground.d.w / 2 - mTextSelector.d.w / 2;
            break;
        case EmodeSelection::PRACTICE:
            mRectSelector.p.x = mTextBackground.d.w - mTextSelector.d.w;
            break;
    }
}

void PantallaMenuModoJuego::print() {
    Ttexture ventana;
    ventana.t = SDL_GetRenderTarget(mRenderer);
    ventana.d = mDimension;

    mUtils->copyTexture(mTextBackground.t, ventana.t);
    mUtils->copyTexture(mTextSelector, ventana, NULL, &mRectSelector);

    SDL_RenderPresent(mRenderer);
}

PantallaMenuModoJuego::~PantallaMenuModoJuego() {
    SDL_DestroyTexture(mTextBackground.t);
    SDL_DestroyTexture(mTextSelector.t);
}

vector<Trect> PantallaMenuModoJuego::getCuadradoModos() {
    Trect primerModo, segundoModo, tercerModo;

    primerModo.d = mTextSelector.d;
    segundoModo.d = mTextSelector.d;
    tercerModo.d = mTextSelector.d;

    primerModo.p.y = mTextBackground.d.h - mTextSelector.d.h;
    segundoModo.p.y = mTextBackground.d.h - mTextSelector.d.h;
    tercerModo.p.y = mTextBackground.d.h - mTextSelector.d.h;

    primerModo.p.x = 0;
    segundoModo.p.x = mTextBackground.d.w / 2 - mTextSelector.d.w / 2;
    tercerModo.p.x = mTextBackground.d.w - mTextSelector.d.w;

    vector<Trect> modos;
    modos.push_back(primerModo);
    modos.push_back(segundoModo);
    modos.push_back(tercerModo);

    return modos;

}
