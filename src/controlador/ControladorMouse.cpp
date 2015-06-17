
#include "ControladorMouse.h"
#include "../utils/Common.h"

ControladorMouse::ControladorMouse() {
    posicionMouse = Posicion();
}

TinputGame ControladorMouse::moverMouse(SDL_Event event) {
    if(event.type == SDL_MOUSEMOTION){
        posicionMouse.x = event.button.x;
        posicionMouse.y = event.button.y;
    } else if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.button == SDL_BUTTON_LEFT) return TinputGame::CLICK_IZQ_MOUSE;
    } else {
        posicionMouse.x = -1;
        posicionMouse.y = -1;
    }
}

