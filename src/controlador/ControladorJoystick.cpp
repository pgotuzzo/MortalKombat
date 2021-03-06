
#include "ControladorJoystick.h"


ControladorJoystick::ControladorJoystick(Tbotones botones) {

    highKick=botones.highKick;
    highPunch=botones.highPunch;
    lowKick=botones.lowKick;
    lowPunch=botones.lowPunch;
    poder=botones.poder;
    proteccion=botones.proteccion;
    if( SDL_NumJoysticks() < 1 ){
        string mensajeError="No hay joystick conectado.";
        loguer->loguear(mensajeError.c_str(),Log::LOG_ERR);

    }
    else{
        //carga joystick
        player1 = SDL_JoystickOpen( 0 );
        if( player1 == NULL ){
            string mensajeError="No se puede abrir.";
            loguer->loguear(mensajeError.c_str(),Log::LOG_ERR);
        }
        player2 = SDL_JoystickOpen( 1 );
        if( player1 == NULL ){
            string mensajeError="No se puede abrir. ";
            loguer->loguear(mensajeError.c_str(),Log::LOG_ERR);
        }
    }
}
Tinput ControladorJoystick::inputAnteriorX(SDL_Joystick*playerX){
    if(playerX==player1){
        return this->inputAnterior1;}
    else
    if(playerX==player2)
        return this->inputAnterior2;
}

/*
 * Devuelve la tecla anterior si se repite o la tecla nada si no se repite
 */
