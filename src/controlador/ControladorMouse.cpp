
#include "ControladorMouse.h"

ControladorMouse::ControladorMouse() {
    posicionMouse = Posicion();
}

void ControladorMouse::moverMouse() {

    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){

        if(e.type == SDL_MOUSEMOTION){
            //TODO: PASARLO A COORDENADAS LOGICAS. ESTA EN PIXELES
            posicionMouse.x = e.button.x;
            posicionMouse.y = e.button.y;
            posicionMouse.mostrarPar();
        }
        if(e.type == SDL_MOUSEBUTTONDOWN){
            if(e.button.button == SDL_BUTTON_LEFT) {
                cout << "Se apreto boton del mouse" << endl;
            }
        }
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
