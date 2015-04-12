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

    // TODO - meter esto en el parser o qda aca para q sea facil de tocar por lo menos
    tventana.distTope = 50;

    //vector<string> dirPaths, vector<float> anchosCapas, Dimensiones dimensiones, int zInd
    Pantalla pantalla = Pantalla(vectorTcapa, tventana, tescenario, tpersonaje);

    cout << "Finaliza la creacion de la pantalla" << endl;
    cout << "------------------------------------------------------------" << endl;


    cout << "------------------------------------------------------------" << endl;
    cout << "Inicia la creacion del mundo" << endl;

    Mundo* mundo = new Mundo(configuracion);

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

    //0 PARADO
    //1 SALTAR
    //2 AGACHAR
    //3 Caminar a la derecha
    //4 Caminar a la izquierda
    //5 Salto oblicuo a la derecha
    //6 Salto oblicuo a la izquierda
    //7 Restart
    //8 Exit


    //Declaracion de variables necesarias para el gameloop
    bool end = false;
    Tcambio c;
    int k;
    Tinput estado;

    //int framerate = 0;

    while(!end){

        // INPUT
        estado = controlador.getInputs();

        //SI SE DESEA SALIR DEL JUEGO
        if (estado == KEY_EXIT)
            end = true;

        //PARA RESTABLECER EL JUEGO
        if (estado == KEY_RESTART){
            configuracion = config(argv[1]);

            tventana = configuracion.getVentana();
            vectorTcapa = configuracion.getCapas();
            tescenario = configuracion.getEscenario();
            tpersonaje = configuracion.getPersonaje();

            delete mundo;
            // delete pantalla;
            //vector<string> dirPaths, vector<float> anchosCapas, Dimensiones dimensiones, int zInd
            pantalla = Pantalla(vectorTcapa, tventana, tescenario, tpersonaje);

            mundo = new Mundo(configuracion);

            controlador= Controlador();
        }

        //DEMAS ACCIONES
        else {
            k = static_cast<int>(estado); // k tiene la posicion del estado en el enum
//            cout << "Valor de orden: " << k << endl << endl;
            c = mundo->actualizarMundo(c, k);
            /*framerate++;
            if  (framerate == 1) {*/
                //framerate = 0;
                pantalla.update(c);
                pantalla.dibujar();
            //}
        }

        SDL_Delay(40);
    }

    delete mundo;
    cout << "------------------------------------------------------------" << endl;
    cout << "---------------------FIN DEL JUEGO--------------------------" << endl;
    cout << "------------------------------------------------------------" << endl;

    return 0;
}