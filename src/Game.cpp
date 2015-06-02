#include "Game.h"
#include "vista/pantallas/PantallaMenuModoJuego.h"
#include "vista/pantallas/PantallaFight.h"

Game::Game(config* configuration, const int gameLoopPeriod) {
    mConfiguration = configuration;

    mLoopPeriod = gameLoopPeriod;
    mState = EgameState::MENU_MODE;
    mModeSelection = EmodeSelection::MULTIPLAYER;

    mPantalla = nullptr;
    mMundo = nullptr;
    mMenuGameMode = nullptr;

    initialize();
};

void Game::clean(){
    if (mPantalla != nullptr)
        delete(mPantalla);
    if (mMundo != nullptr)
        delete(mMundo);
    if (mMenuGameMode != nullptr)
        delete(mMenuGameMode);
}

void Game::initialize() {
    clean();
    switch (mState){
        case EgameState::MENU_MODE: {
            loguer->loguear("[--- MENU PRINCIPAL ---]", Log::LOG_DEB);
            loguer->loguear("Creando la pantalla...", Log::LOG_DEB);

            Tdimension dimPx = mConfiguration->getVentana().dimPx;
            Tdimension dim = {
                    mConfiguration->getVentana().ancho,
                    mConfiguration->getEscenario().d.h,
            };

            mPantalla = new PantallaMenuModoJuego(dimPx, dim);

            loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
            loguer->loguear("Creando el modelo...", Log::LOG_DEB);

            mMenuGameMode = new MenuGameMode();

            loguer->loguear("Finaliza la creacion del modelo", Log::LOG_DEB);
            break;
        };
        case EgameState::MODE_MULTIPLAYER:
        case EgameState::MODE_ARCADE:
        case EgameState::MODE_PRACTICE:{
            loguer->loguear("[--- MODO MULTIPLAYER ---]", Log::LOG_DEB);
            loguer->loguear("Creando la pantalla...", Log::LOG_DEB);

            vector<Tcapa> capas = mConfiguration->getCapas();
            vector<Tpersonaje> personajes = mConfiguration->getPersonajes();
            Tventana ventana = mConfiguration->getVentana();
            Tescenario escenario = mConfiguration->getEscenario();

            mPantalla = new PantallaFight(capas, ventana, escenario, personajes);

            loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
            loguer->loguear("Creando el modelo...", Log::LOG_DEB);

            mMundo = new Mundo(*mConfiguration);

            loguer->loguear("Finaliza la creacion del modelo", Log::LOG_DEB);
            break;
        };
        default:;
    }
}


void Game::play(vector<Tinput> inputs) {
    clock_t t1, t2, deltaT;
    t1 = clock();

    switch (mState){
        case EgameState::MENU_MODE:{
            if ( selectMode(inputs.front()) == EgameResult::END ) {
                /**
                 * TODO - Corregir
                 * mState = EgameState::MENU_PLAYERS;
                 */
                mState = EgameState::MODE_MULTIPLAYER;
                initialize();
            }
            break;
        };
        case EgameState::MODE_ARCADE:
        case EgameState::MODE_MULTIPLAYER:
        case EgameState::MODE_PRACTICE:{
            if ( fight(inputs) == EgameResult::END){
                mState = EgameState::MENU_MODE;
                initialize();
            }
            break;
        };
        default: ;
    }

    t2 = clock();
    deltaT = (clock_t) ( ( (t2 - t1) / 1000.0F ) );
    if (deltaT < mLoopPeriod)
        SDL_Delay((Uint32) (mLoopPeriod - deltaT));
}

string Game::getWinner() {
    switch (mState){
        case EgameState::MODE_ARCADE:
        case EgameState::MODE_MULTIPLAYER:{
            if (mMundo->huboGanador())
                // TODO - ANDRES & MIKI: Como verifico quien gano???
                return "Alguno gano";
            return "Empate";
        };
        default:
            return "";
    }
}

EgameResult Game::selectMode(Tinput input) {
    EmodeSelection selection = mMenuGameMode->update(input);
    mPantalla->update(selection);
    mPantalla->print();

    if ( mMenuGameMode->selectionComplete() ) {
        mModeSelection = selection;
        return EgameResult::END;
    }
    return EgameResult::CONTINUE;
}

EgameResult Game::fight(vector<Tinput> inputs) {
    switch (inputs[0].game){
        case TinputGame::KEY_ESC:
            return EgameResult::END;
        default:{
            vector<Tcambio> c = mMundo->actualizarMundo(inputs);
            mPantalla->update(c,inputs[0]);
            mPantalla->print();
            return ( mMundo->huboGanador() ) ? EgameResult::END : EgameResult::CONTINUE;
        }
    };
}

Game::~Game() {
    delete(mPantalla);
    delete(mMundo);
    delete(mConfiguration);
}

