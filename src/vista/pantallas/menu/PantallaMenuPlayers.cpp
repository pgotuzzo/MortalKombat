#include "PantallaMenuPlayers.h"

const string PATH_BACKGROUND = "./resources/menus/seleccion_personajes/background.png";
const string PATH_SELECTOR_1 = "./resources/menus/seleccion_personajes/selector_1.png";
const string PATH_SELECTOR_2 = "./resources/menus/seleccion_personajes/selector_2.png";

const float RELATIVE_WIDTH = 0.15;
const float RELATIVE_HEIGHT = 0.30;
const float RELATIVE_HORIZONTAL_BOUND = 0.21;
const float RELATIVE_VERTICAL_BOUND = 0.09;

const int MAX_CHARACTER_SHOWN = 12;

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

    EtipoPersonaje type = EtipoPersonaje::SUBZERO;
    TinfoPersonaje info = getInfoPersonaje(type);

    for (int i = 0; i < 2; i++) {
        mPlayers[i] = type;
        mNames[i] = info.defaulName;
        mPlayerViews[i] = PersonajeVista(mUtils, info.spritesPath, info.dimension, (i == 0) ? DERECHA : IZQUIERDA);
        mTextNames[i] = mUtils->createTextureFromText(FONT_PATH, mNames[i], FONT_SIZE);
    }

    mRectName[0].d = mTextNames[0].d;
    mRectName[0].p.x = 1;
    mRectName[0].p.y = mTextBackground.d.h - mTextNames[0].d.h;

    mRectName[1].d = mTextNames[1].d;
    mRectName[1].p.x = mTextBackground.d.w - RELATIVE_HORIZONTAL_BOUND * mTextBackground.d.w + 6;
    mRectName[1].p.y = mTextBackground.d.h - mTextNames[0].d.h;

    activateSecondPlayer = false;
}

void PantallaMenuPlayers::update(array<Posicion, 2> players, array<string, 2> names) {
    for (int i = 0; i < 2; i++) {
        Posicion p = players[i];
        if (p.x < 0 || p.y < 0) {
            // Si me llega una posicion negativa, no muestro dicho cuadro de seleccion.
            mRectSelector[i].p = Posicion(mTextBackground.d.w, mTextBackground.d.h);
        } else {
            // activo el segundo personaje cuando esto es necesario
            if( i == 1 )
                activateSecondPlayer = true;

            // actualizo la posicion de los selectores
            mRectSelector[i].p.x = mRectSelector[0].d.w * p.x + mTextBackground.d.w * RELATIVE_HORIZONTAL_BOUND;
            mRectSelector[i].p.y = mRectSelector[0].d.h * p.y + mTextBackground.d.h * RELATIVE_VERTICAL_BOUND;

            // actualizo el personaje seleccionado
            EtipoPersonaje type = getType(p);
            if (type != mPlayers[i]) {
                // si se eligio otro personaje, lo vuelvo a crear
                mPlayerViews[i].freeTextures();
                SDL_DestroyTexture(mTextNames[i].t);

                mPlayers[i] = type;
                TinfoPersonaje info = getInfoPersonaje(type);

                mTextNames[i] = mUtils->createTextureFromText(FONT_PATH, info.defaulName, FONT_SIZE);
                mRectName[i].d = mTextNames[i].d;

                mUtils->setColorSetting(info.colorSettings);
                mUtils->enableColorChange(true);
                mPlayerViews[i] = PersonajeVista(mUtils, info.spritesPath, info.dimension, (i == 0) ? DERECHA : IZQUIERDA);
                mUtils->enableColorChange(false);
            }
            // actualizo el estado del personaje para darle movimiento
            Tcambio cambio;
            cambio.dPJ = Tdimension(25, 60);
            cambio.estado = MOV_PARADO;
            cambio.sentido = ADELANTE;
            TcambioPoder poder;
            poder.e = DESACTIVADO;
            cambio.poder = (poder);

            if (i == 0){
                cambio.posicion = Posicion(5, mTextBackground.d.h - 60 - 10);
                cambio.direccion = DERECHA;
            } else {
                cambio.posicion =
                        Posicion(
                                mTextBackground.d.w - mPlayerViews[0].getRect().d.w - 5,
                                mTextBackground.d.h - 60 - 10
                        );
                cambio.direccion = IZQUIERDA;
            }
            mPlayerViews[i].update(cambio);

            // actualizo el texto
            if (names[i] != mNames[i]){
                SDL_DestroyTexture(mTextNames[i].t);
                string s = (names[i].length() > MAX_CHARACTER_SHOWN) ?
                           names[i].substr(names[i].length() - MAX_CHARACTER_SHOWN, MAX_CHARACTER_SHOWN) :
                           names[i];
                mTextNames[i] = mUtils->createTextureFromText(FONT_PATH, s, FONT_SIZE);
                mRectName[i].d = mTextNames[i].d;
            }
        }
    }
}

void PantallaMenuPlayers::print() {
    Ttexture ventana;
    ventana.t = SDL_GetRenderTarget(mRenderer);
    ventana.d = mDimension;

    mUtils->copyTexture(mTextBackground.t, ventana.t);
    mUtils->copyTexture(mTextSelector[0], ventana, NULL, &mRectSelector[0]);
    mUtils->copyTexture(mTextSelector[1], ventana, NULL, &mRectSelector[1]);

    mPlayerViews[0].getTexture(ventana, 0);
    mUtils->copyTexture(mTextNames[0], ventana, NULL, &mRectName[0]);
    if (activateSecondPlayer) {
        mPlayerViews[1].getTexture(ventana, 0);
        mUtils->copyTexture(mTextNames[1], ventana, NULL, &mRectName[1]);
    }

    SDL_RenderPresent(mRenderer);
}

Posicion PantallaMenuPlayers::getRelativePosition(Posicion p) {
    float horizontalBoundWidth = RELATIVE_HORIZONTAL_BOUND * mTextBackground.d.w;
    float verticalBoundWidth = RELATIVE_VERTICAL_BOUND * mTextBackground.d.h;
    if (    p.x < horizontalBoundWidth                          ||
            p.x > horizontalBoundWidth + mTextBackground.d.w    ||
            p.y < verticalBoundWidth                            ||
            p.y > verticalBoundWidth + mTextBackground.d.h
            )
        return Posicion(-1, -1);
    else {
        Posicion relativePosition =
                Posicion(
                        (int) ( (p.x - horizontalBoundWidth) / mTextSelector[0].d.w ),
                        (int) ( (p.y - verticalBoundWidth) / mTextSelector[0].d.h )
                );
        return relativePosition;
    }
}

PantallaMenuPlayers::~PantallaMenuPlayers() {
    SDL_DestroyTexture(mTextBackground.t);
    SDL_DestroyTexture(mTextSelector[0].t);
    SDL_DestroyTexture(mTextSelector[1].t);
    for (int i = 0; i < 2; i++)
        mPlayerViews[i].freeTextures();
}
