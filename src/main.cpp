#include <iostream>
#include <SDL2/SDL.h>
#include "vista/Pantalla.h"
#include "parser/config.h"
#include "modelo/Mundo.h"
#include "controlador/Controlador.h"
#include <time.h>

const float delay = 45.0;

int main(int argc, char **argv) {

    string jsonPath = (argv[1] == nullptr) ? string("") : argv[1];

    loguer->loguear("------------------INICIO DEL JUEGO--------------------------", Log::LOG_DEB);

    bool endGame = false;
    clock_t t1, t2;
    float timeloop = 00.0;

    while (!endGame) {

        loguer->loguear("-------------- Cargando la configuracion -------------------", Log::LOG_DEB);

        config configuracion = config(jsonPath);

        loguer->loguear("Inicia la creacion de la pantalla...", Log::LOG_DEB);

        Tventana tventana = configuracion.getVentana();
        std::vector<Tcapa> vectorTcapa = configuracion.getCapas();
        Tescenario tescenario = configuracion.getEscenario();
        Tpersonaje tpersonaje = configuracion.getPersonaje();
        tventana.distTope = MIN_DISTANCE_FROM_BOUND;
        Pantalla pantalla = Pantalla(vectorTcapa, tventana, tescenario, tpersonaje);

        loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
        loguer->loguear("Inicia la creacion del mundo...", Log::LOG_DEB);

        Mundo mundo = Mundo(configuracion);

        loguer->loguear("Finaliza la creacion del mundo", Log::LOG_DEB);
        loguer->loguear("Inicia la creacion del controlador", Log::LOG_DEB);

        Controlador controlador = Controlador();

        loguer->loguear("Finaliza la creacion del controlador", Log::LOG_DEB);

        bool restart = false;

        loguer->loguear("-------------- GameLoop ----------------------------", Log::LOG_DEB);

        while ( !restart && !endGame ) {
            //Declaracion de variables necesarias para el gameloop

            //0 PARADO
            //1 SALTAR
            //2 AGACHAR
            //3 Caminar a la derecha
            //4 Caminar a la izquierda
            //5 Salto oblicuo a la derecha
            //6 Salto oblicuo a la izquierda
            //7 Restart
            //8 Exit

            Tcambio c;
            Tinput input;

            t1 = clock();

            // INPUT
            input = controlador.getInputs();

            //SI SE DESEA SALIR DEL JUEGO
            if (input == KEY_EXIT)
                endGame = true;

            //PARA RESTABLECER EL JUEGO
            if (input == KEY_RESTART) {
                restart = true;
            }

                //DEMAS ACCIONES
            else {
                c = mundo.actualizarMundo(c, input);
                pantalla.update(c);
                pantalla.dibujar();
            }
            t2 = clock();
            timeloop = (((float)t2 - (float)t1) / 1000000.0F ) * 1000;
            SDL_Delay(delay - timeloop);
        }
    }

   loguer->loguear("---------------------FIN DEL JUEGO--------------------------", Log::LOG_DEB);

    return 0;
}