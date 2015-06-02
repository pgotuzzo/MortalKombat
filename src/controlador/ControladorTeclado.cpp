
#include <SDL2/SDL_events.h>
#include "ControladorTeclado.h"

ControladorTeclado::ControladorTeclado() {
}

/*
 * Devuelve la tecla anterior si se repite o la tecla nada si no se repite
 */
Tinput ControladorTeclado::esAnterior1(const Uint8 *state) {
	bool sigue=false;
	Tinput aux;
	switch (inputAnterior1.movimiento) {
		case TinputMovimiento::KEY_IZQUIERDA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]&&(state[SDL_SCANCODE_U] ||state[SDL_SCANCODE_I]||state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K]||state[SDL_SCANCODE_O]||state[SDL_SCANCODE_L])){
				if(state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K]){
					inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
					return inputAnterior1;
				} else {
					inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
					return inputAnterior1;
				}

			}else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
				inputAnterior1.accion=TinputAccion::KEY_NADA;
				return inputAnterior1;
			}else if (state[SDL_SCANCODE_LEFT]&&state[SDL_SCANCODE_U]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
				return inputAnterior1;
			}else if (state[SDL_SCANCODE_LEFT]&&state[SDL_SCANCODE_I]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				return inputAnterior1;
			}else if (state[SDL_SCANCODE_LEFT]&&state[SDL_SCANCODE_J]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
				return inputAnterior1;
			}else if (state[SDL_SCANCODE_LEFT]&&state[SDL_SCANCODE_K]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				return inputAnterior1;
			}
			else if (state[SDL_SCANCODE_LEFT]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				inputAnterior1.accion=TinputAccion::KEY_NADA;
				return inputAnterior1; break;
			}
		};
		case TinputMovimiento::KEY_DERECHA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]&&(state[SDL_SCANCODE_U] ||state[SDL_SCANCODE_I]||state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K]||state[SDL_SCANCODE_O]||state[SDL_SCANCODE_L])){
				if(state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K]){
					inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
					return inputAnterior1;
				} else {
					inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
					return inputAnterior1;
				}

			}else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
				inputAnterior1.accion=TinputAccion::KEY_NADA;
				return inputAnterior1;
			}else if (state[SDL_SCANCODE_RIGHT]&&state[SDL_SCANCODE_U]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_DERECHA;
				inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
				return inputAnterior1;
			}else if (state[SDL_SCANCODE_RIGHT]&&state[SDL_SCANCODE_I]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_DERECHA;
				inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				return inputAnterior1;
			}else if (state[SDL_SCANCODE_RIGHT]&&state[SDL_SCANCODE_J]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_DERECHA;
				inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
				return inputAnterior1;
			}else if (state[SDL_SCANCODE_RIGHT]&&state[SDL_SCANCODE_K]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_DERECHA;
				inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				return inputAnterior1;
			}else if (state[SDL_SCANCODE_RIGHT]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_DERECHA;
				inputAnterior1.accion=TinputAccion::KEY_NADA;
				return inputAnterior1; break;
			}
		};
		case TinputMovimiento::KEY_ARRIBA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]&&(state[SDL_SCANCODE_U] ||state[SDL_SCANCODE_I]||state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K]||state[SDL_SCANCODE_O]||state[SDL_SCANCODE_L])){
				if(state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K]){
					inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
					return inputAnterior1;
				} else {
					inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
					return inputAnterior1;
				}
			} else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]&&(state[SDL_SCANCODE_U] ||state[SDL_SCANCODE_I]||state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K]||state[SDL_SCANCODE_O]||state[SDL_SCANCODE_L])){
				if(state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K]){
					inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
					return inputAnterior1;
				} else {
					inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
					return inputAnterior1;
				}
			}else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
				inputAnterior1.accion=TinputAccion::KEY_NADA;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
				inputAnterior1.accion=TinputAccion::KEY_NADA;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_U]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_I]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_J]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_K]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_L]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior1.accion=TinputAccion::KEY_PODER;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_UP]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior1.accion=TinputAccion::KEY_NADA;
				return inputAnterior1;break;
			}break;
		};
		case TinputMovimiento::KEY_ABAJO: {
			if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_U]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_I]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_J]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_K]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_O]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior1.accion=TinputAccion::KEY_PROTECCION;
				return inputAnterior1;
			}else if(state[SDL_SCANCODE_DOWN]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior1.accion=TinputAccion::KEY_NADA;
				return inputAnterior1;break;
			}
		};
		case TinputMovimiento::KEY_ARRIBA_DERECHA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]&&(!state[SDL_SCANCODE_U]&&!state[SDL_SCANCODE_I]&&!state[SDL_SCANCODE_J]&&!state[SDL_SCANCODE_K]&&!state[SDL_SCANCODE_O]&&!state[SDL_SCANCODE_L])){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
				inputAnterior1.accion=TinputAccion::KEY_NADA;
				return inputAnterior1;
			}else if (state[SDL_SCANCODE_RIGHT]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_DERECHA;
				return inputAnterior1;break;
			}
		};
		case TinputMovimiento::KEY_ARRIBA_IZQUIERDA: {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]&&(!state[SDL_SCANCODE_U]&&!state[SDL_SCANCODE_I]&&!state[SDL_SCANCODE_J]&&!state[SDL_SCANCODE_K]&&!state[SDL_SCANCODE_O]&&!state[SDL_SCANCODE_L])){
				inputAnterior1.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
				inputAnterior1.accion=TinputAccion::KEY_NADA;
				return inputAnterior1;
			}else if (state[SDL_SCANCODE_LEFT]){
				inputAnterior1.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				inputAnterior1.accion=TinputAccion::KEY_NADA;
				return inputAnterior1;break;
			}
		};
		default: sigue=true;
	}
	if (sigue)
		switch(inputAnterior1.accion){
			case TinputAccion::KEY_PINIA_ALTA: {
				if (state[SDL_SCANCODE_U]){
					inputAnterior1.accion= TinputAccion::KEY_PINIA_ALTA;
					return inputAnterior1;
					break;
				}
			};
			case TinputAccion:: KEY_PINIA_BAJA: {
				if (state[SDL_SCANCODE_I]){
					inputAnterior1.accion = TinputAccion::KEY_PINIA_BAJA;
					return inputAnterior1; break;
				}
			};
			case TinputAccion::KEY_PATADA_ALTA: {
				if (state[SDL_SCANCODE_J]){
					inputAnterior1.accion = TinputAccion::KEY_PATADA_ALTA;
					return inputAnterior1; break;
				}
			};
			case TinputAccion::KEY_PATADA_BAJA: {
				if (state[SDL_SCANCODE_K]) {
					inputAnterior1.accion = TinputAccion::KEY_PATADA_BAJA;
					return inputAnterior1; break;
				}
			};
			case TinputAccion:: KEY_PROTECCION: {
				if (state[SDL_SCANCODE_O]) {
					inputAnterior1.accion =TinputAccion:: KEY_PROTECCION;
					return inputAnterior1; break;
				}
			};
			case TinputAccion::KEY_PODER: {
				if (state[SDL_SCANCODE_L]) {
					inputAnterior1.accion = TinputAccion::KEY_PODER;
					return inputAnterior1; break;
				}
			};
		}
	return aux;
}
/*
 * Devuelve la tecla anterior si se repite o la tecla nada si no se repite
 */
