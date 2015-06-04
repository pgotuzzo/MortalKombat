
#include "ControladorTexto.h"

void ControladorTexto::generarCaracter() {

    SDL_Event e;

    while(SDL_PollEvent(&e) != 0){

        if(e.type == SDL_TEXTINPUT){
            cout<<e.text.text<<endl;
        }
    }

}
