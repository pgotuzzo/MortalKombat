#include <SDL2/SDL_events.h>
#include "Controlador.h"

Tinput Controlador::getEvent() {

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
 }

}