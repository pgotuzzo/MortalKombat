#include <iostream>
#include <SDL2/SDL_image.h>
#include "parser/config.h"
#include "controlador/ControladorTeclado.h"
#include "controlador/ControladorMouse.h"
#include "Game.h"
#include "controlador/ControladorJoystick.h"


const int frameRate = 45;

int main(int argc, char **argv) {

    loguer->borrar();

    string jsonPath = (argv[1] == nullptr) ? string("") : argv[1];

    loguer->loguear("------------------INICIANDO MORTAL KOMBAT--------------------------", Log::LOG_DEB);

    bool endGame = false;
    while (!endGame) {

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            loguer->loguear("Fallo la inicializacion general de SDL.", Log::LOG_ERR);
            loguer->loguear(SDL_GetError(), Log::LOG_ERR);
            throw new exception();
        }

        loguer->loguear("-------------- Cargando la configuracion -------------------", Log::LOG_DEB);
        loguer->loguear("Inicia la creacion del controlador", Log::LOG_DEB);

        config* configuracion = new config(jsonPath);

        //TODO: Modificar los dos controladores para que devuelvan los nuevos inputs del struct Tinput
        ControladorTeclado controlador = ControladorTeclado();
        ControladorMouse controladorMouse = ControladorMouse();


        loguer->loguear("Finaliza la creacion del controlador", Log::LOG_DEB);
        loguer->loguear("-------------- Iniciando el Juego -------------------", Log::LOG_DEB);


        Game game = Game(configuracion, frameRate);

        ControladorJoystick controladorJ = ControladorJoystick(configuracion->getBotones());
        bool restart = false;
        do {
            vector<Tinput> inputs;
            //if(game.mState == EgameState::MENU_MODE || game.mState == EgameState::MENU_PLAYERS){
                SDL_Event event;
                while(SDL_PollEvent(&event) != 0){}
                SDL_PollEvent(&event);

                vector<Tinput> inputsT = controlador.getInputs(event);
                vector<Tinput> inputsJ = controladorJ.getInputs(event);
                inputs = inputsT;

                TinputGame inputGame = controladorMouse.moverMouse(event);
                if(inputGame == TinputGame::CLICK_IZQ_MOUSE)inputs[0].game = inputGame;
            //}
            /*else if (game.mState == EgameState::MODE_MULTIPLAYER || game.mState == EgameState::MODE_ARCADE || game.mState == EgameState::MODE_PRACTICE){
                inputs = controladorJ.getInputs();
            }*/
            if(inputs[0].game == TinputGame::KEY_NADA) {
                inputs[0].tiempo = SDL_GetTicks();
                inputs[1].tiempo = SDL_GetTicks();
            }
            switch (inputs.at(0).game) {
                case TinputGame::KEY_EXIT:
                    endGame = true;
                    break;
                case TinputGame::KEY_RESTART:
                    restart = true;
                    break;
                default:
                    game.play(inputs,controladorMouse.posicionMouse);
            }
        } while (!restart && !endGame);

    }


    loguer->loguear("---------------------FIN DEL JUEGO--------------------------", Log::LOG_DEB);

    return 0;
}
