
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
		case KEY_PINIA_ALTA: {
			if (state[SDL_SCANCODE_U]) return inputAnterior1 = KEY_PINIA_ALTA; break;
		};
		case KEY_PINIA_BAJA: {
			if (state[SDL_SCANCODE_I]) return inputAnterior1 = KEY_PINIA_BAJA; break;
		};
		case KEY_PATADA_ALTA: {
			if (state[SDL_SCANCODE_J]) return inputAnterior1 = KEY_PATADA_ALTA; break;
		};
		case KEY_PATADA_BAJA: {
			if (state[SDL_SCANCODE_K]) return inputAnterior1 = KEY_PATADA_BAJA; break;
		};
		case KEY_PROTECCION: {
			if (state[SDL_SCANCODE_O]) return inputAnterior1 = KEY_PROTECCION; break;
		};
		case KEY_PODER: {
			if (state[SDL_SCANCODE_L]) return inputAnterior1 = KEY_PODER; break;
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
		case KEY_PINIA_ALTA: {
			if (state[SDL_SCANCODE_F]) return inputAnterior2 = KEY_PINIA_ALTA; break;
		};
		case KEY_PINIA_BAJA: {
			if (state[SDL_SCANCODE_G]) return inputAnterior2 = KEY_PINIA_BAJA; break;
		};
		case KEY_PATADA_ALTA: {
			if (state[SDL_SCANCODE_V]) return inputAnterior2 = KEY_PATADA_ALTA; break;
		};
		case KEY_PATADA_BAJA: {
			if (state[SDL_SCANCODE_B]) return inputAnterior2 = KEY_PATADA_BAJA; break;
		};
		case KEY_PROTECCION: {
			if (state[SDL_SCANCODE_H]) return inputAnterior2 = KEY_PROTECCION; break;
		};
		case KEY_PODER: {
			if (state[SDL_SCANCODE_N]) return inputAnterior2 = KEY_PODER; break;
		};
	}
	return KEY_NADA;
}

