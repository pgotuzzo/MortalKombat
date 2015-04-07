#include "Pantalla.h"
#include <SDL2/SDL.h>
#include <iostream>

// TODO - Agregar al config.cpp y luego Eliminar!!!!
const string SPRITES_PATH_POSTA = "/home/pablo/Projects/MortalKombat/resources/sprites/zub_zero";

// TODO - Eliminar si no sirve mas
//Pantalla::Pantalla(vector<string> dirPaths, vector<float> anchosCapas, Dimensiones dimensiones, int zInd) {
//    Inicializar(dimensiones);
//    zIndex = zInd;
//    posPantalla = (dimensiones.anchoEscenario - dimensiones.anchoPantalla)/2;
//    cout<<"pos pantalla"<<posPantalla<<std::endl;
//
//    personaje = PersonajeVista(mRenderer, SPRITES_PATH_POSTA, 50, 80);
//
//    personaje.setPosition({750,400});
//
//    for (int i=0;i<dirPaths.size();i++) {
//        SDL_Rect rect;
//        rect.h = (int)dimensiones.altoPantalla;
//        rect.w = (int)dimensiones.anchoPantalla;
//        rect.x = (int)(anchosCapas[i] - dimensiones.anchoPantalla)/2;
//        rect.y = 0;
//        Capa capa = Capa(mRenderer, dirPaths[i],rect);
//        float relacionCapa = (dimensiones.anchoEscenario-dimensiones.anchoPantalla)/(anchosCapas[i]-dimensiones.anchoPantalla);
//        capa.setValores(anchosCapas[i], dimensiones.altoPantalla, dimensiones.distTope,relacionCapa);
//        capas.push_back(capa);
//    }
//    mDimensiones = dimensiones;
//}

Pantalla::Pantalla(vector<Tcapa> tcapas, Tventana ventana, Tescenario escenario, Tpersonaje tpersonaje) {
    mDimensiones.anchoPantalla = ventana.ancho;
    mDimensiones.altoPantalla = escenario.alto;
    mDimensiones.anchoPx = ventana.anchopx;
    mDimensiones.altoPx = ventana.altopx;
    mDimensiones.anchoEscenario = escenario.ancho;

    // TODO - Reimplementar
    mDimensiones.distTope = 50;

    Inicializar(mDimensiones);
    zIndex = tpersonaje.zIndex;
    posPantalla = (mDimensiones.anchoEscenario - mDimensiones.anchoPantalla)/2;

    // TODO - Loguear si se quiere
    cout << "Posicion de la pantalla = " << posPantalla << std::endl;

    // TODO - Eliminar SPRITES_PATH_POSTA
    personaje = PersonajeVista(mRenderer, SPRITES_PATH_POSTA, tpersonaje.ancho, tpersonaje.alto, tpersonaje.orientacion);

    for (Tcapa tcapa : tcapas){
        SDL_Rect rect;
        rect.h = (int) mDimensiones.altoPantalla;
        rect.w = (int) mDimensiones.anchoPantalla;
        rect.x = (int)(tcapa.ancho - mDimensiones.anchoPantalla)/2;
        rect.y = 0;
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
    SDL_Texture* escenario = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, mDimensiones.anchoPantalla, mDimensiones.altoPantalla);
    SDL_SetRenderTarget(mRenderer,escenario);

    for (int i = 0; i < capas.size(); i++) {
        SDL_Texture* texture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, mDimensiones.anchoPantalla, mDimensiones.altoPantalla);
        capas[i].getTexture(texture);
        SDL_RenderCopy(mRenderer, texture, NULL, NULL);
        if (i == zIndex) {
            SDL_Texture* texture = personaje.getTexture();
            SDL_Rect r = personaje.getRect();

            //TODO - Eliminar si no sirve mas o agregar al loguer - Fran?
//            cout<< "pos personaje"<< r.x<<"pos pantalla"<<posPantalla<<std::endl;

            r.x = r.x - (int) posPantalla;
            SDL_RenderCopy(mRenderer, texture, NULL, &r);
        }
    }

    //escalado
    SDL_SetRenderTarget(mRenderer, NULL);
    SDL_RenderCopy(mRenderer, escenario, NULL, NULL);
    SDL_RenderPresent(mRenderer);
}

void Pantalla::update(Tcambio change) {
    SDL_Rect rect = personaje.getRect();
    personaje.update(change);
    for (int i = 0; i < capas.size(); i++) {
        capas[i].cambiar(change.posicion, rect.w);
    }
    posPantalla = Capa::getPosCapa(change.posicion.x, 1, posPantalla, mDimensiones.anchoPantalla, mDimensiones.anchoEscenario, rect.w);
}


