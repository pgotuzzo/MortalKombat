#include <iostream>
#include <SDL2/SDL.h>
#include "vista/Pantalla.h"
#include "parser/config.h"
#include "modelo/Mundo.h"
#include "controlador/Controlador.h"
#include <time.h>

const float delay = 45;

int main(int argc, char **argv) {


    //loguer->borrar();

    string jsonPath = (argv[1] == nullptr) ? string("") : argv[1];

    loguer->loguear("------------------INICIO DEL JUEGO--------------------------", Log::LOG_DEB);

    bool endGame = false;
    clock_t t1, t2;
    float timeloop = 00.0;

    while (!endGame) {

        bool restart = false;


        loguer->loguear("-------------- Cargando la configuracion -------------------", Log::LOG_DEB);

        config configuracion = config(jsonPath);

        loguer->loguear("Inicia la creacion de la pantalla...", Log::LOG_DEB);

        Tventana tventana = configuracion.getVentana();
        std::vector<Tcapa> vectorTcapa = configuracion.getCapas();
        Tescenario tescenario = configuracion.getEscenario();
        Tpersonaje tpersonaje = configuracion.getPersonaje();
        tventana.distTope = MIN_DISTANCE_FROM_BOUND;
        Tpersonajes tpersonajes;
        tpersonajes.ancho=tpersonaje.ancho;
        tpersonajes.alto=tpersonaje.alto;
        tpersonajes.zIndex=tpersonaje.zIndex;
        tpersonajes.orientacion[0]=tpersonaje.orientacion;
        tpersonajes.sprites[0]=tpersonaje.sprites;
        tpersonajes.orientacion[1]=tpersonaje.orientacion;
        tpersonajes.sprites[1]=tpersonaje.sprites;

        Pantalla* pantalla = new Pantalla(vectorTcapa, tventana, tescenario, tpersonajes);

        loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
        loguer->loguear("Inicia la creacion del mundo...", Log::LOG_DEB);

        Mundo* mundo = new Mundo(configuracion);

        loguer->loguear("Finaliza la creacion del mundo", Log::LOG_DEB);
        loguer->loguear("Inicia la creacion del controlador", Log::LOG_DEB);

        Controlador controlador = Controlador();

        loguer->loguear("Finaliza la creacion del controlador", Log::LOG_DEB);
        loguer->loguear("-------------- GameLoop ----------------------------", Log::LOG_DEB);


        while ( !restart && !endGame ) {
            t1 = clock();

            // INPUT
            Tinput input = controlador.getInputs();

            switch (input){
                //PARA RESTABLECER EL JUEGO
                case KEY_RESTART:{
                    restart = true;
                    delete(pantalla);
                    delete(mundo);
                    break;
                };
                    //SI SE DESEA SALIR DEL JUEGO
                case KEY_EXIT:{
                    endGame = true;
                    delete(pantalla);
                    delete(mundo);
                    break;
                }
                    //DEMAS ACCIONES
                default:{
                    Tcambios c;
                    c = mundo->actualizarMundo(input);
                    pantalla->update(c);
                    pantalla->dibujar();
                    t2 = clock();
                    timeloop = (((float)t2 - (float)t1) / 1000000.0F ) * 1000;
                    SDL_Delay(delay - timeloop);
                }
            };
        }
    }
    loguer->loguear("---------------------FIN DEL JUEGO--------------------------", Log::LOG_DEB);

    return 0;
}
