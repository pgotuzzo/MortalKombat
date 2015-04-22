#include "Pantalla.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
 * Se inicia la ventana y el renderer.
 */
void Pantalla::Inicializar(int anchoPx,int altoPx) {
    loguer->loguear("Inicia SDL", Log::LOG_DEB);
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        loguer->loguear("Fallo la inicializacion de SDL.", Log::LOG_ERR);

    mWindow = SDL_CreateWindow("MortalKombat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, anchoPx, altoPx, SDL_WINDOW_SHOWN);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
}

/*
 * Crea una pantalla.
 * capas : formato de cada capa.
 * ventana : formato de ventana.
 * escenario : formato del escenario.
 * personaje : formato del personaje.
 */
Pantalla::Pantalla(vector<Tcapa> tcapas, Tventana ventana, Tescenario escenario, Tpersonaje tpersonaje) {
    // Setea los parametros de la pantalla
	mDimension.w = ventana.ancho;
    mDimension.h = escenario.alto;

    // Setea las escalas de relacion entre unidades y pixeles en la clase utilitaria
    VistaUtils::SCALE_X = ventana.anchopx / ventana.ancho;
    VistaUtils::SCALE_Y = ventana.altopx / escenario.alto;

    // Inicia la ventana y el renderer
    Inicializar(ventana.anchopx, ventana.altopx);
    xVentana = (escenario.ancho - ventana.ancho)/ 2;
    topeVentana = ventana.distTope;
    anchoEscenario = escenario.ancho;

    // Personaje
    zIndex = tpersonaje.zIndex;
    personaje = PersonajeVista(mRenderer, tpersonaje.sprites, tpersonaje.ancho, tpersonaje.alto, tpersonaje.orientacion);

    for (int i = 0; i < tcapas.size(); i++){
        Tdimension d;
        d.h = mDimension.h;
        d.w = tcapas[i].ancho;
        float v = (d.w - ventana.ancho) / (escenario.ancho - ventana.ancho); // TODO - Si ecenario == ventana?????
        v = ( v < 0 ) ? 0 : v;
        Capa capa = Capa(mRenderer, tcapas[i].dirCapa, d, v);
        capas.push_back(capa);
    }
}

/*
 * Dibuja todos los objetos en pantalla.
 */
void Pantalla::dibujar() {

    SDL_Texture* ventana = SDL_GetRenderTarget(mRenderer);

    for (int i = 0; i < capas.size(); i++) {
        capas[i].getTexture(ventana, mDimension.w, xVentana);
        if (i == zIndex) {
            personaje.getTexture(ventana, xVentana);
        }
    }
    SDL_RenderPresent(mRenderer);

}

/*
 * Actualiza todos los objetos de pantalla.
 * change : contiene los cambios a realizar.
 */
void Pantalla::update(Tcambio change) {
    personaje.update(change);
    float xPersonaje = personaje.getRect().p.x;
    if ( xPersonaje < xVentana + topeVentana ) {
        xVentana = xPersonaje - topeVentana;
        xVentana = (xVentana > 0) ? xVentana : 0;
    }
    else if ( xPersonaje > xVentana + mDimension.w - topeVentana ){
        xVentana = xPersonaje + topeVentana - mDimension.w;
        xVentana = (xVentana < anchoEscenario - mDimension.w) ? xVentana : anchoEscenario - mDimension.w;
    }
//    Capa::cambiarEscenario(change.posicion.x);
//    for (int i = 0; i < capas.size(); i++) {
//        capas[i].ajustar();
//    }
}


Pantalla::~Pantalla() {
    loguer->loguear("Destruccion de la pantalla", Log::LOG_DEB);
    for (int i = 0; i < capas.size(); i++)
        capas[i].freeTextures();
    personaje.freeTextures();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    loguer->loguear("Cierra SDL", Log::LOG_DEB);
    SDL_Quit();
    IMG_Quit();
}
