
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
        if(event.button.button == SDL_BUTTON_LEFT) return TinputGame::KEY_ENTER;
    }
}

bool ControladorMouse::dentroDeRectangulo(Trect rectangulo) {
    float x = posicionMouse.getX();
    float y = posicionMouse.getY();

    float xRect = rectangulo.p.x;
    float yRect = rectangulo.p.y;
    float ancho = rectangulo.d.w;
    float alto = rectangulo.d.h;

    if (x < (xRect + ancho)) {
        return x > xRect && y > yRect && y < (yRect + alto);
    }
    else {
        return false;
    }
}
