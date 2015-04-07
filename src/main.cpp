#include <iostream>
#include <SDL2/SDL.h>
#include "vista/Pantalla.h"
#include "parser/config.h"
#include "modelo/Mundo.h"

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
    cout << "-------------- Game Loop Finito ----------------------------" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Camina a la derecha" << endl;
    for( int i = 0; i < 100; i++ ){
        Tcambio c;
        c = mundo.actualizarMundo(c,3);
        //c.estado = CAMINANDO;
        //c.direccion = IZQUIERDA;
        //c.sentido = ATRAS;
        pantalla.update(c);
        pantalla.dibujar();
        SDL_Delay(50);
    }
    cout << "Camina a la izquierda" << endl;
    for( int i = 0; i < 100; i++ ){
        Tcambio c;
        c = mundo.actualizarMundo(c,4);
        //c.estado = CAMINANDO;
        //c.direccion = IZQUIERDA;
        //c.sentido = ADELANTE;
        pantalla.update(c);
        pantalla.dibujar();
        SDL_Delay(50);
    }

    cout << "------------------------------------------------------------" << endl;
    cout << "---------------------FIN DEL JUEGO--------------------------" << endl;
    cout << "------------------------------------------------------------" << endl;

    return 0;
}