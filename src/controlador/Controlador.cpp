#include <SDL2/SDL_events.h>
#include "Controlador.h"

/*
 * Pablo:
 * Esto del array de eventos lo saque de un video de internet. La url es https://www.youtube.com/watch?v=kaCOFjZXuQw
 * abajo del video esta el repo con el codigo, yo me fui guiando con eso y el video para hacerlo.
 * Hay que ver bien el tema de los saltos oblicuos porque ahi hay que leer mas de una tecla y no se muy bien como hacerlo.
 * Si queres seguir con tu codigo no hay drama, yo lo hice de esta manera pq me parecia una forma mas facil y mas linda.
 * No inclui el controlador.cpp y .h al makelist para que no pinche el codigo por algun motivo.
 * No pude probarlo pq estoy apurado.
 * Maniana sigo con otras cosas en que pueda ayudar. Abrazo. *
 */


//Recibo un array en el cual me dice que tecla se ha apretado
Controlador::Controlador() {
	keyWord = SDL_GetKeyboardState(NULL);
	}


//Devuelve el Tinput correspondiente evaluando al keyWord con los scancode de las teclas (true si estan activadas)
Tinput Controlador::getEvent() {
	Tinput input;

	if (keyWord[SDL_SCANCODE_UP]){
		input = KEY_ARRIBA;
	}

	if (keyWord[SDL_SCANCODE_DOWN]){
		input = KEY_ABAJO;
	}

	if (keyWord[SDL_SCANCODE_LEFT]){
		if (keyWord[SDL_SCANCODE_UP]){
			input = KEY_ARRIBA_IZQUIERDA;
		}
		input = KEY_IZQUIERDA;
	}

	if (keyWord[SDL_SCANCODE_RIGHT]){
		if (KeyWord[SDL_SCANCODE_UP]){
			input = KEY_ARRIBA_DERECHA;
		}
		input = KEY_DERECHA;
	}
	return input;

}


/*Tinput Controlador::getEvent() {

 SDL_Event event;

 while( SDL_PollEvent( &event ) ){
  switch( event.type ){
   case SDL_KEYDOWN:
	switch( event.key.keysym.sym ){
	 case SDLK_LEFT:
	  return KEY_IZQUIERDA;
	 case SDLK_RIGHT:
	  return KEY_DERECHA;
	 case SDLK_UP:
	  return KEY_ARRIBA;
	 case SDLK_DOWN:
	  return KEY_ABAJO;
	 default:
	  break;
	}
  }
 }*/

}