#ifndef MORTALKOMBAT_JUEGO_H
#define MORTALKOMBAT_JUEGO_H


#include "parser/config.h"
#include "modelo/Mundo.h"
#include "vista/pantallas/Pantalla.h"

class Game {
private:

    enum GameState{
        // seleccion del modo practica/arcade/multiplayer
        MENU_MODE,

        // seleccion de los personajes
        MENU_PLAYERS,

        // finalizar o volver al menu principal
        MENU_END,

        /** animacion para enfrentar al siguiente oponente
         * NEXT_OPONENT_ANIMATION,
         */

        // modos de juego
        MODE_PRACTICE,
        MODE_MULTIPLAYER,
        MODE_ARCADE,
    };

    int mLoopPeriod;
    GameState mState;

    Pantalla* mPantalla;
    Mundo* mMundo;

    // metodos privados
    void restart();
    bool fight(vector<Tinput> inputs);


public:
    Game(config configuracion, const int gameloop);

    bool play(vector<Tinput> inputs);
    string getWinner();

    virtual ~Game();
};


#endif //MORTALKOMBAT_JUEGO_H