Tinput ControladorJoystick::esAnterior(SDL_Joystick* playerX,SDL_Event event) {
    Tinput aux=inputAnteriorX(playerX);
    Tinput retorno;
    switch (aux.movimiento) {
        case TinputMovimiento::KEY_IZQUIERDA: {
            if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&& (SDL_JoystickGetButton(playerX, lowKick) || SDL_JoystickGetButton(playerX, highKick) || SDL_JoystickGetButton(playerX, lowPunch) || SDL_JoystickGetButton(playerX, highPunch) || SDL_JoystickGetButton(playerX, proteccion)|| SDL_JoystickGetButton(playerX, poder))){
                if((SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))&& event.type==SDL_JOYBUTTONDOWN){
                    retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;

                    retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }else {
                    if((SDL_JoystickGetButton(playerX, lowPunch)||SDL_JoystickGetButton(playerX, highPunch))&&event.type==SDL_JOYBUTTONDOWN){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                        retorno.accion=TinputAccion::KEY_PINIA_ALTA;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;
                    }else if(SDL_JoystickGetButton(playerX, proteccion)){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                        retorno.accion=TinputAccion::KEY_PROTECCION;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;break;
                    }
                }
            } else if(SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, lowKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                retorno.accion=TinputAccion::KEY_PATADA_BAJA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, highKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;

                retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, highPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;

                retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, lowPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;

                retorno.accion=TinputAccion::KEY_PINIA_BAJA;
                guardarAnteriorX(playerX,retorno);
                return retorno;


            }else if(SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, poder)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.accion=TinputAccion::KEY_PODER;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, proteccion)){
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                retorno.accion=TinputAccion::KEY_PROTECCION;

                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)){
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;

                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }
        };
        case TinputMovimiento::KEY_DERECHA:{
            if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&& (SDL_JoystickGetButton(playerX, lowKick) || SDL_JoystickGetButton(playerX, highKick) || SDL_JoystickGetButton(playerX, lowPunch) || SDL_JoystickGetButton(playerX, highPunch)||SDL_JoystickGetButton(playerX, proteccion))){
                if((SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))&& event.type==SDL_JOYBUTTONDOWN){
                    retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                    retorno.accion=TinputAccion::KEY_PATADA_ALTA;

                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }else {
                    if((SDL_JoystickGetButton(playerX, lowPunch)||SDL_JoystickGetButton(playerX, highPunch))&&event.type==SDL_JOYBUTTONDOWN){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        retorno.accion=TinputAccion::KEY_PINIA_ALTA;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;
                    }else if(SDL_JoystickGetButton(playerX, proteccion)){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        retorno.accion=TinputAccion::KEY_PROTECCION;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;break;
                    }
                }
            } else if(SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;

                guardarAnteriorX(playerX,retorno);break;
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, lowKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;

                retorno.accion=TinputAccion::KEY_PATADA_BAJA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, highKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;
                retorno.accion=TinputAccion::KEY_PATADA_ALTA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, highPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;
                retorno.accion=TinputAccion::KEY_PINIA_ALTA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, lowPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;

                retorno.accion=TinputAccion::KEY_PINIA_BAJA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if(SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, poder)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.accion=TinputAccion::KEY_PODER;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, proteccion)){
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;
                retorno.accion=TinputAccion::KEY_PROTECCION;

                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)){
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;

                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }
        };
        case TinputMovimiento::KEY_ARRIBA: {
            if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&& (SDL_JoystickGetButton(playerX, lowKick) || SDL_JoystickGetButton(playerX, highKick) || SDL_JoystickGetButton(playerX, lowPunch) || SDL_JoystickGetButton(playerX, highPunch)||SDL_JoystickGetButton(playerX, proteccion))){
                if((SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))&& event.type==SDL_JOYBUTTONDOWN){
                    retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                    retorno.accion=TinputAccion::KEY_PATADA_ALTA;

                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }else {
                    if((SDL_JoystickGetButton(playerX, lowPunch)||SDL_JoystickGetButton(playerX, highPunch))&&event.type==SDL_JOYBUTTONDOWN){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        retorno.accion=TinputAccion::KEY_PINIA_ALTA;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;
                    }else if(SDL_JoystickGetButton(playerX, proteccion)){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        retorno.accion=TinputAccion::KEY_PROTECCION;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;break;
                    }
                }
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&& (SDL_JoystickGetButton(playerX, lowKick) || SDL_JoystickGetButton(playerX, highKick) || SDL_JoystickGetButton(playerX, lowPunch) || SDL_JoystickGetButton(playerX, highPunch)||SDL_JoystickGetButton(playerX, proteccion))){
                if((SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))&& event.type==SDL_JOYBUTTONDOWN){
                    retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                    retorno.accion=TinputAccion::KEY_PATADA_ALTA;

                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }else {
                    if((SDL_JoystickGetButton(playerX, lowPunch)||SDL_JoystickGetButton(playerX, highPunch))&&event.type==SDL_JOYBUTTONDOWN){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                        retorno.accion=TinputAccion::KEY_PINIA_ALTA;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;
                    }else if(SDL_JoystickGetButton(playerX, proteccion)){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                        retorno.accion=TinputAccion::KEY_PROTECCION;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;break;
                    }
                }
            } else if(SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            } else if(SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if(SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, lowKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA;

                retorno.accion=TinputAccion::KEY_PATADA_BAJA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, highKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA;

                retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, highPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA;

                retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, lowPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA;
                retorno.accion=TinputAccion::KEY_PINIA_BAJA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, proteccion)){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA;
                retorno.accion=TinputAccion::KEY_PROTECCION;
                guardarAnteriorX(playerX,retorno);

                return retorno;break;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA;
                guardarAnteriorX(playerX,retorno);

                return retorno;break;
            }
        };
        case TinputMovimiento::KEY_ABAJO: {
            if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, lowKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;

                retorno.accion=TinputAccion::KEY_PATADA_BAJA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, highKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;
                retorno.accion=TinputAccion::KEY_PATADA_ALTA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, highPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;
                retorno.accion=TinputAccion::KEY_PINIA_ALTA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, lowPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;
                retorno.accion=TinputAccion::KEY_PINIA_BAJA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, proteccion)){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;
                retorno.accion=TinputAccion::KEY_PROTECCION;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;

                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }
        };
        case TinputMovimiento::KEY_ARRIBA_DERECHA: {
            if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&& (!SDL_JoystickGetButton(playerX, lowKick) && !SDL_JoystickGetButton(playerX, highKick) && !SDL_JoystickGetButton(playerX, lowPunch) && !SDL_JoystickGetButton(playerX, highPunch) && !SDL_JoystickGetButton(playerX, proteccion)&& !SDL_JoystickGetButton(playerX, poder))) {
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&& (SDL_JoystickGetButton(playerX, lowKick) || SDL_JoystickGetButton(playerX, highKick) || SDL_JoystickGetButton(playerX, lowPunch) || SDL_JoystickGetButton(playerX, highPunch)||SDL_JoystickGetButton(playerX, proteccion))){
                if((SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))&& event.type==SDL_JOYBUTTONDOWN){
                    retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                    retorno.accion=TinputAccion::KEY_PATADA_ALTA;

                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }else {
                    if((SDL_JoystickGetButton(playerX, lowPunch)||SDL_JoystickGetButton(playerX, highPunch))&&event.type==SDL_JOYBUTTONDOWN){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        retorno.accion=TinputAccion::KEY_PINIA_ALTA;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;
                    }else if(SDL_JoystickGetButton(playerX, proteccion)){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        retorno.accion=TinputAccion::KEY_PROTECCION;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;break;
                    }
                }
            } else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, proteccion)) {
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;
                retorno.accion=TinputAccion::KEY_PROTECCION;

                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)) {
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;

                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }

        };
        case TinputMovimiento::KEY_ARRIBA_IZQUIERDA: {
            if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX,FLECHA_IZQUIERDA )&& (!SDL_JoystickGetButton(playerX, lowKick) && !SDL_JoystickGetButton(playerX, highKick) && !SDL_JoystickGetButton(playerX, lowPunch) && !SDL_JoystickGetButton(playerX, highPunch) && !SDL_JoystickGetButton(playerX, proteccion)&& !SDL_JoystickGetButton(playerX, poder))) {
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;

                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&& (SDL_JoystickGetButton(playerX, lowKick) || SDL_JoystickGetButton(playerX, highKick) || SDL_JoystickGetButton(playerX, lowPunch) || SDL_JoystickGetButton(playerX, highPunch)|| SDL_JoystickGetButton(playerX, proteccion) || SDL_JoystickGetButton(playerX, poder))){
                if((SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))&& event.type==SDL_JOYBUTTONDOWN){
                    retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                    retorno.accion=TinputAccion::KEY_PATADA_ALTA;

                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }else {
                    if((SDL_JoystickGetButton(playerX, lowPunch)||SDL_JoystickGetButton(playerX, highPunch))&&event.type==SDL_JOYBUTTONDOWN){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                        retorno.accion=TinputAccion::KEY_PINIA_ALTA;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;
                    }else if(SDL_JoystickGetButton(playerX, proteccion)){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                        retorno.accion=TinputAccion::KEY_PROTECCION;

                        guardarAnteriorX(playerX,retorno);
                        return retorno;break;
                    }
                }
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, proteccion)) {
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                retorno.accion=TinputAccion::KEY_PROTECCION;

                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)) {
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;

                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }
        };


    }
    return retorno;
}


