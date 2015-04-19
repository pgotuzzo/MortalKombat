#include "Pantalla.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
 * Se inicia la ventana y el renderer.
 */
void Pantalla::Inicializar(int anchoPx,int altoPx) {
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
	anchoPantalla = ventana.ancho;
    altoPantalla = escenario.alto;

    // Setea las escalas de relacion entre unidades y pixeles
    VistaUtils::SCALE_X = ventana.anchopx / ventana.ancho;
    VistaUtils::SCALE_Y = ventana.altopx / escenario.alto;

    // Inicia la ventana y el renderer
    Inicializar(ventana.anchopx,ventana.altopx);
    zIndex = tpersonaje.zIndex;
    personaje = PersonajeVista(mRenderer, tpersonaje.sprites, tpersonaje.ancho, tpersonaje.alto, tpersonaje.orientacion);

    // Primero se setean las variables de clase.
    Capa::setStatics(ventana.distTope, tpersonaje.ancho, escenario.ancho, anchoPantalla);
    // Crea las capas.
    for (int i = 0; i < tcapas.size(); i++){
        VistaUtils::Trect rect;
        rect.h = altoPantalla;
        rect.w = anchoPantalla;
        rect.p.x = (tcapas[i].ancho - anchoPantalla)/2;
        rect.p.y = 0;
        Capa capa = Capa(mRenderer, tcapas[i].dirCapa, rect);
        capa.setValores(tcapas[i].ancho, altoPantalla);
        capas.push_back(capa);
    }
}

/*
 * Dibuja todos los objetos en pantalla.
 */
void Pantalla::dibujar() {

    SDL_Texture* ventana = SDL_GetRenderTarget(mRenderer);

    for (int i = 0; i < capas.size(); i++) {
        capas[i].getTexture(ventana);
        if (i == zIndex) {
            personaje.getTexture(ventana, Capa::getPosPantalla());
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
    Capa::cambiarEscenario(change.posicion.x);
    for (int i = 0; i < capas.size(); i++) {
        capas[i].ajustar();
    }
}


Pantalla::~Pantalla() {
    for (int i = 0; i < capas.size(); i++)
        capas[i].freeTextures();
    personaje.freeTextures();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
    IMG_Quit();
}
