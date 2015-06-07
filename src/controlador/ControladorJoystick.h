
#ifndef MORTALKOMBAT_CONTROLADORJOYSTICK_H
#define MORTALKOMBAT_CONTROLADORJOYSTICK_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <vector>
#include "../utils/Common.h"
#include <fstream>

class ControladorJoystick {

    enum Tflecha{
        FLECHA_ARRIBA=4,
        FLECHA_DERECHA,
        FLECHA_ABAJO,
        FLECHA_IZQUIERDA
    };
private:
    Tinput esAnterior(SDL_Joystick*,SDL_Event);
    void guardarAnteriorX(SDL_Joystick* ,Tinput );
    void setInputAnteriorX(SDL_Joystick*,Tinput& ,SDL_Event );
    Tinput inputAnteriorX(SDL_Joystick* );
    void vibrar();
    SDL_Joystick* player1 = NULL;
    SDL_Joystick* player2 = NULL;
    SDL_Haptic *haptic=NULL;
    SDL_HapticEffect effect;
    int effect_id=0;

    int lowKick;
    int highKick;
    int lowPunch;
    int highPunch;
    int poder;
    int proteccion;
public:
    Tinput inputAnterior1;
    Tinput inputAnterior2;
    ControladorJoystick(Tbotones);
    void cerrarJoysticks();
    vector<Tinput> getInputs(SDL_Event);

};


#endif //MORTALKOMBAT_CONTROLADORJOYSTICK_H