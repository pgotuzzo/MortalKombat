
#include <SDL2/SDL_events.h>
#include "Controlador.h"

Controlador::Controlador() {

}

Tinput Controlador::getInputs() {

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			return KEY_EXIT;

		case SDL_KEYDOWN: {
			Tinput input = getKeyBoardInput(event.key.keysym.sym);
			switch (input) {
				case KEY_IZQUIERDA: {
					return (state[SDL_SCANCODE_UP]) ? KEY_ARRIBA_IZQUIERDA : KEY_IZQUIERDA;
				};
				case KEY_DERECHA: {
					return (state[SDL_SCANCODE_UP]) ? KEY_ARRIBA_DERECHA : KEY_DERECHA;
				};
				case KEY_ARRIBA: {
					if (state[SDL_SCANCODE_RIGHT])
						return KEY_ARRIBA_DERECHA;
					else if (state[SDL_SCANCODE_LEFT])
						return KEY_ARRIBA_IZQUIERDA;
					return KEY_ARRIBA;
				}
				default:
					return input;
			}
		}
		default:
			if (state[SDL_SCANCODE_RIGHT]) return KEY_DERECHA;
			else if (state[SDL_SCANCODE_LEFT]) return KEY_IZQUIERDA;
			else if (state[SDL_SCANCODE_UP]) return KEY_ARRIBA;
			else if (state[SDL_SCANCODE_DOWN]) return KEY_ABAJO;
	}

	return KEY_NADA;
}

Tinput Controlador::getKeyBoardInput(SDL_Keycode key){
	switch (key){
		case SDLK_LEFT:
			return KEY_IZQUIERDA;
		case SDLK_RIGHT:
			return KEY_DERECHA;
		case SDLK_UP:
			return KEY_ARRIBA;
		case SDLK_DOWN:
			return KEY_ABAJO;
		case SDLK_r:
			return KEY_RESTART;
	}
	return KEY_NADA;
}