void ControladorJoystick::guardarAnteriorX(SDL_Joystick* playerX,Tinput anterior){
    if(playerX==player1)
        this->inputAnterior1=anterior;
    else
    if(playerX==player2)
        inputAnterior2=anterior;
}

void ControladorJoystick::setInputAnteriorX(SDL_Joystick* playerX,Tinput& auxInputX,SDL_Event event){
    auxInputX.accion=TinputAccion::KEY_NADA;auxInputX.movimiento=TinputMovimiento::KEY_NADA;auxInputX.game=TinputGame::KEY_NADA;
    if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)) auxInputX.movimiento = TinputMovimiento::KEY_DERECHA;
    else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)) auxInputX.movimiento = TinputMovimiento::KEY_IZQUIERDA;
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)) auxInputX.movimiento = TinputMovimiento::KEY_ARRIBA;
    else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)) auxInputX.movimiento = TinputMovimiento::KEY_ABAJO;
    else if (SDL_JoystickGetButton(playerX, lowKick) && event.type==SDL_JOYBUTTONDOWN) auxInputX.accion = TinputAccion::KEY_PATADA_BAJA;
    else if (SDL_JoystickGetButton(playerX, highKick)&& event.type==SDL_JOYBUTTONDOWN) auxInputX.accion = TinputAccion::KEY_PATADA_ALTA;
    else if (SDL_JoystickGetButton(playerX, highPunch)&& event.type==SDL_JOYBUTTONDOWN) auxInputX.accion = TinputAccion::KEY_PINIA_ALTA;
    else if (SDL_JoystickGetButton(playerX, lowPunch)&& event.type==SDL_JOYBUTTONDOWN) auxInputX.accion = TinputAccion::KEY_PINIA_BAJA;
    else if (SDL_JoystickGetButton(playerX, proteccion))auxInputX.accion = TinputAccion::KEY_PROTECCION;
    else if (SDL_JoystickGetButton(playerX, poder)&& event.type==SDL_JOYBUTTONDOWN)auxInputX.accion = TinputAccion::KEY_PODER;
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, lowKick)){
        auxInputX.movimiento = TinputMovimiento::KEY_ARRIBA;
        auxInputX.accion=TinputAccion::KEY_PATADA_BAJA;
    }
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, highKick)){
        auxInputX.movimiento = TinputMovimiento::KEY_ARRIBA;

        auxInputX.accion=TinputAccion::KEY_PATADA_ALTA;
    }
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, lowPunch)){
        auxInputX.movimiento = TinputMovimiento::KEY_ARRIBA;
        auxInputX.accion=TinputAccion::KEY_PINIA_BAJA;
    }
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, highPunch)){
        auxInputX.movimiento = TinputMovimiento::KEY_ARRIBA;
        auxInputX.accion=TinputAccion::KEY_PINIA_ALTA;
    }
    else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, lowPunch)){
        auxInputX.movimiento =TinputMovimiento:: KEY_ABAJO;
        auxInputX.accion=TinputAccion::KEY_PINIA_BAJA;
    }
    else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, highPunch)){
        auxInputX.movimiento = TinputMovimiento::KEY_ABAJO;
        auxInputX.accion=TinputAccion::KEY_PINIA_ALTA;
    }
    else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, lowKick)){
        auxInputX.movimiento =TinputMovimiento:: KEY_ABAJO;
        auxInputX.accion=TinputAccion::KEY_PATADA_BAJA;
    }
    else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, highKick)){
        auxInputX.movimiento = TinputMovimiento::KEY_ABAJO;
        auxInputX.accion=TinputAccion::KEY_PATADA_ALTA;
    }

    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)) auxInputX.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)) auxInputX.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&(SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))){
        auxInputX.movimiento =TinputMovimiento:: KEY_ARRIBA_DERECHA;
        auxInputX.accion=TinputAccion::KEY_PATADA_BAJA;
    }
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&(SDL_JoystickGetButton(playerX, lowPunch)||SDL_JoystickGetButton(playerX, highPunch))){
        auxInputX.movimiento = TinputMovimiento::KEY_ARRIBA_DERECHA;
        auxInputX.accion=TinputAccion::KEY_PINIA_BAJA;
    }
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&(SDL_JoystickGetButton(playerX, lowPunch)||SDL_JoystickGetButton(playerX, highPunch))){
        auxInputX.movimiento =TinputMovimiento:: KEY_ARRIBA_IZQUIERDA;
        auxInputX.accion=TinputAccion::KEY_PINIA_BAJA;
    }
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&(SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))){
        auxInputX.movimiento = TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
        auxInputX.accion=TinputAccion::KEY_PATADA_BAJA;
    }
    else {auxInputX.movimiento = TinputMovimiento::KEY_NADA;
        auxInputX.accion = TinputAccion::KEY_NADA;
        auxInputX.game = TinputGame::KEY_NADA;
    }

}