Tinput ControladorTeclado::esAnterior2(const Uint8 *state) {
	bool sigue=false;
	Tinput aux;
	switch (inputAnterior2.movimiento) {
		case TinputMovimiento::KEY_IZQUIERDA: {
			if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]&&(state[SDL_SCANCODE_F] ||state[SDL_SCANCODE_G]||state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B]||state[SDL_SCANCODE_H]||state[SDL_SCANCODE_N])){
				if(state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B]){
					inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
					return inputAnterior2;
				} else {
					inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
					return inputAnterior2;
				}

			}else if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
				inputAnterior2.accion=TinputAccion::KEY_NADA;
				return inputAnterior2;
			}else if (state[SDL_SCANCODE_A]&&state[SDL_SCANCODE_F]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
				return inputAnterior2;
			}else if (state[SDL_SCANCODE_A]&&state[SDL_SCANCODE_G]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				return inputAnterior2;
			}else if (state[SDL_SCANCODE_A]&&state[SDL_SCANCODE_V]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
				return inputAnterior2;
			}else if (state[SDL_SCANCODE_A]&&state[SDL_SCANCODE_B]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				return inputAnterior2;
			}
			else if (state[SDL_SCANCODE_A]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				inputAnterior2.accion=TinputAccion::KEY_NADA;
				return inputAnterior2; break;
			}
		};
		case TinputMovimiento::KEY_DERECHA: {
			if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]&&(state[SDL_SCANCODE_F] ||state[SDL_SCANCODE_G]||state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B]||state[SDL_SCANCODE_H]||state[SDL_SCANCODE_N])){
				if(state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B]){
					inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
					return inputAnterior2;
				} else {
					inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
					return inputAnterior2;
				}

			}else if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
				inputAnterior2.accion=TinputAccion::KEY_NADA;
				return inputAnterior2;
			}else if (state[SDL_SCANCODE_D]&&state[SDL_SCANCODE_F]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_DERECHA;
				inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
				return inputAnterior2;
			}else if (state[SDL_SCANCODE_D]&&state[SDL_SCANCODE_G]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_DERECHA;
				inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				return inputAnterior2;
			}else if (state[SDL_SCANCODE_D]&&state[SDL_SCANCODE_V]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_DERECHA;
				inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
				return inputAnterior2;
			}else if (state[SDL_SCANCODE_D]&&state[SDL_SCANCODE_B]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_DERECHA;
				inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				return inputAnterior2;
			}else if (state[SDL_SCANCODE_D]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_DERECHA;
				inputAnterior2.accion=TinputAccion::KEY_NADA;
				return inputAnterior2; break;
			}
		};
		case TinputMovimiento::KEY_ARRIBA: {
			if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]&&(state[SDL_SCANCODE_F] ||state[SDL_SCANCODE_G]||state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B]||state[SDL_SCANCODE_H]||state[SDL_SCANCODE_N])){
				if(state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B]){
					inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
					return inputAnterior2;
				} else {
					inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
					return inputAnterior2;
				}
			} else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]&&(state[SDL_SCANCODE_F] ||state[SDL_SCANCODE_G]||state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B]||state[SDL_SCANCODE_H]||state[SDL_SCANCODE_N])){
				if(state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B]){
					inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
					return inputAnterior1;
				} else {
					inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
					return inputAnterior2;
				}
			}else if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
				inputAnterior2.accion=TinputAccion::KEY_NADA;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
				inputAnterior2.accion=TinputAccion::KEY_NADA;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_F]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_G]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_V]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_B]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_N]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior2.accion=TinputAccion::KEY_PODER;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_W]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA;
				inputAnterior2.accion=TinputAccion::KEY_NADA;
				return inputAnterior2;break;
			}break;
		};
		case TinputMovimiento::KEY_ABAJO: {
			if(state[SDL_SCANCODE_S] && state[SDL_SCANCODE_F]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_S] && state[SDL_SCANCODE_G]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_S] && state[SDL_SCANCODE_V]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_S] && state[SDL_SCANCODE_B]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_S] && state[SDL_SCANCODE_N]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior2.accion=TinputAccion::KEY_PODER;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_S] && state[SDL_SCANCODE_H]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior2.accion=TinputAccion::KEY_PROTECCION;
				return inputAnterior2;
			}else if(state[SDL_SCANCODE_S]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ABAJO;
				inputAnterior2.accion=TinputAccion::KEY_NADA;
				return inputAnterior2;break;
			}
		};
		case TinputMovimiento::KEY_ARRIBA_DERECHA: {
			if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]&&(!state[SDL_SCANCODE_F]&&!state[SDL_SCANCODE_G]&&!state[SDL_SCANCODE_V]&&!state[SDL_SCANCODE_B]&&!state[SDL_SCANCODE_H]&&!state[SDL_SCANCODE_N])){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
				return inputAnterior2;
			}else if (state[SDL_SCANCODE_D]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_DERECHA;
				return inputAnterior2;break;
			}
		};
		case TinputMovimiento::KEY_ARRIBA_IZQUIERDA: {
			if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]&&(!state[SDL_SCANCODE_F]&&!state[SDL_SCANCODE_G]&&!state[SDL_SCANCODE_V]&&!state[SDL_SCANCODE_B]&&!state[SDL_SCANCODE_H]&&!state[SDL_SCANCODE_N])){
				inputAnterior2.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
				return inputAnterior2;
			}else if (state[SDL_SCANCODE_A]){
				inputAnterior2.movimiento=TinputMovimiento::KEY_IZQUIERDA;
				return inputAnterior2;break;
			}
		};
		default: sigue=true;
	}
	if (sigue)
		switch(inputAnterior1.accion){
			case TinputAccion::KEY_PINIA_ALTA: {
				if (state[SDL_SCANCODE_F]){
					inputAnterior2.accion= TinputAccion::KEY_PINIA_ALTA;
					return inputAnterior2;
					break;
				}
			};
			case TinputAccion:: KEY_PINIA_BAJA: {
				if (state[SDL_SCANCODE_G]){
					inputAnterior2.accion = TinputAccion::KEY_PINIA_BAJA;
					return inputAnterior2; break;
				}
			};
			case TinputAccion::KEY_PATADA_ALTA: {
				if (state[SDL_SCANCODE_V]){
					inputAnterior2.accion = TinputAccion::KEY_PATADA_ALTA;
					return inputAnterior2; break;
				}
			};
			case TinputAccion::KEY_PATADA_BAJA: {
				if (state[SDL_SCANCODE_B]) {
					inputAnterior2.accion = TinputAccion::KEY_PATADA_BAJA;
					return inputAnterior2; break;
				}
			};
			case TinputAccion:: KEY_PROTECCION: {
				if (state[SDL_SCANCODE_H]) {
					inputAnterior2.accion =TinputAccion:: KEY_PROTECCION;
					return inputAnterior2; break;
				}
			};
			case TinputAccion::KEY_PODER: {
				if (state[SDL_SCANCODE_N]) {
					inputAnterior2.accion = TinputAccion::KEY_PODER;
					return inputAnterior2; break;
				}
			};
		}
	return aux;
}

