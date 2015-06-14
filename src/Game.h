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

    config* mConfiguration;
    Pantalla* mPantalla;
    Mundo* mMundo;
    MenuGameMode* mMenuGameMode;
    MenuPlayerSelection* mMenuPlayers;

    bool dentroDelCuadroDePjs(Posicion coordenadasMouse,vector<Trect> cuadroPlayers);


    // metodos privados
    void clean();
    void initialize();

    EgameResult selectMode(Tinput input,Posicion coordenadasMouse);
    EgameResult selectPlayers(vector<Tinput> inputs,Posicion coordenadasMouse,bool seleccionOponenteAleatorio);

    EgameResult fight(vector<Tinput> inputs);

    Musica* sonidoPJ1;
    Musica* sonidoPJ2;

    Musica* musicaDelJuego;

public:

    EgameState mState;

    EmodeSelection modoDeJuegoElegido;

    EtipoPersonaje personajesElegidos[2];

    string nombrePjs[2];
    string rutaSprites[2];

    void setInformacionPersonajesElegidos(int jugador);

    Game(config* configuration, const int gameloop);

    void play(vector<Tinput> inputs,Posicion coordenandasMouse);
    string getWinner();

    virtual ~Game();
};


#endif //MORTALKOMBAT_GAME_H