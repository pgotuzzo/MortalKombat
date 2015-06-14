
#include "ControladorMouse.h"
#include "../utils/Common.h"

ControladorMouse::ControladorMouse() {
    posicionMouse = Posicion();
}

TinputGame ControladorMouse::moverMouse(SDL_Event event) {
    if(event.type == SDL_MOUSEMOTION){
        //TODO: PASARLO A COORDENADAS LOGICAS. ESTA EN PIXELES
        posicionMouse.x = event.button.x;
        posicionMouse.y = event.button.y;
    }
    if(event.type == SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT) return TinputGame::CLICK_IZQ_MOUSE;
    }
}

