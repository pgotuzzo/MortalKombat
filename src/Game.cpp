#include "Game.h"
#include "vista/pantallas/menu/PantallaMenuModoJuego.h"
#include "vista/pantallas/PantallaFight.h"
#include "vista/pantallas/PantallaPractice.h"
#include "vista/pantallas/PantallaArcade.h"
#include "vista/pantallas/menu/PantallaMenuPlayers.h"

Game::Game(config* configuration, const int gameLoopPeriod) {
    mConfiguration = configuration;

    mLoopPeriod = gameLoopPeriod;
    mState = EgameState::MENU_MODE;
    mModeSelection = EmodeSelection::MULTIPLAYER;

    mPantalla = nullptr;
    mMundo = nullptr;
    mMenuGameMode = nullptr;
    mMenuPlayers = nullptr;

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
        case EgameState::MENU_PLAYERS:{
            loguer->loguear("[--- MENU DE JUGADORES ---]", Log::LOG_DEB);
            loguer->loguear("Creando la pantalla...", Log::LOG_DEB);

            Tdimension dimPx = mConfiguration->getVentana().dimPx;
            Tdimension dim = {
                    mConfiguration->getVentana().ancho,
                    mConfiguration->getEscenario().d.h,
            };

            mPantalla = new PantallaMenuPlayers(dimPx, dim);

            loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
            loguer->loguear("Creando el modelo...", Log::LOG_DEB);

            mMenuPlayers = new MenuPlayers();

            loguer->loguear("Finaliza la creacion del modelo", Log::LOG_DEB);
            break;
        };
        case EgameState::MODE_MULTIPLAYER:
        case EgameState::MODE_ARCADE:{
            loguer->loguear("[--- MODO MULTIPLAYER/ARCADE ---]", Log::LOG_DEB);
            loguer->loguear("Creando la pantalla...", Log::LOG_DEB);

            vector<Tcapa> capas = mConfiguration->getCapas();
            vector<Tpersonaje> personajes = mConfiguration->getPersonajes();
            Tventana ventana = mConfiguration->getVentana();
            Tescenario escenario = mConfiguration->getEscenario();

            mPantalla = new PantallaArcade(capas, ventana, escenario, personajes);// Capas
            string nombres[2] = {personajes[0].nombre, personajes[1].nombre};
            mPantalla->initialize(capas, nombres);

            loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
            loguer->loguear("Creando el modelo...", Log::LOG_DEB);

            mMundo = new Mundo(*mConfiguration);

            loguer->loguear("Finaliza la creacion del modelo", Log::LOG_DEB);
            break;
        };
        case EgameState::MODE_PRACTICE:{
            loguer->loguear("[--- MODO PRACTICE ---]", Log::LOG_DEB);
            loguer->loguear("Creando la pantalla...", Log::LOG_DEB);

            vector<Tcapa> capas = mConfiguration->getCapas();
            vector<Tpersonaje> personajes = mConfiguration->getPersonajes();
            Tventana ventana = mConfiguration->getVentana();
            Tescenario escenario = mConfiguration->getEscenario();

            mPantalla = new PantallaPractice(capas, ventana, escenario, personajes);
            // Capas
            string nombres[2] = {personajes[0].nombre, personajes[1].nombre};
            mPantalla->initialize(capas, nombres);

            loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
            loguer->loguear("Creando el modelo...", Log::LOG_DEB);

            mMundo = new Mundo(*mConfiguration);

            loguer->loguear("Finaliza la creacion del modelo", Log::LOG_DEB);
            break;
        };
        default:;
    }
}


void Game::play(vector<Tinput> inputs, Posicion coordenadasMouse) {
    clock_t t1, t2, deltaT;
    t1 = clock();

    switch (mState){
        case EgameState::MENU_MODE:{
            if ( selectMode(inputs.front(),coordenadasMouse) == EgameResult::END ) {
                switch (mModeSelection){
                    case EmodeSelection::MULTIPLAYER: {
                        mState = EgameState::MODE_MULTIPLAYER;
                        initialize();
                        break;
                    };
                    case EmodeSelection::ARCADE: {
                        mState = EgameState::MODE_ARCADE;
                        initialize();
                        break;
                    };
                    case EmodeSelection::PRACTICE: {
                        mState = EgameState::MODE_PRACTICE;
                        initialize();
                        break;
                    };
                }
            }
            break;
        };
        case EgameState::MENU_PLAYERS:{
            if (selectPlayers(inputs) == EgameResult::END ) {}
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
                return mMundo->quienGano();
            return "Empate";
        };
        default:
            return "";
    }
}

EgameResult Game::selectMode(Tinput input,Posicion coordenadasMouse) {
    vector<float> escalas = mPantalla->getEscalas();

    coordenadasMouse.x = coordenadasMouse.x / escalas[0];
    coordenadasMouse.y = coordenadasMouse.y / escalas[1];

    EmodeSelection selection = mMenuGameMode->update(coordenadasMouse,mPantalla->getCuadradoModos());
    selection = mMenuGameMode->update(input);
    mPantalla->update(selection);
    mPantalla->print();

    if ( mMenuGameMode->selectionComplete() ) {
        mModeSelection = selection;
        return EgameResult::END;
    }
    return EgameResult::CONTINUE;
}

EgameResult Game::selectPlayers(vector<Tinput> inputs) {
    vector<EtipoPersonaje> players = mMenuPlayers->update(inputs);
    mPantalla->update(players);
    mPantalla->print();

    if ( mMenuPlayers->selectionComplete() ) {
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

