
#include "ControladorJoystick.h"


ControladorJoystick::ControladorJoystick() {
    inputAnterior1 = KEY_NADA;
    inputAnterior2 = KEY_NADA;

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
Tinput ControladorJoystick::esAnterior(SDL_Joystick* playerX) {
    Tinput aux=inputAnteriorX(playerX);
    switch (aux) {
        case KEY_IZQUIERDA: {
            if (SDL_JoystickGetButton(playerX, 4) && SDL_JoystickGetButton(playerX, 7)){
                guardarAnteriorX(playerX,KEY_ARRIBA_IZQUIERDA);
                return KEY_ARRIBA_IZQUIERDA;
            }
            else if (SDL_JoystickGetButton(playerX, 7)){
                guardarAnteriorX(playerX,KEY_IZQUIERDA);
                return KEY_IZQUIERDA; break;
            }
        };
        case KEY_DERECHA: {
            if (SDL_JoystickGetButton(playerX, 4) && SDL_JoystickGetButton(playerX, 5)){
                guardarAnteriorX(playerX,KEY_ARRIBA_DERECHA);
                return KEY_ARRIBA_DERECHA;
            }
            else if (SDL_JoystickGetButton(playerX, 5)){
                guardarAnteriorX(playerX,KEY_DERECHA);
                return KEY_DERECHA; break;
            }
        };
        case KEY_ARRIBA: {
            if (SDL_JoystickGetButton(playerX, 4) && SDL_JoystickGetButton(playerX, 5)){
                guardarAnteriorX(playerX,KEY_ARRIBA_DERECHA);
                return KEY_ARRIBA_DERECHA;
            }
            else if (SDL_JoystickGetButton(playerX, 4) && SDL_JoystickGetButton(playerX, 7)){
                guardarAnteriorX(playerX,KEY_ARRIBA_IZQUIERDA);
                return KEY_ARRIBA_IZQUIERDA;
            }
            else if (SDL_JoystickGetButton(playerX, 4)){
                guardarAnteriorX(playerX,KEY_ARRIBA);
                return KEY_ARRIBA; break;
            }
        };
        case KEY_ABAJO: {
            if (SDL_JoystickGetButton(playerX, 6)){
                guardarAnteriorX(playerX,KEY_ABAJO);
                return KEY_ABAJO; break;
            }
        };
        case KEY_ARRIBA_DERECHA: {
            if (SDL_JoystickGetButton(playerX, 4) && SDL_JoystickGetButton(playerX, 5)) {
                guardarAnteriorX(playerX,KEY_ARRIBA_DERECHA);
                return KEY_ARRIBA_DERECHA;
            }
            else if (SDL_JoystickGetButton(playerX, 5)) {
                guardarAnteriorX(playerX,KEY_DERECHA);
                return KEY_DERECHA; break;
            }
        };
        case KEY_ARRIBA_IZQUIERDA: {
            if (SDL_JoystickGetButton(playerX, 4) && SDL_JoystickGetButton(playerX, 7)) {
                guardarAnteriorX(playerX,KEY_ARRIBA_IZQUIERDA);
                return KEY_ARRIBA_IZQUIERDA;
            }
            else if (SDL_JoystickGetButton(playerX, 7)) {
                guardarAnteriorX(playerX,KEY_IZQUIERDA);
                return KEY_IZQUIERDA; break;
            }
        };
    }
    return KEY_NADA;
}

void ControladorJoystick::guardarAnteriorX(SDL_Joystick* playerX,Tinput anterior){
    if(playerX==player1)
        this->inputAnterior1=anterior;
    else
    if(playerX==player2)
        inputAnterior2=anterior;
}

void ControladorJoystick::setInputAnteriorX(SDL_Joystick* playerX,Tinput& auxInputX){

    if (SDL_JoystickGetButton(playerX, FLECHA_DERECHA)) auxInputX = KEY_DERECHA;
    else if (SDL_JoystickGetButton(playerX, FLECHA_IZQUIERDA)) auxInputX = KEY_IZQUIERDA;
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA)) auxInputX = KEY_ARRIBA;
    else if (SDL_JoystickGetButton(playerX, FLECHA_ABAJO)) auxInputX = KEY_ABAJO;
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(player2, FLECHA_DERECHA)) auxInputX = KEY_ARRIBA_DERECHA;
    else if (SDL_JoystickGetButton(playerX, FLECHA_ARRIBA) && SDL_JoystickGetButton(player2, FLECHA_IZQUIERDA)) auxInputX = KEY_ARRIBA_IZQUIERDA;
    else auxInputX = KEY_NADA;

}

vector<Tinput> ControladorJoystick::getInputs() {

    vector<Tinput> inputs = {Tinput(), Tinput()};


    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {}
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            inputs[0] = KEY_EXIT;
            return inputs;

            // Solo captura el evento cuando suelta R
        case SDL_JOYBUTTONUP:{ if (event.jbutton.button == 0) {
                inputs[0] = KEY_RESTART;
                return inputs;
            }
        };
        default:
            Tinput anterior1 = esAnterior(player1);
            Tinput anterior2 = esAnterior(player2);
            if (anterior1 != KEY_NADA && anterior2 != KEY_NADA) {
                inputs[0] = anterior1;
                inputs[1] = anterior2;
                return inputs;
            } else if (anterior1 != KEY_NADA) {
                inputs[0] = anterior1;
                setInputAnteriorX(player2,inputAnterior2);
                inputs[1] = inputAnterior2;
                return inputs;

            } else if (anterior2 != KEY_NADA) {
                inputs[1] = anterior2;
                setInputAnteriorX(player1,inputAnterior1);
                inputs[0] = inputAnterior1;
                return inputs;
            } else {
                setInputAnteriorX(player1,inputAnterior1);
                setInputAnteriorX(player2,inputAnterior2);
                inputs[0] = inputAnterior1;
                inputs[1] = inputAnterior2;
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
