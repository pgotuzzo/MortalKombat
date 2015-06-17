#ifndef MORTALKOMBAT_GAME_H
#define MORTALKOMBAT_GAME_H

#include "modelo/Mundo.h"
#include "parser/config.h"
#include "vista/pantallas/Pantalla.h"
#include "modelo/menu/MenuGameMode.h"
#include "utils/GameUtils.h"
#include "modelo/menu/MenuPlayerSelection.h"

#include "Musica.h"

class Game {
private:

    int mLoopPeriod;

    EmodeSelection mModeSelection;
    array<Tplayer, 2> mPlayers;

    // configuracion
    config* mConfiguration;

    // pantalla
    Pantalla* mPantalla;

    // modelos
    Mundo* mMundo;
    MenuGameMode* mMenuGameMode;
    MenuPlayerSelection* mMenuPlayers;

    // musica
    Musica* mMusic;

    // metodos privados
    void clean();
    void initialize();

    EgameResult selectMode(Tinput input,Posicion coordenadasMouse);
    EgameResult selectPlayers(vector<Tinput> inputs,Posicion coordenadasMouse,bool seleccionOponenteAleatorio);

    EgameResult fight(vector<Tinput> inputs);

public:
    EgameState mState;

    Game(config* configuration, const int gameloop);

    void play(vector<Tinput> inputs,Posicion coordenandasMouse);

    virtual ~Game();
};


#endif //MORTALKOMBAT_GAME_H