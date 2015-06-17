
#include "ControladorTexto.h"

Tletras ControladorTexto::generarCaracter(SDL_Event &e) {

	Tletras input;
	if(e.type == SDL_TEXTINPUT){
		input.letra = e.text.text[0];
		input.recibe = true;

	}else if(e.key.keysym.sym == SDLK_BACKSPACE){
		input.borrado = true;
		input.recibe = true;
	}

	return input;

}