vector<Tinput> ControladorJoystick::getInputs(SDL_Event &event) {

    vector<Tinput> inputs;


    //SDL_Event event;
    SDL_Event auxE;
    Tinput aux;
    //while (SDL_PollEvent(&event) != 0) {}
    //SDL_PollEvent(&event);
    auxE=event;
    switch (event.type) {
        case SDL_QUIT:
            aux.game=TinputGame::KEY_EXIT;
            inputs.clear();
            inputs.push_back(aux);
            return inputs;

            // Solo captura el evento cuando suelta R
        case SDL_JOYBUTTONUP:{ if (event.jbutton.button == 0) {
                aux.game=TinputGame::KEY_RESTART;
                inputs.clear();
                inputs.push_back(aux);
                return inputs;
            }
        };
        case SDL_KEYUP: {
            if (event.key.keysym.sym == SDLK_r) {
                aux.game=TinputGame::KEY_RESTART;
                inputs.clear();
                inputs.push_back(aux);
                return inputs;
            }
        };

        default:
            Tinput anterior1 = esAnterior(player1,event);
            Tinput anterior2 = esAnterior(player2,event);
            if ((anterior1.accion !=TinputAccion:: KEY_NADA || anterior1.movimiento != TinputMovimiento::KEY_NADA) &&(anterior2.accion != TinputAccion::KEY_NADA|| anterior2.movimiento != TinputMovimiento::KEY_NADA)) {
                inputs.clear();
                inputs.push_back(anterior1);
                inputs.push_back(anterior2);
                return inputs;
            } else if (anterior1.accion != TinputAccion::KEY_NADA ||anterior1.movimiento != TinputMovimiento::KEY_NADA ) {
                inputs.clear();
                setInputAnteriorX(player2,inputAnterior2,auxE);
                inputs.push_back(anterior1);
                inputs.push_back(inputAnterior2);
                return inputs;

            } else if (anterior2.accion != TinputAccion::KEY_NADA || anterior2.movimiento != TinputMovimiento::KEY_NADA ) {
                inputs.clear();
                setInputAnteriorX(player1,inputAnterior1,auxE);
                inputs.push_back(inputAnterior1);
                inputs.push_back(anterior2);
                return inputs;
            } else {

                setInputAnteriorX(player1,inputAnterior1,auxE);
                setInputAnteriorX(player2,inputAnterior2,auxE);

                inputs.clear();
                inputs.push_back(inputAnterior1);
                inputs.push_back(inputAnterior2);
                return inputs;
            }
    }
}
/*void  ControladorJoystick::vibrar(){

    haptic = SDL_HapticOpen( 0 );

    if (haptic == NULL){
        string mensajeError="No se puede abrir haptic.";
        loguer->loguear(mensajeError.c_str(),Log::LOG_ERR);
    }
    // inicializa
    if (SDL_HapticRumbleInit( haptic ) != 0){
        string mensajeError="No se puede abrir haptic, vibración.";
        loguer->loguear(mensajeError.c_str(),Log::LOG_ERR);
    }


    // abre vibracion
    haptic = SDL_HapticOpenFromJoystick( player1 );

    if (haptic == NULL) {
        string mensajeError="Joystick sin vibración.";
        loguer->loguear(mensajeError.c_str(),Log::LOG_ERR);
    }

    if ((SDL_HapticQuery(haptic) & SDL_HAPTIC_SINE)==0) {
        SDL_HapticClose(haptic); // efector sine
        string mensajeError="Joystick sin sine effect.";
        loguer->loguear(mensajeError.c_str(),Log::LOG_ERR);
    }

    memset( &effect, 0, sizeof(SDL_HapticEffect) ); //
    effect.type = SDL_HAPTIC_SINE;
    effect.periodic.direction.type = SDL_HAPTIC_POLAR; // coordenadas polares
    effect.periodic.direction.dir[0] = 18000; // efecto de direccion de fuerza
    effect.periodic.period = 10; // ms
    effect.periodic.magnitude = 32767; // 20000/32767 fuerza
    effect.periodic.length = 150; // largo
    effect.periodic.attack_length = 10; // aceleracion
    effect.periodic.fade_length = 10; // desaceleracion

    // Upload the effect
    effect_id = SDL_HapticNewEffect( haptic, &effect );

    // hace el efecto
    SDL_HapticRunEffect( haptic, effect_id, 1 );
    // espera a q termine
    SDL_Delay(150);

    //se destruye aunq siga vibrando
    SDL_HapticDestroyEffect( haptic, effect_id );

    // cierra
    SDL_HapticClose(haptic);

}*/