vector<Tinput> ControladorTeclado::getInputs() {

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	vector<Tinput> inputs = {Tinput(), Tinput()};

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {}
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			inputs[0] = KEY_EXIT;
			return inputs;

			// Solo captura el evento cuando suelta R
		case SDL_KEYUP: {
			if (event.key.keysym.sym == SDLK_r) {
				inputs[0] = KEY_RESTART;
				return inputs;
			}
		};
		default:
			Tinput anterior1 = esAnterior1(state);
			Tinput anterior2 = esAnterior2(state);
			if (anterior1 != KEY_NADA && anterior2 != KEY_NADA) {
				inputs[0] = anterior1;
				inputs[1] = anterior2;
				return inputs;
			} else if (anterior1 != KEY_NADA) {
				inputs[0] = anterior1;
				if (state[SDL_SCANCODE_D]) inputAnterior2 = KEY_DERECHA;
				else if (state[SDL_SCANCODE_A]) inputAnterior2 = KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_W]) inputAnterior2 = KEY_ARRIBA;
				else if (state[SDL_SCANCODE_S]) inputAnterior2 = KEY_ABAJO;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) inputAnterior2 = KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) inputAnterior2 = KEY_ARRIBA_IZQUIERDA;
				else if (state[SDL_SCANCODE_F]) inputAnterior2 = KEY_PINIA_ALTA;
				else if (state[SDL_SCANCODE_G]) inputAnterior2 = KEY_PINIA_BAJA;
				else if (state[SDL_SCANCODE_V]) inputAnterior2 = KEY_PATADA_ALTA;
				else if (state[SDL_SCANCODE_B]) inputAnterior2 = KEY_PATADA_BAJA;
				else if (state[SDL_SCANCODE_H]) inputAnterior2 = KEY_PROTECCION;
				else if (state[SDL_SCANCODE_N]) inputAnterior2 = KEY_PODER;
				else inputAnterior2 = KEY_NADA;
				inputs[1] = inputAnterior2;
				return inputs;

			} else if (anterior2 != KEY_NADA) {
				inputs[1] = anterior2;
				if (state[SDL_SCANCODE_RIGHT]) inputAnterior1 = KEY_DERECHA;
				else if (state[SDL_SCANCODE_LEFT]) inputAnterior1 = KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_UP]) inputAnterior1 = KEY_ARRIBA;
				else if (state[SDL_SCANCODE_DOWN]) inputAnterior1 = KEY_ABAJO;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) inputAnterior1 = KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) inputAnterior1 = KEY_ARRIBA_IZQUIERDA;
				else if (state[SDL_SCANCODE_U]) inputAnterior1 = KEY_PINIA_ALTA;
				else if (state[SDL_SCANCODE_I]) inputAnterior1 = KEY_PINIA_BAJA;
				else if (state[SDL_SCANCODE_J]) inputAnterior1 = KEY_PATADA_ALTA;
				else if (state[SDL_SCANCODE_K]) inputAnterior1 = KEY_PATADA_BAJA;
				else if (state[SDL_SCANCODE_O]) inputAnterior1 = KEY_PROTECCION;
				else if (state[SDL_SCANCODE_L]) inputAnterior1 = KEY_PODER;
				else inputAnterior1 = KEY_NADA;
				inputs[0] = inputAnterior1;
				return inputs;
			} else {
				if (state[SDL_SCANCODE_RIGHT]) inputAnterior1 = KEY_DERECHA;
				else if (state[SDL_SCANCODE_LEFT]) inputAnterior1 = KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_UP]) inputAnterior1 = KEY_ARRIBA;
				else if (state[SDL_SCANCODE_DOWN]) inputAnterior1 = KEY_ABAJO;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) inputAnterior1 = KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) inputAnterior1 = KEY_ARRIBA_IZQUIERDA;
				else if (state[SDL_SCANCODE_F]) inputAnterior1 = KEY_PINIA_ALTA;
				else if (state[SDL_SCANCODE_G]) inputAnterior1 = KEY_PINIA_BAJA;
				else if (state[SDL_SCANCODE_V]) inputAnterior1 = KEY_PATADA_ALTA;
				else if (state[SDL_SCANCODE_B]) inputAnterior1 = KEY_PATADA_BAJA;
				else if (state[SDL_SCANCODE_H]) inputAnterior1 = KEY_PROTECCION;
				else if (state[SDL_SCANCODE_N]) inputAnterior1 = KEY_PODER;
				else inputAnterior1 = KEY_NADA;
				if (state[SDL_SCANCODE_D]) inputAnterior2 = KEY_DERECHA;
				else if (state[SDL_SCANCODE_A]) inputAnterior2 = KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_W]) inputAnterior2 = KEY_ARRIBA;
				else if (state[SDL_SCANCODE_S]) inputAnterior2 = KEY_ABAJO;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) inputAnterior2 = KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) inputAnterior2 = KEY_ARRIBA_IZQUIERDA;
				else if (state[SDL_SCANCODE_U]) inputAnterior2 = KEY_PINIA_ALTA;
				else if (state[SDL_SCANCODE_I]) inputAnterior2 = KEY_PINIA_BAJA;
				else if (state[SDL_SCANCODE_J]) inputAnterior2 = KEY_PATADA_ALTA;
				else if (state[SDL_SCANCODE_K]) inputAnterior2 = KEY_PATADA_BAJA;
				else if (state[SDL_SCANCODE_O]) inputAnterior2 = KEY_PROTECCION;
				else if (state[SDL_SCANCODE_L]) inputAnterior2 = KEY_PODER;
				else inputAnterior2 = KEY_NADA;
				inputs[0] = inputAnterior1;
				inputs[1] = inputAnterior2;
				return inputs;
			}
	}
};
