
#include <SDL2/SDL_events.h>
#include "ControladorTeclado.h"

ControladorTeclado::ControladorTeclado() {
	inputAnterior1 = KEY_NADA;
	inputAnterior2 = KEY_NADA;
}

/*
 * Devuelve la tecla anterior si se repite o la tecla nada si no se repite
 */
Tinput ControladorTeclado::esAnterior1(const Uint8 *state) {
	switch (inputAnterior1) {
		case KEY_IZQUIERDA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) return inputAnterior1 = KEY_ARRIBA_IZQUIERDA;
			else if (state[SDL_SCANCODE_LEFT]) return inputAnterior1 = KEY_IZQUIERDA; break;
		};
		case KEY_DERECHA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) return inputAnterior1 = KEY_ARRIBA_DERECHA;
			else if (state[SDL_SCANCODE_RIGHT]) return inputAnterior1 = KEY_DERECHA; break;
		};
		case KEY_ARRIBA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) return inputAnterior1 = KEY_ARRIBA_DERECHA;
			else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) return inputAnterior1 = KEY_ARRIBA_IZQUIERDA;
			else if (state[SDL_SCANCODE_UP]) return inputAnterior1 = KEY_ARRIBA; break;
		};
		case KEY_ABAJO: {
			if (state[SDL_SCANCODE_DOWN]) return inputAnterior1 = KEY_ABAJO; break;
		};
		case KEY_ARRIBA_DERECHA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) return inputAnterior1 = KEY_ARRIBA_DERECHA;
			else if (state[SDL_SCANCODE_RIGHT]) return inputAnterior1 = KEY_DERECHA; break;
		};
		case KEY_ARRIBA_IZQUIERDA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) return inputAnterior1 = KEY_ARRIBA_IZQUIERDA;
			else if (state[SDL_SCANCODE_LEFT]) return inputAnterior1 = KEY_IZQUIERDA; break;
		};
	}
	return KEY_NADA;
}
/*
 * Devuelve la tecla anterior si se repite o la tecla nada si no se repite
 */
Tinput ControladorTeclado::esAnterior2(const Uint8 *state) {
	switch (inputAnterior2) {
		case KEY_IZQUIERDA: {
			if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) return inputAnterior2 = KEY_ARRIBA_IZQUIERDA;
			else if (state[SDL_SCANCODE_A]) return inputAnterior2 = KEY_IZQUIERDA; break;
		};
		case KEY_DERECHA: {
			if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) return inputAnterior2 = KEY_ARRIBA_DERECHA;
			else if (state[SDL_SCANCODE_D]) return inputAnterior2 = KEY_DERECHA; break;
		};
		case KEY_ARRIBA: {
			if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) return inputAnterior2 = KEY_ARRIBA_DERECHA;
			else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) return inputAnterior2 = KEY_ARRIBA_IZQUIERDA;
			else if (state[SDL_SCANCODE_W]) return inputAnterior2 = KEY_ARRIBA; break;
		};
		case KEY_ABAJO: {
			if (state[SDL_SCANCODE_S]) return inputAnterior2 = KEY_ABAJO; break;
		};
		case KEY_ARRIBA_DERECHA: {
			if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) return inputAnterior2 = KEY_ARRIBA_DERECHA;
			else if (state[SDL_SCANCODE_D]) return inputAnterior2 = KEY_DERECHA; break;
		};
		case KEY_ARRIBA_IZQUIERDA: {
			if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) return inputAnterior2 = KEY_ARRIBA_IZQUIERDA;
			else if (state[SDL_SCANCODE_A]) return inputAnterior2 = KEY_IZQUIERDA; break;
		};
	}
	return KEY_NADA;
}

Tinputs ControladorTeclado::getInputs() {

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	Tinputs inputs;

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {}
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			inputs.input1 = KEY_EXIT;
			return inputs;

		// Solo captura el evento cuando suelta R
		case SDL_KEYUP: {
			if (event.key.keysym.sym == SDLK_r) {
				inputs.input1 = KEY_RESTART;
				return inputs;
			}
		};
		default:
			Tinput anterior1 = esAnterior1(state);
			Tinput anterior2 = esAnterior2(state);
			if (anterior1 != KEY_NADA && anterior2 != KEY_NADA) {
				inputs.input1 = anterior1;
				inputs.input2 = anterior2;
				return inputs;
			} else if (anterior1 != KEY_NADA) {
				inputs.input1 = anterior1;
				if (state[SDL_SCANCODE_D]) inputAnterior2 = KEY_DERECHA;
				else if (state[SDL_SCANCODE_A]) inputAnterior2 = KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_W]) inputAnterior2 = KEY_ARRIBA;
				else if (state[SDL_SCANCODE_S]) inputAnterior2 = KEY_ABAJO;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) inputAnterior2 = KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) inputAnterior2 = KEY_ARRIBA_IZQUIERDA;
				else inputAnterior2 = KEY_NADA;
				inputs.input2 = inputAnterior2;
				return inputs;

			} else if (anterior2 != KEY_NADA) {
				inputs.input2 = anterior2;
				if (state[SDL_SCANCODE_RIGHT]) inputAnterior1 = KEY_DERECHA;
				else if (state[SDL_SCANCODE_LEFT]) inputAnterior1 = KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_UP]) inputAnterior1 = KEY_ARRIBA;
				else if (state[SDL_SCANCODE_DOWN]) inputAnterior1 = KEY_ABAJO;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) inputAnterior1 = KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) inputAnterior1 = KEY_ARRIBA_IZQUIERDA;
				else inputAnterior1 = KEY_NADA;
				inputs.input1 = inputAnterior1;
				return inputs;
			} else {
				if (state[SDL_SCANCODE_RIGHT]) inputAnterior1 = KEY_DERECHA;
				else if (state[SDL_SCANCODE_LEFT]) inputAnterior1 = KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_UP]) inputAnterior1 = KEY_ARRIBA;
				else if (state[SDL_SCANCODE_DOWN]) inputAnterior1 = KEY_ABAJO;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) inputAnterior1 = KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) inputAnterior1 = KEY_ARRIBA_IZQUIERDA;
				else inputAnterior1 = KEY_NADA;
				if (state[SDL_SCANCODE_D]) inputAnterior2 = KEY_DERECHA;
				else if (state[SDL_SCANCODE_A]) inputAnterior2 = KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_W]) inputAnterior2 = KEY_ARRIBA;
				else if (state[SDL_SCANCODE_S]) inputAnterior2 = KEY_ABAJO;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) inputAnterior2 = KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) inputAnterior2 = KEY_ARRIBA_IZQUIERDA;
				else inputAnterior2 = KEY_NADA;
				inputs.input1 = inputAnterior1;
				inputs.input2 = inputAnterior2;
				return inputs;
			}
	}
}