vector<Tinput> ControladorTeclado::getInputs() {

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	vector<Tinput> inputs;
	Tinput aux;
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {}
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			aux.game=TinputGame::KEY_EXIT;
			inputs.clear();
			inputs.push_back(aux);
			return inputs;

			// Solo captura el evento cuando suelta R
		case SDL_KEYUP: {
			if (event.key.keysym.sym == SDLK_r) {
				aux.game=TinputGame::KEY_RESTART;
				inputs.clear();
				inputs.push_back(aux);
				return inputs;
			} else if (event.key.keysym.sym == SDLK_SPACE) {
				// TODO - SEBASTIAN. Deberia capturar el enter...no se fijate que onda. Esto se puede (y debe) cambiar
				aux.game = TinputGame::KEY_ENTER;
				inputs.clear();
				inputs.push_back(aux);
				inputs.push_back(aux);
				return inputs;
			}
		};
		default:
			Tinput anterior1 = esAnterior1(state);
			Tinput anterior2 = esAnterior2(state);
			if ((anterior1.accion !=TinputAccion:: KEY_NADA || anterior1.movimiento != TinputMovimiento::KEY_NADA) &&(anterior2.accion != TinputAccion::KEY_NADA|| anterior2.movimiento != TinputMovimiento::KEY_NADA)) {
				inputs.clear();
				inputs.push_back(anterior1);
				inputs.push_back(anterior2);
				return inputs;
			} else if (anterior1.accion != TinputAccion::KEY_NADA ||anterior1.movimiento != TinputMovimiento::KEY_NADA ) {
				inputs.clear();
				inputAnterior2.accion=TinputAccion::KEY_NADA;inputAnterior2.movimiento=TinputMovimiento::KEY_NADA;inputAnterior2.game=TinputGame::KEY_NADA;
				if (state[SDL_SCANCODE_D]) inputAnterior2.movimiento = TinputMovimiento::KEY_DERECHA;
				else if (state[SDL_SCANCODE_A]) inputAnterior2.movimiento = TinputMovimiento::KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_W]) inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
				else if (state[SDL_SCANCODE_S]) inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
				else if (state[SDL_SCANCODE_F]){
					inputAnterior2.accion = TinputAccion::KEY_PINIA_ALTA;
					inputAnterior2.movimiento = TinputMovimiento::KEY_NADA;
				}
				else if (state[SDL_SCANCODE_G]){
					inputAnterior2.accion = TinputAccion::KEY_PINIA_BAJA;
					inputAnterior2.movimiento = TinputMovimiento::KEY_NADA;
				}
				else if (state[SDL_SCANCODE_V]){
					inputAnterior2.accion =TinputAccion:: KEY_PATADA_ALTA;
					inputAnterior2.movimiento = TinputMovimiento::KEY_NADA;
				}
				else if (state[SDL_SCANCODE_B]){
					inputAnterior2.accion = TinputAccion::KEY_PATADA_BAJA;
					inputAnterior2.movimiento = TinputMovimiento::KEY_NADA;
				}
				else if (state[SDL_SCANCODE_H]) {
					inputAnterior2.accion= TinputAccion::KEY_PROTECCION;
					inputAnterior2.movimiento = TinputMovimiento::KEY_NADA;
				}
				else if (state[SDL_SCANCODE_N]) {
					inputAnterior2.accion = TinputAccion::KEY_PODER;
					inputAnterior2.movimiento = TinputMovimiento::KEY_NADA;
				}
				else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_F]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
				}else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_G]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_V]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
				}else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_B]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_H]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PODER;
				}else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_N]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PROTECCION;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_F]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_G]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_V]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_B]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_H]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PODER;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_N]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PROTECCION;
				}else if(state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_A]&&(state[SDL_SCANCODE_F]||state[SDL_SCANCODE_G])){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if(state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_A]&&(state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B])){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if(state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_D]&&(state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B])){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if(state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_D]&&(state[SDL_SCANCODE_F]||state[SDL_SCANCODE_G])){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				}
				else {inputAnterior2.accion=TinputAccion::KEY_NADA;inputAnterior2.movimiento=TinputMovimiento::KEY_NADA;inputAnterior2.game=TinputGame::KEY_NADA;}
				inputs.push_back(anterior1);
				inputs.push_back(inputAnterior2);
				return inputs;

			} else if (anterior2.accion != TinputAccion::KEY_NADA ||anterior2.movimiento != TinputMovimiento::KEY_NADA ) {
				inputs.clear();
				inputAnterior1.accion=TinputAccion::KEY_NADA;inputAnterior1.movimiento=TinputMovimiento::KEY_NADA;inputAnterior1.game=TinputGame::KEY_NADA;
				if (state[SDL_SCANCODE_RIGHT]) inputAnterior1.movimiento = TinputMovimiento::KEY_DERECHA;
				else if (state[SDL_SCANCODE_LEFT]) inputAnterior1.movimiento = TinputMovimiento::KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_UP]) inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
				else if (state[SDL_SCANCODE_DOWN]) inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
				else if (state[SDL_SCANCODE_U]){
					inputAnterior1.accion = TinputAccion::KEY_PINIA_ALTA;
					inputAnterior1.movimiento = TinputMovimiento::KEY_NADA;
				}
				else if (state[SDL_SCANCODE_I]){
					inputAnterior1.accion = TinputAccion::KEY_PINIA_BAJA;
					inputAnterior1.movimiento = TinputMovimiento::KEY_NADA;
				}
				else if (state[SDL_SCANCODE_J]){
					inputAnterior1.accion =TinputAccion:: KEY_PATADA_ALTA;
					inputAnterior1.movimiento = TinputMovimiento::KEY_NADA;
				}
				else if (state[SDL_SCANCODE_K]){
					inputAnterior1.accion = TinputAccion::KEY_PATADA_BAJA;
					inputAnterior1.movimiento = TinputMovimiento::KEY_NADA;
				}
				else if (state[SDL_SCANCODE_O]){
					inputAnterior1.accion= TinputAccion::KEY_PROTECCION;
					inputAnterior1.movimiento = TinputMovimiento::KEY_NADA;
				}
				else if (state[SDL_SCANCODE_L]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_NADA;
					inputAnterior1.accion = TinputAccion::KEY_PODER;
				}
				else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_U]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
				}else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_I]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_J]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
				}else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_K]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_O]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PODER;
				}else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_L]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PROTECCION;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_U]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_I]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_J]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_K]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_O]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PODER;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_L]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PROTECCION;
				}else if(state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_LEFT]&&(state[SDL_SCANCODE_U]||state[SDL_SCANCODE_I])){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if(state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_LEFT]&&(state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K])){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if(state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_RIGHT]&&(state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K])){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if(state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_RIGHT]&&(state[SDL_SCANCODE_U]||state[SDL_SCANCODE_I])){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				}
				else {inputAnterior1.accion=TinputAccion::KEY_NADA;inputAnterior1.movimiento=TinputMovimiento::KEY_NADA;inputAnterior1.game=TinputGame::KEY_NADA;}
				inputs.push_back(inputAnterior1);
				inputs.push_back(anterior2);
				return inputs;
			} else {
				inputs.clear();
				inputAnterior1.accion=TinputAccion::KEY_NADA;inputAnterior1.movimiento=TinputMovimiento::KEY_NADA;inputAnterior1.game=TinputGame::KEY_NADA;
				if (state[SDL_SCANCODE_RIGHT]) inputAnterior1.movimiento = TinputMovimiento::KEY_DERECHA;
				else if (state[SDL_SCANCODE_LEFT]) inputAnterior1.movimiento = TinputMovimiento::KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_UP]) inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
				else if (state[SDL_SCANCODE_DOWN]) inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT]) inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT]) inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
				else if (state[SDL_SCANCODE_U]) inputAnterior1.accion = TinputAccion::KEY_PINIA_ALTA;
				else if (state[SDL_SCANCODE_I]) inputAnterior1.accion = TinputAccion::KEY_PINIA_BAJA;
				else if (state[SDL_SCANCODE_J]) inputAnterior1.accion =TinputAccion:: KEY_PATADA_ALTA;
				else if (state[SDL_SCANCODE_K]) inputAnterior1.accion = TinputAccion::KEY_PATADA_BAJA;
				else if (state[SDL_SCANCODE_O]) inputAnterior1.accion= TinputAccion::KEY_PROTECCION;
				else if (state[SDL_SCANCODE_L]) inputAnterior1.accion = TinputAccion::KEY_PODER;
				else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_U]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
				}else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_I]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_J]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
				}else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_K]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_O]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PODER;
				}else if (state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_L]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior1.accion=TinputAccion::KEY_PROTECCION;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_U]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_ALTA;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_I]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_J]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_ALTA;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_K]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_O]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PODER;
				}else if (state[SDL_SCANCODE_DOWN]&&state[SDL_SCANCODE_L]){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior1.accion=TinputAccion::KEY_PROTECCION;
				}else if(state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_LEFT]&&(state[SDL_SCANCODE_U]||state[SDL_SCANCODE_I])){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if(state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_LEFT]&&(state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K])){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if(state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_RIGHT]&&(state[SDL_SCANCODE_J]||state[SDL_SCANCODE_K])){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior1.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if(state[SDL_SCANCODE_UP]&&state[SDL_SCANCODE_RIGHT]&&(state[SDL_SCANCODE_U]||state[SDL_SCANCODE_I])){
					inputAnterior1.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior1.accion=TinputAccion::KEY_PINIA_BAJA;
				}
				else {inputAnterior1.accion=TinputAccion::KEY_NADA;inputAnterior1.movimiento=TinputMovimiento::KEY_NADA;inputAnterior1.game=TinputGame::KEY_NADA;}
				inputAnterior2.accion=TinputAccion::KEY_NADA;inputAnterior2.movimiento=TinputMovimiento::KEY_NADA;inputAnterior2.game=TinputGame::KEY_NADA;
				if (state[SDL_SCANCODE_D]) inputAnterior2.movimiento = TinputMovimiento::KEY_DERECHA;
				else if (state[SDL_SCANCODE_A]) inputAnterior2.movimiento = TinputMovimiento::KEY_IZQUIERDA;
				else if (state[SDL_SCANCODE_W]) inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
				else if (state[SDL_SCANCODE_S]) inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
				else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
				else if (state[SDL_SCANCODE_F]) inputAnterior2.accion = TinputAccion::KEY_PINIA_ALTA;
				else if (state[SDL_SCANCODE_G]) inputAnterior2.accion = TinputAccion::KEY_PINIA_BAJA;
				else if (state[SDL_SCANCODE_V]) inputAnterior2.accion =TinputAccion:: KEY_PATADA_ALTA;
				else if (state[SDL_SCANCODE_B]) inputAnterior2.accion = TinputAccion::KEY_PATADA_BAJA;
				else if (state[SDL_SCANCODE_H]) inputAnterior2.accion= TinputAccion::KEY_PROTECCION;
				else if (state[SDL_SCANCODE_N]) inputAnterior2.accion = TinputAccion::KEY_PODER;
				else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_F]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
				}else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_G]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_V]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
				}else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_B]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_H]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PODER;
				}else if (state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_N]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA;
					inputAnterior2.accion=TinputAccion::KEY_PROTECCION;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_F]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_ALTA;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_G]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_V]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_ALTA;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_B]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_H]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PODER;
				}else if (state[SDL_SCANCODE_S]&&state[SDL_SCANCODE_N]){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ABAJO;
					inputAnterior2.accion=TinputAccion::KEY_PROTECCION;
				}else if(state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_A]&&(state[SDL_SCANCODE_F]||state[SDL_SCANCODE_G])){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				}else if(state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_A]&&(state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B])){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if(state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_D]&&(state[SDL_SCANCODE_V]||state[SDL_SCANCODE_B])){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior2.accion=TinputAccion::KEY_PATADA_BAJA;
				}else if(state[SDL_SCANCODE_W]&&state[SDL_SCANCODE_D]&&(state[SDL_SCANCODE_F]||state[SDL_SCANCODE_G])){
					inputAnterior2.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
					inputAnterior2.accion=TinputAccion::KEY_PINIA_BAJA;
				}
				else {inputAnterior2.accion=TinputAccion::KEY_NADA;inputAnterior2.movimiento=TinputMovimiento::KEY_NADA;inputAnterior2.game=TinputGame::KEY_NADA;}
				inputs.push_back(inputAnterior1);
				inputs.push_back(inputAnterior2);
				return inputs;
			}
	}
};