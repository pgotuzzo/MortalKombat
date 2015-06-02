#include "PantallaMultiplayer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

const float distVibracion = 5;

/**
 * Crea los personjaes
 *
 * \observacion Para que se puedan inicializar los personajes, previamente se tuvo que inicializar los
 *              componentes de SDL (mUtils)
 */
void PantallaMultiplayer::InicializarPersonajes(vector<Tpersonaje> personajes) {
    if (mUtils == nullptr){
        loguer->loguear("No se pueden crear las vistas de los personajes sin antes inicializar SDL", Log::LOG_ERR);
        throw new exception;
    }

    // zIndex y igual para ambos personajes
    zIndex = personajes[0].zIndex;

    // Personaje 1
    PersonajeVista p = PersonajeVista(mUtils, personajes[0].sprites, personajes[0].d, personajes[0].orientacion);
    mPersonajes.push_back(p);

    // Personaje 2
    if (personajes[1].sprites == personajes[0].sprites){
        mUtils->setColorSetting(personajes.at(1).colorSettings);
        mUtils->enableColorChange(true);
        p = PersonajeVista(mUtils, personajes[1].sprites, personajes[1].d, personajes[1].orientacion);
        mUtils->enableColorChange(false);
    }else{
        p = PersonajeVista(mUtils, personajes[1].sprites, personajes[1].d, personajes[1].orientacion);
    }
    mPersonajes.push_back(p);

}

/**
 * Crea las capas
 *
 * \observacion Para que se puedan inicializar las capas, previamente se tuvo que inicializar los
 *              componentes de SDL (mUtils)
 */
void PantallaMultiplayer::InicializarCapas(vector<Tcapa> capas, string personajes[2]) {
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

    capaInfo = CapaInfo(mUtils, mDimension, personajes);
}

/*
 * Crea una pantalla.
 * capas : formato de cada capa.
 * ventana : formato de ventana.
 * escenario : formato del escenario.
 * personaje : formato del personaje.
 */
PantallaMultiplayer::PantallaMultiplayer(vector<Tcapa> capas, Tventana ventana,
                                             Tescenario escenario, vector<Tpersonaje> personajes)
        : Pantalla(ventana.dimPx, Tdimension(ventana.ancho, escenario.d.h)) {

    mAnchoEscenario = escenario.d.w;
    posEscenario = ( mAnchoEscenario - mDimension.w ) / 2;
    distTope = ventana.distTope;

    // Personajes
    InicializarPersonajes(personajes);

    // Capas
    string nombres[2] = {personajes[0].nombre, personajes[1].nombre};
    InicializarCapas(capas, nombres);
    vibroADerecha = false;
};

/*
 * Dibuja todos los objetos en pantalla.
 */
void PantallaMultiplayer::print() {

    Ttexture ventana;
    ventana.t = SDL_GetRenderTarget(mRenderer);
    ventana.d = mDimension;

    for (int i = 0; i < mCapas.size(); i++) {
        mCapas[i].getTexture(ventana);
        if (i == zIndex) {
            for (unsigned i = 0; i < mPersonajes.size(); i++)
               mPersonajes[i].getTexture(ventana, posEscenario);
        }
    }
    capaInfo.getTexture(ventana);
    SDL_RenderPresent(mRenderer);

}

/*
 * Actualiza todos los objetos de pantalla.
 * change : contiene los cambios a realizar.
 */
void PantallaMultiplayer::update(vector<Tcambio> changes) {
    for (unsigned i = 0; i < mPersonajes.size(); i++){
        if (mPersonajes[i].update(changes[i]))
            this->vibrar();
    }

    // Se tienen en cuenta solo los primeros 2 personajes para modificar la posicion del escenario
    float posPersonaje1X = changes[0].posicion.x;
    float posPersonaje2X = changes[1].posicion.x;
    float topeDerecha = posEscenario + mDimension.w - distTope;
    float topeIzquierda = posEscenario + distTope;
    float anchoPersonaje1 = mPersonajes[0].getRect().d.w;
    float anchoPersonaje2 = mPersonajes[1].getRect().d.w;
    bool moverIzq1 = topeIzquierda > posPersonaje1X && posPersonaje1X - distTope > 0;
    bool moverIzq2 = topeIzquierda > posPersonaje2X && posPersonaje2X - distTope > 0;
    bool moverDer1 = posPersonaje1X + anchoPersonaje1 > topeDerecha &&
                     posPersonaje1X + anchoPersonaje1 + distTope < mAnchoEscenario;
    bool moverDer2 = posPersonaje2X + anchoPersonaje2 > topeDerecha &&
                     posPersonaje2X + anchoPersonaje2 + distTope < mAnchoEscenario;
    if (moverIzq1) {
        posEscenario = posPersonaje1X - distTope;
    } else if (moverIzq2) {
        posEscenario = posPersonaje2X - distTope;
    } else if (moverDer1) {
        posEscenario = posPersonaje1X + anchoPersonaje1 + distTope - mDimension.w;
    } else if (moverDer2) {
        posEscenario = posPersonaje2X + anchoPersonaje2 + distTope - mDimension.w;
    }

    for (int i = 0; i < mCapas.size(); i++) {
        mCapas[i].ajustar(posEscenario);
    }

    capaInfo.update(changes[0].vida/100,changes[1].vida/100);
}

void PantallaMultiplayer::vibrar(){
    if (vibroADerecha) {
        posEscenario = posEscenario - distVibracion;
        vibroADerecha = false;
    } else {
        posEscenario = posEscenario + distVibracion;
        vibroADerecha = true;
    }
}

PantallaMultiplayer::~PantallaMultiplayer() {
    loguer->loguear("Destruccion de la pantalla", Log::LOG_DEB);
    for (int i = 0; i < mCapas.size(); i++)
        mCapas[i].freeTextures();
    capaInfo.freeTextures();
    for (int i = 0; i < mPersonajes.size(); i++)
        mPersonajes[i].freeTextures();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    loguer->loguear("Cierra SDL", Log::LOG_DEB);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
