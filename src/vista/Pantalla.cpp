#include "Pantalla.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
 * Crea los objectos referentes a SDL:
 * - Window
 * - Renderer
 * - VistaUtils
 *
 * d    Dimensiones en pixeles
 */
void Pantalla::InicializarSdl(Tdimension d) {
    loguer->loguear("Inicia SDL", Log::LOG_DEB);
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        loguer->loguear("Fallo la inicializacion de SDL.", Log::LOG_ERR);

    mWindow = SDL_CreateWindow("MortalKombat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, d.w, d.h, SDL_WINDOW_SHOWN);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

    float scales[2] = {d.w / mDimension.w, d.h / mDimension.h};
    mUtils = new VistaUtils(mRenderer, mDimension.w / mDimension.h, scales);
}

/**
 * Crea los personjaes
 *
 * \observacion Para que se puedan inicializar los personajes, previamente se tuvo que inicializar los
 *              componentes de SDL (mUtils)
 */
void Pantalla::InicializarPersonajes(vector<Tpersonaje> personajes) {
    if (mUtils == nullptr){
        loguer->loguear("No se pueden crear las vistas de los personajes sin antes inicializar SDL", Log::LOG_ERR);
        throw new exception;
    }

    // zIndex y ancho del personaje igual para ambos personajes
    zIndex = personajes[0].zIndex;
    mAnchoPersonaje = personajes[0].d.w;

    for (unsigned i = 0; i < personajes.size(); i++) {
        PersonajeVista p = PersonajeVista(mUtils, personajes[i].sprites, personajes[i].d, personajes[i].orientacion);
        mPersonajes.push_back(p);
    }
}

/**
 * Crea las capas
 *
 * \observacion Para que se puedan inicializar las capas, previamente se tuvo que inicializar los
 *              componentes de SDL (mUtils)
 */
void Pantalla::InicializarCapas(vector<Tcapa> capas) {
    if (mUtils == nullptr){
        loguer->loguear("No se pueden crear las vistas de las capas sin antes inicializar SDL", Log::LOG_ERR);
        throw new exception;
    }

    for (int i = 0; i < capas.size(); i++){
        Trect rect;
        rect.d = mDimension;
        rect.p.x = (capas[i].ancho - mDimension.w)/2;
        rect.p.y = 0;
        Capa capa = Capa(mUtils, capas[i].dirCapa, rect, capas[i].ancho, mAnchoEscenario);
        mCapas.push_back(capa);
    }
}

/*
 * Crea una pantalla.
 * capas : formato de cada capa.
 * ventana : formato de ventana.
 * escenario : formato del escenario.
 * personaje : formato del personaje.
 */
Pantalla::Pantalla(vector<Tcapa> capas, Tventana ventana, Tescenario escenario, vector<Tpersonaje> personajes) {
	mDimension = {ventana.ancho, escenario.d.h};
    mAnchoEscenario = escenario.d.w;
    posEscenario = ( mAnchoEscenario - mDimension.w ) / 2;
    distTope = ventana.distTope;

    // SDL
    InicializarSdl(ventana.dimPx);

    // Personajes
    InicializarPersonajes(personajes);

    // Capas
    InicializarCapas(capas);
};

/*
 * Dibuja todos los objetos en pantalla.
 */
void Pantalla::dibujar() {

    SDL_Texture* ventana = SDL_GetRenderTarget(mRenderer);

    for (int i = 0; i < mCapas.size(); i++) {
        mCapas[i].getTexture(ventana);
        if (i == zIndex) {
            for (unsigned i = 0; i < mPersonajes.size(); i++)
               mPersonajes[i].getTexture(ventana, posEscenario);
        }
    }
    SDL_RenderPresent(mRenderer);

}

/*
 * Actualiza todos los objetos de pantalla.
 * change : contiene los cambios a realizar.
 */
void Pantalla::update(vector<Tcambio> changes) {
    for (unsigned i = 0; i < mPersonajes.size(); i++)
        mPersonajes[i].update(changes[i]);

    // Se tienen en cuenta solo los primeros 2 personajes para modificar la posicion del escenario
    float posPersonaje1X = changes[0].posicion.x;
    float posPersonaje2X = changes[1].posicion.x;
    float topeDerecha = posEscenario + mDimension.w - distTope;
    float topeIzquierda = posEscenario + distTope;
    bool moverIzq1 = topeIzquierda > posPersonaje1X && posPersonaje1X-distTope> 0;
    bool moverIzq2 = topeIzquierda > posPersonaje2X && posPersonaje2X-distTope> 0;
    bool moverDer1 = posPersonaje1X + mAnchoPersonaje > topeDerecha && posPersonaje1X + mAnchoPersonaje + distTope < mAnchoEscenario;
    bool moverDer2 = posPersonaje2X + mAnchoPersonaje > topeDerecha && posPersonaje2X + mAnchoPersonaje + distTope < mAnchoEscenario;
    if (moverIzq1) {
        posEscenario = posPersonaje1X - distTope;
    } else if (moverIzq2) {
        posEscenario = posPersonaje2X - distTope;
    } else if (moverDer1) {
        posEscenario = posPersonaje1X + mAnchoPersonaje + distTope - mDimension.w;
    } else if (moverDer2) {
        posEscenario = posPersonaje2X + mAnchoPersonaje + distTope - mDimension.w;
    }

    for (int i = 0; i < mCapas.size(); i++) {
        mCapas[i].ajustar(posEscenario);
    }
}


Pantalla::~Pantalla() {
    loguer->loguear("Destruccion de la pantalla", Log::LOG_DEB);
    for (int i = 0; i < mCapas.size(); i++)
        mCapas[i].freeTextures();
    for (int i = 0; i < mPersonajes.size(); i++)
        mPersonajes[i].freeTextures();
    delete (mUtils);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    loguer->loguear("Cierra SDL", Log::LOG_DEB);
    SDL_Quit();
    IMG_Quit();
}

