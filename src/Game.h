#ifndef MORTALKOMBAT_GAME_H
#define MORTALKOMBAT_GAME_H

#include "modelo/Mundo.h"
#include "parser/config.h"
#include "vista/pantallas/Pantalla.h"
#include "modelo/menu/MenuGameMode.h"
#include "utils/GameUtils.h"
#include "modelo/menu/MenuPlayers.h"

class Game {
private:
    enum class EgameState {
        // seleccion del modo practica/arcade/multiplayer
        MENU_MODE,

        // seleccion de los personajes
        MENU_PLAYERS,

        // finalizar o volver al menu principal
        //MENU_END,

        /** animacion para enfrentar al siguiente oponente
         * NEXT_OPONENT_ANIMATION,
         */

        // modos de juego
        MODE_PRACTICE,
        MODE_MULTIPLAYER,
        MODE_ARCADE,
    };

    int mLoopPeriod;
    EgameState mState;
    EmodeSelection mModeSelection;

    config* mConfiguration;
    Pantalla* mPantalla;
    Mundo* mMundo;
    MenuGameMode* mMenuGameMode;
    MenuPlayers* mMenuPlayers;

    // metodos privados
    void clean();
    void initialize();

    EgameResult selectMode(Tinput input);
    EgameResult fight(vector<Tinput> inputs);


public:
    Game(config* configuration, const int gameloop);

    void play(vector<Tinput> inputs);
    string getWinner();

    virtual ~Game();
};


#endif //MORTALKOMBAT_GAME_H
