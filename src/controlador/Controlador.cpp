
#include <SDL2/SDL_events.h>
#include "Controlador.h"

Controlador::Controlador() {
	inputAnterior = KEY_NADA;
}

/*
 * Devuelve la tecla anterior si se repite o la tecla nada si no se repite
 */
TinputPersonaje Controlador::esAnterior(const Uint8 *state) {
	switch (inputAnterior) {
		case KEY_IZQUIERDA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) return inputAnterior = KEY_ARRIBA_IZQUIERDA;
			else if (state[SDL_SCANCODE_LEFT]) return inputAnterior = KEY_IZQUIERDA; break;
		};
		case KEY_DERECHA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) return inputAnterior = KEY_ARRIBA_DERECHA;
			else if (state[SDL_SCANCODE_RIGHT]) return inputAnterior = KEY_DERECHA; break;
		};
		case KEY_ARRIBA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) return inputAnterior = KEY_ARRIBA_DERECHA;
			else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) return inputAnterior = KEY_ARRIBA_IZQUIERDA;
			else if (state[SDL_SCANCODE_UP]) return inputAnterior = KEY_ARRIBA; break;
		};
		case KEY_ABAJO: {
			if (state[SDL_SCANCODE_DOWN]) return inputAnterior = KEY_ABAJO; break;
		};
		case KEY_ARRIBA_DERECHA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) return inputAnterior = KEY_ARRIBA_DERECHA;
			else if (state[SDL_SCANCODE_RIGHT]) return inputAnterior = KEY_DERECHA; break;
		};
		case KEY_ARRIBA_IZQUIERDA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) return inputAnterior = KEY_ARRIBA_IZQUIERDA;
			else if (state[SDL_SCANCODE_LEFT]) return inputAnterior = KEY_IZQUIERDA; break;
		};
	}
	return KEY_NADA;
}

TinputPersonaje Controlador::getInputs() {

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	SDL_Event event;
//	TODO - Fran - Comento esta linea porque sino no funciona la tecla R. Hay que hacer alguna otra modificacion??
	while (SDL_PollEvent(&event) != 0) {}
	SDL_PollEvent(&event);
	TinputPersonaje anterior = esAnterior(state);
	switch (event.type) {
		case SDL_QUIT:
			return KEY_EXIT;

		case SDL_KEYDOWN: {
			if (anterior != KEY_NADA) return anterior;
			switch (event.key.keysym.sym) {
				case SDLK_LEFT: {
					if (state[SDL_SCANCODE_UP]) return inputAnterior = KEY_ARRIBA_IZQUIERDA;
					return inputAnterior = KEY_IZQUIERDA;
				};
				case SDLK_RIGHT: {
					if (state[SDL_SCANCODE_UP]) return inputAnterior = KEY_ARRIBA_DERECHA;
					return inputAnterior = KEY_DERECHA;
				};
				case SDLK_UP: {
					if (state[SDL_SCANCODE_RIGHT]) return inputAnterior = KEY_ARRIBA_DERECHA;
					else if (state[SDL_SCANCODE_LEFT]) return inputAnterior = KEY_ARRIBA_IZQUIERDA;
					return inputAnterior = KEY_ARRIBA;
				};
				case SDLK_DOWN: return inputAnterior = KEY_ABAJO;
				case SDLK_r: return KEY_RESTART;
			}
		}
		default:
			if (anterior != KEY_NADA) return anterior;
			if (state[SDL_SCANCODE_R]) return KEY_RESTART;
			if (state[SDL_SCANCODE_RIGHT]) return inputAnterior = KEY_DERECHA;
			else if (state[SDL_SCANCODE_LEFT]) return inputAnterior = KEY_IZQUIERDA;
			else if (state[SDL_SCANCODE_UP]) return inputAnterior = KEY_ARRIBA;
			else if (state[SDL_SCANCODE_DOWN]) return inputAnterior = KEY_ABAJO;
			else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) return inputAnterior = KEY_ARRIBA_DERECHA;
			else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) return inputAnterior = KEY_ARRIBA_IZQUIERDA;
	}

	inputAnterior = KEY_NADA;
	return KEY_NADA;
}