#include "Pantalla.h"
#include <SDL2/SDL.h>
#include <iostream>

const string SPRITES_PATH_POSTA = "/home/pablo/Projects/MortalKombat/resources/sprites/zub_zero";

void Pantalla::Inicializar(Dimensiones dimensiones) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        cout << "Fallo la inicializacion de SDL." << endl;

    mWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimensiones.anchoPx, dimensiones.altoPx, SDL_WINDOW_SHOWN);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
}

Pantalla::Pantalla(vector<string> dirPaths, vector<float> anchosCapas, Dimensiones dimensiones, int zInd) {
    Inicializar(dimensiones);
    zIndex = zInd;
    posPantalla = (dimensiones.anchoEscenario - dimensiones.anchoPantalla)/2;
    cout<<"pos pantalla"<<posPantalla<<std::endl;
    personaje = PersonajeVista(mRenderer, SPRITES_PATH_POSTA, 50, 80);
    personaje.setPosition({750,400});

    for (int i=0;i<dirPaths.size();i++) {
        SDL_Rect rect;
        rect.h = (int)dimensiones.altoPantalla;
        rect.w = (int)dimensiones.anchoPantalla;
        rect.x = (int)(anchosCapas[i] - dimensiones.anchoPantalla)/2;
        rect.y = 0;
        Capa capa = Capa(mRenderer, dirPaths[i],rect);
        float relacionCapa = (dimensiones.anchoEscenario-dimensiones.anchoPantalla)/(anchosCapas[i]-dimensiones.anchoPantalla);
        capa.setValores(anchosCapas[i], dimensiones.altoPantalla, dimensiones.distTope,relacionCapa);
        capas.push_back(capa);
    }
    mDimensiones = dimensiones;
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
            cout<< "pos personaje"<< r.x<<"pos pantalla"<<posPantalla<<std::endl;
            r.x = r.x - posPantalla;
            SDL_RenderCopy(mRenderer, texture, NULL, &r);
        }
    }

    //escalado
    SDL_SetRenderTarget(mRenderer, NULL);
    SDL_RenderCopy(mRenderer, escenario, NULL, NULL);
    SDL_RenderPresent(mRenderer);
}

void Pantalla::update(Pos p, PersonajeVista::State state) {
    SDL_Rect rect = personaje.getRect();
    personaje.setState(state);
    personaje.setPosition(p);
    for (int i=0;i<capas.size();i++) {
        capas[i].cambiar(p, rect.w);
    }
    posPantalla = Capa::getPosCapa(p.x,1,posPantalla, mDimensiones.anchoPantalla, mDimensiones.anchoEscenario, rect.w);
}
