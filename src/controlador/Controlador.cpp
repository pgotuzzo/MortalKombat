
#include <SDL2/SDL_events.h>
#include "Controlador.h"

Controlador::Controlador() {}

std::vector<Tinput> Controlador::getInputs() {

	std::vector<Tinput> inputs = std::vector<Tinput>();

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return std::vector<Tinput >({KEY_EXIT});

			case SDL_KEYDOWN: {
				Tinput input = getKeyBoardInput(event.key.keysym.sym);
				switch (input) {
					case KEY_RESTART: return std::vector<Tinput >({KEY_RESTART});
					case KEY_ARRIBA: {
						if (state[SDL_SCANCODE_RIGHT])
							inputs.push_back(KEY_ARRIBA_DERECHA);
						else if (state[SDL_SCANCODE_LEFT])
							inputs.push_back(KEY_ARRIBA_IZQUIERDA);
					}
				}
				inputs.push_back(input);
			}
		};
	}
	return inputs;
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