void ControladorJoystick::cerrarJoysticks() {
    SDL_JoystickClose(player1);
    SDL_JoystickClose(player2);
}

vector<Tinput> ControladorJoystick::getInputs() {
    vector<Tinput> inputs;


    SDL_Event event;
    SDL_Event auxE;
    Tinput aux;
    while (SDL_PollEvent(&event) != 0) {}
    SDL_PollEvent(&event);
    auxE=event;
    switch (event.type) {
        case SDL_QUIT:
            aux.game=TinputGame::KEY_EXIT;
            inputs.clear();
            inputs.push_back(aux);
            return inputs;

            // Solo captura el evento cuando suelta R
        case SDL_JOYBUTTONUP:{ if (event.jbutton.button == 0) {
                aux.game=TinputGame::KEY_RESTART;
                inputs.clear();
                inputs.push_back(aux);
                return inputs;
            }
        };
        case SDL_KEYUP: {
            if (event.key.keysym.sym == SDLK_r) {
                aux.game=TinputGame::KEY_RESTART;
                inputs.clear();
                inputs.push_back(aux);
                return inputs;
            }
        };

        default:
            Tinput anterior1 = esAnterior(player1,event);
            Tinput anterior2 = esAnterior(player2,event);
            if ((anterior1.accion !=TinputAccion:: KEY_NADA || anterior1.movimiento != TinputMovimiento::KEY_NADA) &&(anterior2.accion != TinputAccion::KEY_NADA|| anterior2.movimiento != TinputMovimiento::KEY_NADA)) {
                inputs.clear();
                inputs.push_back(anterior1);
                inputs.push_back(anterior2);
                return inputs;
            } else if (anterior1.accion != TinputAccion::KEY_NADA ||anterior1.movimiento != TinputMovimiento::KEY_NADA ) {
                inputs.clear();
                setInputAnteriorX(player2,inputAnterior2,auxE);
                inputs.push_back(anterior1);
                inputs.push_back(inputAnterior2);
                return inputs;

            } else if (anterior2.accion != TinputAccion::KEY_NADA || anterior2.movimiento != TinputMovimiento::KEY_NADA ) {
                inputs.clear();
                setInputAnteriorX(player1,inputAnterior1,auxE);
                inputs.push_back(inputAnterior1);
                inputs.push_back(anterior2);
                return inputs;
            } else {

                setInputAnteriorX(player1,inputAnterior1,auxE);
                setInputAnteriorX(player2,inputAnterior2,auxE);

                inputs.clear();
                inputs.push_back(inputAnterior1);
                inputs.push_back(inputAnterior2);
                return inputs;
            }
    }
}
