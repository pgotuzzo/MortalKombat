
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
                    cout<<"11111111111"<<endl;
                    retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }else {
                    if(event.type==SDL_JOYBUTTONDOWN){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                        retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                        cout<<"2222222222"<<endl;
                        guardarAnteriorX(playerX,retorno);
                        return retorno;
                    }
                }
            } else if(SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                cout<<"3333333333"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, lowKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                retorno.accion=TinputAccion::KEY_PATADA_BAJA;
                cout<<"444444444444444"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, highKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                cout<<"55555555555555"<<endl;
                retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, highPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                cout<<"6666666666666666666"<<endl;
                retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, lowPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                cout<<"777777777777777"<<endl;
                retorno.accion=TinputAccion::KEY_PINIA_BAJA;
                guardarAnteriorX(playerX,retorno);
                return retorno;


            }else if(SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&&SDL_JoystickGetButton(playerX, poder)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.accion=TinputAccion::KEY_PODER;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)){
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                cout<<"88888888888888"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }
        };
        case TinputMovimiento::KEY_DERECHA:{
            if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&& (SDL_JoystickGetButton(playerX, lowKick) || SDL_JoystickGetButton(playerX, highKick) || SDL_JoystickGetButton(playerX, lowPunch) || SDL_JoystickGetButton(playerX, highPunch))){
                if((SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))&& event.type==SDL_JOYBUTTONDOWN){
                    retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                    retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                    cout<<"99999999999999"<<endl;
                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }else {
                    if(event.type==SDL_JOYBUTTONDOWN){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                        cout<<"aaaaaaaaaaaaaaaaa"<<endl;
                        guardarAnteriorX(playerX,retorno);
                        return retorno;
                    }
                }
            } else if(SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                cout<<"bbbbbbbbbbbbbbbbbbbbbb"<<endl;
                guardarAnteriorX(playerX,retorno);break;
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, lowKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;
                cout<<"cccccccccccccccccccc"<<endl;
                retorno.accion=TinputAccion::KEY_PATADA_BAJA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, highKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;
                retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                cout<<"dddddddddddddddddddddd"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, highPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;
                retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                cout<<"eeeeeeeeeeeeeeeeeeeee"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, lowPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;
                cout<<"ffffffffffffffffffffffffff"<<endl;
                retorno.accion=TinputAccion::KEY_PINIA_BAJA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if(SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&&SDL_JoystickGetButton(playerX, poder)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.accion=TinputAccion::KEY_PODER;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)){
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;
                cout<<"gggggggggggggggggggggggg"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }
        };
        case TinputMovimiento::KEY_ARRIBA: {
            if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&& (SDL_JoystickGetButton(playerX, lowKick) || SDL_JoystickGetButton(playerX, highKick) || SDL_JoystickGetButton(playerX, lowPunch) || SDL_JoystickGetButton(playerX, highPunch))){
                if((SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))&& event.type==SDL_JOYBUTTONDOWN){
                    retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                    retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                    cout<<"hhhhhhhhhhhhh"<<endl;
                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }else {
                    if(event.type==SDL_JOYBUTTONDOWN){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                        cout<<"iiiiiiiiiiiiiiiiiiiii"<<endl;
                        guardarAnteriorX(playerX,retorno);
                        return retorno;
                    }
                }
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&& (SDL_JoystickGetButton(playerX, lowKick) || SDL_JoystickGetButton(playerX, highKick) || SDL_JoystickGetButton(playerX, lowPunch) || SDL_JoystickGetButton(playerX, highPunch))){
                if((SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))&& event.type==SDL_JOYBUTTONDOWN){
                    retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                    retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                    cout<<"kkkkkkkkkkkkkkkkkkk"<<endl;
                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }else {
                    if(event.type==SDL_JOYBUTTONDOWN){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                        retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                        cout<<"mmmmmmmmmmmm"<<endl;
                        guardarAnteriorX(playerX,retorno);
                        return retorno;
                    }
                }
            } else if(SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                cout<<"jjjjjjjjjjjjjjjjj"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            } else if(SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                cout<<"ooooooooooooooooo"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if(SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, lowKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA;
                cout<<"ppppppppppppppppppppppp"<<endl;
                retorno.accion=TinputAccion::KEY_PATADA_BAJA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, highKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA;
                cout<<"rrrrrrrrrrrrrrrrrrrrrrr"<<endl;
                retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, highPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA;
                cout<<"ssssssssssssssssssssssss"<<endl;
                retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)&&SDL_JoystickGetButton(playerX, lowPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA;
                retorno.accion=TinputAccion::KEY_PINIA_BAJA;
                cout<<"uuuuuuuuuuuuuuuuuuu"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA;
                guardarAnteriorX(playerX,retorno);
                cout<<"wwwwwwwwwwwww"<<endl;
                return retorno;break;
            }
        };
        case TinputMovimiento::KEY_ABAJO: {
            if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, lowKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;
                cout<<"xxxxxxxxxxxxxxxxxx"<<endl;
                retorno.accion=TinputAccion::KEY_PATADA_BAJA;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, highKick)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;
                retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                cout<<"yyyyyyyyyyyyyyyyyyyy"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, highPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;
                retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                cout<<"zzzzzzzzzzzzzzzzz"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, lowPunch)&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;
                retorno.accion=TinputAccion::KEY_PINIA_BAJA;
                cout<<"111111111110000000000000"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)&&SDL_JoystickGetButton(playerX, proteccion)){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;
                retorno.accion=TinputAccion::KEY_PROTECCION;
                cout<<"111111111119999999999999"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)){
                retorno.movimiento=TinputMovimiento::KEY_ABAJO;
                cout<<"111111111112222222222222222222"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }
        };
        case TinputMovimiento::KEY_ARRIBA_DERECHA: {
            if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&& (!SDL_JoystickGetButton(playerX, lowKick) && !SDL_JoystickGetButton(playerX, highKick) && !SDL_JoystickGetButton(playerX, lowPunch) && !SDL_JoystickGetButton(playerX, highPunch) && !SDL_JoystickGetButton(playerX, proteccion)&& !SDL_JoystickGetButton(playerX, poder))) {
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                cout<<"111111111113333333333333333"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_DERECHA)&& (SDL_JoystickGetButton(playerX, lowKick) || SDL_JoystickGetButton(playerX, highKick) || SDL_JoystickGetButton(playerX, lowPunch) || SDL_JoystickGetButton(playerX, highPunch))){
                if((SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))&& event.type==SDL_JOYBUTTONDOWN){
                    retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                    retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                    cout<<"hhhhhhhhhhhhh"<<endl;
                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }else {
                    if(event.type==SDL_JOYBUTTONDOWN){
                        retorno.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                        cout<<"iiiiiiiiiiiiiiiiiiiii"<<endl;
                        guardarAnteriorX(playerX,retorno);
                        return retorno;
                    }
                }
            } else if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)) {
                retorno.movimiento=TinputMovimiento::KEY_DERECHA;
                cout<<"11111111111444444444444444444"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;break;
            }

        };
        case TinputMovimiento::KEY_ARRIBA_IZQUIERDA: {
            if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX,FLECHA_IZQUIERDA )&& (!SDL_JoystickGetButton(playerX, lowKick) && !SDL_JoystickGetButton(playerX, highKick) && !SDL_JoystickGetButton(playerX, lowPunch) && !SDL_JoystickGetButton(playerX, highPunch) && !SDL_JoystickGetButton(playerX, proteccion)&& !SDL_JoystickGetButton(playerX, poder))) {
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                cout<<"1111111111155555555555555555"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }
            else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)&& (SDL_JoystickGetButton(playerX, lowKick) || SDL_JoystickGetButton(playerX, highKick) || SDL_JoystickGetButton(playerX, lowPunch) || SDL_JoystickGetButton(playerX, highPunch)))
            if((SDL_JoystickGetButton(playerX, lowKick)||SDL_JoystickGetButton(playerX, highKick))&& event.type==SDL_JOYBUTTONDOWN){
                retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                retorno.accion=TinputAccion::KEY_PATADA_ALTA;
                cout<<"kkkkkkkkkkkkkkkkkkk"<<endl;
                guardarAnteriorX(playerX,retorno);
                return retorno;
            }else {
                if(event.type==SDL_JOYBUTTONDOWN){
                    retorno.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                    retorno.accion=TinputAccion::KEY_PINIA_ALTA;
                    cout<<"mmmmmmmmmmmm"<<endl;
                    guardarAnteriorX(playerX,retorno);
                    return retorno;
                }
            }else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)) {
                retorno.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                cout<<"111111111116666666666666666"<<endl;
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
        cout<<"entra"<<endl;
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
                //cout<<"mov1: "<<anterior1.num()<<" acc1: "<<anterior1.numA()<<endl;
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
                //cout<<"mov2: "<<inputAnterior1.num()<<" acc2: "<<inputAnterior1.numA()<<endl;
                setInputAnteriorX(player1,inputAnterior1,auxE);
                setInputAnteriorX(player2,inputAnterior2,auxE);
                //cout<<"mov3: "<<inputAnterior1.num()<<" acc3: "<<inputAnterior1.numA()<<endl;
                inputs.clear();
                inputs.push_back(inputAnterior1);
                inputs.push_back(inputAnterior2);
                return inputs;
            }
    }
}
void  ControladorJoystick::vibrar(){

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

}