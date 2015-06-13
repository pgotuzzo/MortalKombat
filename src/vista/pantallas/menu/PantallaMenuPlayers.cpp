#include "PantallaMenuPlayers.h"

const string PATH_BACKGROUND = "./resources/menus/seleccion_personajes/background.png";
const string PATH_SELECTOR_1 = "./resources/menus/seleccion_personajes/selector_1.png";
const string PATH_SELECTOR_2 = "./resources/menus/seleccion_personajes/selector_2.png";

const float RELATIVE_WIDTH = 0.15;
const float RELATIVE_HEIGHT = 0.30;
const float RELATIVE_HORIZONTAL_BOUND = 0.21;
const float RELATIVE_VERTICAL_BOUND = 0.09;

void PantallaMenuPlayers::InicializarPersonaje(Tpersonaje personaje,int index) {
    if (mUtils == nullptr) {
        loguer->loguear("No se pueden crear las vistas de los personajes sin antes inicializar SDL", Log::LOG_ERR);
        throw new exception;
    }

    mPersonajes[index] = PersonajeVista(mUtils, personaje.sprites, personaje.d, personaje.orientacion);
}

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
    filaPers1 = 0;
    filaPers2 = 0;
    mPersonajes[0].freeTextures();
    Tpersonaje personaje;
    personaje.d = Tdimension(25, 60);
    personaje.orientacion = DERECHA;
    personaje.sprites = "./resources/sprites/subzero";
    InicializarPersonaje(personaje,0);
    Tcambio cambio;
    cambio.posicion = Posicion(5,75);
    cambio.dPJ = personaje.d;
    cambio.estado = MOV_PARADO;
    cambio.direccion = DERECHA;
    cambio.sentido = ADELANTE;
    TcambioPoder poder;
    poder.e = DESACTIVADO;
    cambio.poder = (poder);
    mPersonajes[0].update( cambio);
    mPersonajes[1].freeTextures();
    personaje.d = Tdimension(25, 60);
    personaje.orientacion = IZQUIERDA;
    personaje.sprites = "./resources/sprites/subzero";
    InicializarPersonaje(personaje,1);
    cambio.posicion = Posicion(170,75);
    cambio.dPJ = personaje.d;
    cambio.estado = MOV_PARADO;
    cambio.direccion = IZQUIERDA;
    cambio.sentido = ADELANTE;
    poder.e = DESACTIVADO;
    cambio.poder = (poder);
    mPersonajes[1].update( cambio);
}

void PantallaMenuPlayers::update(vector<Posicion> players) {
    for (int i = 0; i < 2; i++) {
        //Posicion p = getPosition(players[i]);
        mRectSelector[i].p.x = mRectSelector[0].d.w * players[i].x + mTextBackground.d.w * RELATIVE_HORIZONTAL_BOUND;
        mRectSelector[i].p.y = mRectSelector[0].d.h * players[i].y + mTextBackground.d.h * RELATIVE_VERTICAL_BOUND;
    }
    // Al rico harcoding
    if (filaPers1 != players[0].y) {
        filaPers1 = players[0].y;
        mPersonajes[0].freeTextures();
        Tpersonaje personaje;
        personaje.d = Tdimension(25, 60);
        personaje.orientacion = DERECHA;
        switch (filaPers1){
            case 0: {
                personaje.sprites = "./resources/sprites/subzero";
                break;
            };
            case 1: {
                personaje.sprites = "./resources/sprites/ermac";
                break;
            };
            case 2: {
                personaje.sprites = "./resources/sprites/liukang";
                break;
            };
        }
        InicializarPersonaje(personaje,0);
        Tcambio cambio;
        cambio.posicion = Posicion(5,75);
        cambio.dPJ = personaje.d;
        cambio.estado = MOV_PARADO;
        cambio.direccion = DERECHA;
        cambio.sentido = ADELANTE;
        TcambioPoder poder;
        poder.e = DESACTIVADO;
        cambio.poder = (poder);
        mPersonajes[0].update( cambio);
    }
    if (filaPers2 != players[1].y) {
        filaPers2 = players[1].y;
        mPersonajes[1].freeTextures();
        Tpersonaje personaje;
        personaje.d = Tdimension(25, 60);
        personaje.orientacion = IZQUIERDA;
        switch (filaPers2){
            case 0: {
                 personaje.sprites = "./resources/sprites/subzero";
                break;
            };
            case 1: {
                personaje.sprites = "./resources/sprites/ermac";
                break;
            };
            case 2: {
                personaje.sprites = "./resources/sprites/liukang";
                break;
            };
        }
        InicializarPersonaje(personaje,1);
        Tcambio cambio;
        cambio.posicion = Posicion(170,75);
        cambio.dPJ = personaje.d;
        cambio.estado = MOV_PARADO;
        cambio.direccion = IZQUIERDA;
        cambio.sentido = ADELANTE;
        TcambioPoder poder;
        poder.e = DESACTIVADO;
        cambio.poder = (poder);
        mPersonajes[1].update( cambio);
    }
}

void PantallaMenuPlayers::print() {
    Ttexture ventana;
    ventana.t = SDL_GetRenderTarget(mRenderer);
    ventana.d = mDimension;

    mUtils->copyTexture(mTextBackground.t, ventana.t);
    mUtils->copyTexture(mTextSelector[0], ventana, NULL, &mRectSelector[0]);
    mUtils->copyTexture(mTextSelector[1], ventana, NULL, &mRectSelector[1]);

    for (unsigned i = 0; i < 2; i++)
        mPersonajes[i].getTexture(ventana, 0);

    SDL_RenderPresent(mRenderer);
}

PantallaMenuPlayers::~PantallaMenuPlayers() {
    SDL_DestroyTexture(mTextBackground.t);
    SDL_DestroyTexture(mTextSelector[0].t);
    SDL_DestroyTexture(mTextSelector[1].t);
    for (int i = 0; i < 2; i++)
        mPersonajes[i].freeTextures();
}
