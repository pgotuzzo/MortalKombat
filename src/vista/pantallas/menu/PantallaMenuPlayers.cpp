#include "PantallaMenuPlayers.h"

const string PATH_BACKGROUND = "./resources/menus/seleccion_personajes/background.png";
const string PATH_SELECTOR_1 = "./resources/menus/seleccion_personajes/selector_1.png";
const string PATH_SELECTOR_2 = "./resources/menus/seleccion_personajes/selector_2.png";

const float RELATIVE_WIDTH = 0.15;
const float RELATIVE_HEIGHT = 0.30;
const float RELATIVE_HORIZONTAL_BOUND = 0.21;
const float RELATIVE_VERTICAL_BOUND = 0.09;

PantallaMenuPlayers::PantallaMenuPlayers(Tdimension dimPixels, Tdimension dimUl) : Pantalla(dimPixels, dimUl) {
    mTextBackground = mUtils->loadTexture(PATH_BACKGROUND);
    mTextBackground.d = dimUl;
    mTextSelector[0] = mUtils->loadTexture(PATH_SELECTOR_1);
    mTextSelector[0].d = {
            mTextBackground.d.w * RELATIVE_WIDTH,
            mTextBackground.d.h * RELATIVE_HEIGHT
    };
    mRectSelector[0].d = mTextSelector[0].d;
    mTextSelector[1] = mUtils->loadTexture(PATH_SELECTOR_2);
    mTextSelector[1].d = {
            mTextBackground.d.w * RELATIVE_WIDTH,
            mTextBackground.d.h * RELATIVE_HEIGHT
    };
    mRectSelector[1].d = mTextSelector[1].d;
}

void PantallaMenuPlayers::update(vector<Posicion> players) {
    for (int i = 0; i < 2; i++ ){
        //Posicion p = getPosition(players[i]);
        mRectSelector[i].p.x = mRectSelector[0].d.w * players[i].x + mTextBackground.d.w * RELATIVE_HORIZONTAL_BOUND;
        mRectSelector[i].p.y = mRectSelector[0].d.h * players[i].y + mTextBackground.d.h * RELATIVE_VERTICAL_BOUND;
    }
}

void PantallaMenuPlayers::print() {
    Ttexture ventana;
    ventana.t = SDL_GetRenderTarget(mRenderer);
    ventana.d = mDimension;

    mUtils->copyTexture(mTextBackground.t, ventana.t);
    mUtils->copyTexture(mTextSelector[0], ventana, NULL, &mRectSelector[0]);
    mUtils->copyTexture(mTextSelector[1], ventana, NULL, &mRectSelector[1]);

    SDL_RenderPresent(mRenderer);
}

PantallaMenuPlayers::~PantallaMenuPlayers() {
    SDL_DestroyTexture(mTextBackground.t);
    SDL_DestroyTexture(mTextSelector[0].t);
    SDL_DestroyTexture(mTextSelector[1].t);
}

vector<Trect> PantallaMenuPlayers::getCuadradoPlayers() {
    vector<Trect> players;
    for(int i = 0;i<3;i++){
        for(int j = 0;j<4;j++){
            Trect player;
            player.d.w = mTextBackground.d.w * RELATIVE_WIDTH;
            player.d.h = mTextBackground.d.h * RELATIVE_HEIGHT;
            player.p.x = mRectSelector[0].d.w * j + mTextBackground.d.w * RELATIVE_HORIZONTAL_BOUND;
            player.p.y = mRectSelector[0].d.h * i + mTextBackground.d.h * RELATIVE_VERTICAL_BOUND;
            players.push_back(player);
        }
    }
    return players;
}
