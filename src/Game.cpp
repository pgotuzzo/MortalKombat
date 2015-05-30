#include "Game.h"
#include "vista/pantallas/PantallaMultiplayer.h"

Game::Game(config configuracion, const int gameLoopPeriod) {

    loguer->loguear("Inicia la creacion de la pantalla...", Log::LOG_DEB);

    Tventana tventana = configuracion.getVentana();
    vector<Tcapa> vectorTcapa = configuracion.getCapas();
    Tescenario tescenario = configuracion.getEscenario();
    vector<Tpersonaje> tpersonajes = configuracion.getPersonajes();

    mPantalla = new PantallaMultiplayer(vectorTcapa, tventana, tescenario, tpersonajes);

    loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
    loguer->loguear("Inicia la creacion del mundo...", Log::LOG_DEB);

    mMundo = new Mundo(configuracion);

    loguer->loguear("Finaliza la creacion del mundo", Log::LOG_DEB);

    mLoopPeriod = gameLoopPeriod;

}

/**
 * return   "true" si el juego finalizó.
 *          "false" si el juego continua.
 */
bool Game::play(vector<Tinput> inputs) {
    clock_t t1, t2, deltaT;
    t1 = clock();
//    switch (mState){
//        default: ;
//    }

    bool returnValue = fight(inputs);

    t2 = clock();
    deltaT = (clock_t) ( ( (t2 - t1) / 1000.0F ) );
    SDL_Delay( (Uint32) (mLoopPeriod - deltaT) );
    return returnValue;
}



string Game::getWinner() {
    return "EMPATE";
}

bool Game::fight(vector<Tinput> inputs) {
    switch (inputs[0].game){
        case TinputGame::KEY_ESC:
            return false;
        default:{
            vector<Tcambio> c;
            c = mMundo->actualizarMundo(inputs);
            mPantalla->update(c);
            mPantalla->print();
            return !(mMundo->huboGanador());
        }
    };
}

void Game::restart() {
    // TODO - Liberar memoria!!!!
}

Game::~Game() {
    delete(mPantalla);
    delete(mMundo);
}
