
#include <SDL2/SDL_events.h>
#include "Controlador.h"

Controlador::Controlador() {
	inputAnterior = KEY_NADA;
}

Tinput Controlador::getInputs() {

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			return KEY_EXIT;

		case SDL_KEYDOWN: {
			switch (inputAnterior) {
				case KEY_IZQUIERDA: {
					if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT])
						return KEY_ARRIBA_IZQUIERDA;
					else if (state[SDL_SCANCODE_LEFT])
						return KEY_IZQUIERDA;
					break;
				};
				case KEY_DERECHA: {
					if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
						return KEY_ARRIBA_DERECHA;
					else if (state[SDL_SCANCODE_RIGHT])
						return KEY_DERECHA;
					break;
				};
				case KEY_ARRIBA: {
					if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
						return KEY_ARRIBA_DERECHA;
					else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT])
						return KEY_ARRIBA_IZQUIERDA;
					else if (state[SDL_SCANCODE_UP])
						return KEY_ARRIBA;
					break;
				};
				case KEY_ABAJO: {
					if (state[SDL_SCANCODE_DOWN])
						return KEY_ABAJO;
					break;
				};
				case KEY_ARRIBA_DERECHA: {
					if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
						return KEY_ARRIBA_DERECHA;
					else if (state[SDL_SCANCODE_RIGHT])
						return KEY_DERECHA;
					break;
				};
				case KEY_ARRIBA_IZQUIERDA: {
					if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT])
						return KEY_ARRIBA_IZQUIERDA;
					else if (state[SDL_SCANCODE_LEFT])
						return KEY_IZQUIERDA;
					break;
				};
			}
			switch (event.key.keysym.sym) {
				case SDLK_LEFT: {
					if (state[SDL_SCANCODE_UP]) {
						inputAnterior = KEY_ARRIBA_IZQUIERDA;
						return KEY_ARRIBA_IZQUIERDA;
					}
					inputAnterior = KEY_IZQUIERDA;
					return KEY_IZQUIERDA;
				};
				case SDLK_RIGHT: {
					if (state[SDL_SCANCODE_UP]) {
						inputAnterior = KEY_ARRIBA_DERECHA;
						return KEY_ARRIBA_DERECHA;
					}
					inputAnterior = KEY_DERECHA;
					return KEY_DERECHA;
				};
				case SDLK_UP: {
					if (state[SDL_SCANCODE_RIGHT]) {
						inputAnterior = KEY_ARRIBA_DERECHA;
						return KEY_ARRIBA_DERECHA;
					}
					else if (state[SDL_SCANCODE_LEFT]) {
						inputAnterior = KEY_ARRIBA_IZQUIERDA;
						return KEY_ARRIBA_IZQUIERDA;
					}
					inputAnterior = KEY_ARRIBA;
					return KEY_ARRIBA;
				};
				case SDLK_DOWN: {
					inputAnterior = KEY_ABAJO;
					return KEY_ABAJO;
				};
				case SDLK_r: {
					return KEY_RESTART;
				};
			}
		}
		default:
			switch (inputAnterior) {
				case KEY_IZQUIERDA: {
					if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT])
						return KEY_ARRIBA_IZQUIERDA;
					else if (state[SDL_SCANCODE_LEFT])
						return KEY_IZQUIERDA;
					break;
				};
				case KEY_DERECHA: {
					if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
						return KEY_ARRIBA_DERECHA;
					else if (state[SDL_SCANCODE_RIGHT])
						return KEY_DERECHA;
					break;
				};
				case KEY_ARRIBA: {
					if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
						return KEY_ARRIBA_DERECHA;
					else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT])
						return KEY_ARRIBA_IZQUIERDA;
					else if (state[SDL_SCANCODE_UP])
						return KEY_ARRIBA;
					break;
				};
				case KEY_ABAJO: {
					if (state[SDL_SCANCODE_DOWN])
						return KEY_ABAJO;
					break;
				};
				case KEY_ARRIBA_DERECHA: {
					if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
						return KEY_ARRIBA_DERECHA;
					else if (state[SDL_SCANCODE_RIGHT])
						return KEY_DERECHA;
					break;
				};
			}
			if (state[SDL_SCANCODE_RIGHT]) return KEY_DERECHA;
			else if (state[SDL_SCANCODE_LEFT]) return KEY_IZQUIERDA;
			else if (state[SDL_SCANCODE_UP]) return KEY_ARRIBA;
			else if (state[SDL_SCANCODE_DOWN]) return KEY_ABAJO;
			else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) return KEY_ARRIBA_DERECHA;
			else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) return KEY_ARRIBA_IZQUIERDA;
	}

	return KEY_NADA;
}