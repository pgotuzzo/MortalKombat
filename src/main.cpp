#include <iostream>
#include <SDL2/SDL.h>
#include "vista/Pantalla.h"
#include "parser/config.h"
#include "modelo/Mundo.h"
#include "controlador/Controlador.h"

int main(int argc, char** argv) {

    cout << "------------------------------------------------------------" << endl;
    cout << "------------------INICIO DEL JUEGO--------------------------" << endl;
    cout << "------------------------------------------------------------" << endl;


    cout << "------------------------------------------------------------" << endl;
    cout << "-------------- Cargando la configuracion -------------------" << endl;
    cout << "------------------------------------------------------------" << endl;

    config configuracion = config(argv[1]);

    cout << "------------------------------------------------------------" << endl;
    cout << "Inicia la creacion de la pantalla" << endl;

    Tventana tventana = configuracion.getVentana();
    std::vector<Tcapa> vectorTcapa = configuracion.getCapas();
    Tescenario tescenario = configuracion.getEscenario();
    Tpersonaje tpersonaje = configuracion.getPersonaje();


    //vector<string> dirPaths, vector<float> anchosCapas, Dimensiones dimensiones, int zInd
    Pantalla pantalla = Pantalla(vectorTcapa, tventana, tescenario, tpersonaje);

    cout << "Finaliza la creacion de la pantalla" << endl;
    cout << "------------------------------------------------------------" << endl;


    cout << "------------------------------------------------------------" << endl;
    cout << "Inicia la creacion del mundo" << endl;

    Mundo mundo = Mundo(configuracion);

    cout << "Finaliza la creacion del mundo" << endl;
    cout << "------------------------------------------------------------" << endl;

    cout << "------------------------------------------------------------" << endl;
    cout << "Inicia la creacion del controlador" << endl;

    Controlador controlador= Controlador();

    cout << "Finaliza la creacion del controlador" << endl;
    cout << "------------------------------------------------------------" << endl;

    cout << "------------------------------------------------------------" << endl;
    cout << "-------------- Game Loop Finito ----------------------------" << endl;
    cout << "------------------------------------------------------------" << endl;

    //1 SALTAR
    //2 AGACHAR
    //3 Caminar a la derecha
    //4 Caminar a la izquierda
    //5 Salto oblicuo a la derecha
    //6 Salto oblicuo a la izquierda

    bool end = false;
    while(!end){
        std::vector<Tinput> inputs = controlador.getInputs();
        if (!inputs.empty()) {
            if (inputs[0] == KEY_EXIT)
                end = true;
            else {
                for (Tinput input : inputs) {
                    int k;
                    switch (input) {
                        case KEY_ARRIBA: {k = 1; break;};
                        case KEY_ABAJO: {k = 2; break;};
                        case KEY_DERECHA: {k = 3; break;};
                        case KEY_IZQUIERDA: {k = 4; break;};
                        case KEY_ARRIBA_DERECHA: {k = 5; break;};
                        case KEY_ARRIBA_IZQUIERDA: {k = 6; break;};
                        default:
                            k = 0;
                    }
                    Tcambio c;
                    c = mundo.actualizarMundo(c, k);
                    pantalla.update(c);
                    pantalla.dibujar();
                }
            }
        }
        else{
            Tcambio c = mundo.actualizarMundo(c, 0);
            pantalla.update(c);
            pantalla.dibujar();
        }
        SDL_Delay(40);
    }

    cout << "------------------------------------------------------------" << endl;
    cout << "---------------------FIN DEL JUEGO--------------------------" << endl;
    cout << "------------------------------------------------------------" << endl;

    return 0;
}