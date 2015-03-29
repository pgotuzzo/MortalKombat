#include "Pantalla.h"
#include "Capa.h"
#include <vector>

Pantalla::Pantalla(std::vector<std::string> dirPaths,std::vector<float> anchosCapas,float distTope) {
    Capa capa;
// en algun momento se tiene q crear el render
    //tambien linkear el personaje
    for (int i=0;i<dirPaths.size();i++) {
        capa = new Capa(mRender, dirPaths[i]);
        float relacionCapa = (anchoEscenario-anchoPantalla)/(anchoCapa-anchoPantalla);
        capa.setValores(anchosCapas[i],distTope,relacionCapa);
        capas.push_back(capa);
    }
}

void Pantalla::dibujar() {
    for (int i=0;i<capas.size();i++) {
        cambiar(personaje.getPos);
    }
    for (int i=0;i<capas.size();i++) {
        SDL_Texture texture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, anchoPantalla, altoPantalla);
        capas[i].getTexture(SDL_Texture* texture);
        //hay que pintar la textura
    }
}