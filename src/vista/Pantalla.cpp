#include "Pantalla.h"
#include "VistaUtils.h"
#include <SDL2/SDL.h>
#include <iostream>

// TODO - Agregar al config.cpp y luego Eliminar!!!!
const string SPRITES_PATH_POSTA = "/home/pablo/Projects/MortalKombat/resources/sprites/zub_zero";

Pantalla::Pantalla(vector<Tcapa> tcapas, Tventana ventana, Tescenario escenario, Tpersonaje tpersonaje) {
    mDimensiones.anchoPantalla = ventana.ancho;
    mDimensiones.altoPantalla = escenario.alto;
    mDimensiones.anchoPx = ventana.anchopx;
    mDimensiones.altoPx = ventana.altopx;
    mDimensiones.anchoEscenario = escenario.ancho;

    VistaUtils::SCALE_X = ventana.anchopx / ventana.ancho;
    VistaUtils::SCALE_Y = ventana.altopx / escenario.alto;

    // TODO - Reimplementar
    mDimensiones.distTope = 50;

    Inicializar(mDimensiones);
    zIndex = tpersonaje.zIndex;
    posPantalla = (mDimensiones.anchoEscenario - mDimensiones.anchoPantalla)/2;

    // TODO - Eliminar SPRITES_PATH_POSTA
    personaje = PersonajeVista(mRenderer, SPRITES_PATH_POSTA, tpersonaje.ancho, tpersonaje.alto, tpersonaje.orientacion);

    for (Tcapa tcapa : tcapas){
        VistaUtils::Trect rect;
        rect.h = mDimensiones.altoPantalla;
        rect.w = mDimensiones.anchoPantalla;
        rect.p.x = (tcapa.ancho - mDimensiones.anchoPantalla)/2;
        rect.p.y = 0;
        Capa capa = Capa(mRenderer, tcapa.dirCapa, rect);
        float relacionCapa = (mDimensiones.anchoEscenario - mDimensiones.anchoPantalla)/(tcapa.ancho - mDimensiones.anchoPantalla);
        capa.setValores(tcapa.ancho, mDimensiones.altoPantalla, mDimensiones.distTope, relacionCapa);
        capas.push_back(capa);
    }
}

void Pantalla::Inicializar(Dimensiones dimensiones) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        cout << "Fallo la inicializacion de SDL." << endl;

    mWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimensiones.anchoPx, dimensiones.altoPx, SDL_WINDOW_SHOWN);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
}

void Pantalla::dibujar() {
    SDL_Texture* texture = VistaUtils::createTexture(mRenderer, mDimensiones.anchoPantalla, mDimensiones.altoPantalla);

    for (int i = 0; i < capas.size(); i++) {
        capas[i].getTexture(texture);
        if (i == zIndex) {
            SDL_Texture* texturePersonaje = personaje.getTexture();
            VistaUtils::Trect r = personaje.getRect();

            r.p.x = r.p.x - posPantalla;
            VistaUtils::copyTexture(mRenderer, texturePersonaje, texture , NULL, &r);
        }
        VistaUtils::copyTexture(mRenderer, texture, NULL, NULL, NULL);
    }
    SDL_RenderPresent(mRenderer);

}

void Pantalla::update(Tcambio change) {
    VistaUtils::Trect rect = personaje.getRect();
    personaje.update(change);
    for (int i = 0; i < capas.size(); i++) {
        capas[i].cambiar(change.posicion, rect.w);
    }
    posPantalla = Capa::getPosCapa(change.posicion.x, 1, posPantalla, mDimensiones.anchoPantalla, mDimensiones.anchoEscenario, rect.w);
}


