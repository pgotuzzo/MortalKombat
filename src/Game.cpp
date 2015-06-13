#include "Game.h"
#include "vista/pantallas/menu/PantallaMenuModoJuego.h"
#include "vista/pantallas/PantallaFight.h"
#include "vista/pantallas/PantallaPractice.h"
#include "vista/pantallas/PantallaArcade.h"
#include "vista/pantallas/menu/PantallaMenuPlayers.h"

Game::Game(config* configuration, const int gameLoopPeriod) {
    SDL_InitSubSystem(SDL_INIT_AUDIO);
    mConfiguration = configuration;

    mLoopPeriod = gameLoopPeriod;
    mState = EgameState::MENU_MODE;
    mModeSelection = EmodeSelection::MULTIPLAYER;

    modoDeJuegoElegido = EmodeSelection::MULTIPLAYER;

    mPantalla = nullptr;
    mMundo = nullptr;
    mMenuGameMode = nullptr;
    mMenuPlayers = nullptr;

    sonidoPJ1 = new Musica();
    sonidoPJ2 = new Musica();

    musicaDelJuego = new Musica();

    initialize();
};

void Game::clean(){
    if (mPantalla != NULL) {
        delete(mPantalla);
        mPantalla = NULL;
    }
    if (mMundo != NULL) {
        delete(mMundo);
        mMundo = NULL;
    }
    if (mMenuGameMode != NULL) {
        delete(mMenuGameMode);
        mMenuGameMode = NULL;
    }
    if (mMenuPlayers != NULL){
        delete(mMenuPlayers);
        mMenuPlayers = NULL;
    }
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

            musicaDelJuego->musicMenu();

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

            musicaDelJuego->pararMusica();
            musicaDelJuego->musicSeleccion();

            loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
            loguer->loguear("Creando el modelo...", Log::LOG_DEB);

            mMenuPlayers = new MenuPlayerSelection();

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

            setInformacionPersonajesElegidos(0);
            setInformacionPersonajesElegidos(1);
            personajes[0].nombre = nombrePjs[0];
            personajes[1].nombre = nombrePjs[1];
            personajes[0].sprites = rutaSprites[0];
            personajes[1].sprites = rutaSprites[1];

            mPantalla = new PantallaArcade(capas, ventana, escenario, personajes);// Capas

            mPantalla->initialize(capas, nombrePjs);

            loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
            loguer->loguear("Creando el modelo...", Log::LOG_DEB);

            mMundo = new Mundo(*mConfiguration,nombrePjs);
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

            setInformacionPersonajesElegidos(0);
            setInformacionPersonajesElegidos(1);
            personajes[0].nombre = nombrePjs[0];
            personajes[1].nombre = nombrePjs[1];
            personajes[0].sprites = rutaSprites[0];
            personajes[1].sprites = rutaSprites[1];

            mPantalla = new PantallaPractice(capas, ventana, escenario, personajes);

            // Capas
            mPantalla->initialize(capas, nombrePjs);

            loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
            loguer->loguear("Creando el modelo...", Log::LOG_DEB);

            mMundo = new Mundo(*mConfiguration,nombrePjs);

            loguer->loguear("Finaliza la creacion del modelo", Log::LOG_DEB);
            break;
        };
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
                        mState = EgameState::MENU_PLAYERS;
                        modoDeJuegoElegido = EmodeSelection::MULTIPLAYER;
                        initialize();
                        break;
                    };
                    case EmodeSelection::ARCADE: {
                        mState = EgameState::MENU_PLAYERS;
                        modoDeJuegoElegido = EmodeSelection::ARCADE;
                        initialize();
                        break;
                    };
                    case EmodeSelection::PRACTICE: {
                        mState = EgameState::MENU_PLAYERS;
                        modoDeJuegoElegido = EmodeSelection::PRACTICE;
                        initialize();
                        break;
                    };
                }
            }
            break;
        };
        case EgameState::MENU_PLAYERS:{
            if ( selectPlayers(inputs) == EgameResult::END) {
                switch (modoDeJuegoElegido){
                    case EmodeSelection::MULTIPLAYER: {
                        mState = EgameState::MODE_MULTIPLAYER;
                        modoDeJuegoElegido = EmodeSelection::MULTIPLAYER;
                        musicaDelJuego->pararMusica();
                        musicaDelJuego->musicVs();
                        initialize();

                        break;
                    };
                    case EmodeSelection::ARCADE: {
                        mState = EgameState::MODE_ARCADE;
                        modoDeJuegoElegido = EmodeSelection::ARCADE;
                        musicaDelJuego->pararMusica();
                        musicaDelJuego->musicVs();
                        initialize();
                        break;
                    };
                    case EmodeSelection::PRACTICE: {
                        mState = EgameState::MODE_PRACTICE;
                        modoDeJuegoElegido = EmodeSelection::PRACTICE;
                        musicaDelJuego->pararMusica();
                        musicaDelJuego->musicPractica();
                        initialize();
                        break;
                    };
                }
            }
            break;
        };
        case EgameState::MODE_ARCADE:
        case EgameState::MODE_MULTIPLAYER:
        case EgameState::MODE_PRACTICE:{
            if ( fight(inputs) == EgameResult::END){
                mState = EgameState::MENU_MODE;
                musicaDelJuego->pararMusica();
                initialize();
            }
            break;
        };
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

    EmodeSelection selection = mMenuGameMode->update(input,coordenadasMouse,mPantalla->getCuadradoModos());
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
    vector<Posicion> players = mMenuPlayers->update(inputs);
    mPantalla->update(players);
    mPantalla->print();

    if ( mMenuPlayers->selectionComplete() ) {
        personajesElegidos[0] = mMenuPlayers->personajesElegidos[0];
        personajesElegidos[1] = mMenuPlayers->personajesElegidos[1];
        return EgameResult::END;
    }
    return EgameResult::CONTINUE;
}

EgameResult Game::fight(vector<Tinput> inputs) {
    switch (inputs[0].game){
        case TinputGame::KEY_ESC:
            return EgameResult::END;
        default:{
            vector<Tcambio> c = mMundo->actualizarMundo(inputs,mState);

            sonidoPJ1->soundRounds(mState,mMundo->roundsPJ1, mMundo->roundsPJ2);

            sonidoPJ1->playFX(c.at(0).estado,inputs[0]);
            sonidoPJ2->playFX(c.at(1).estado,inputs[1]);

            mPantalla->update(c,inputs[0]);
            mPantalla->print();
            return ( mMundo->huboGanador() && modoDeJuegoElegido != EmodeSelection::PRACTICE ) ? EgameResult::END : EgameResult::CONTINUE;
        }
    };
}

Game::~Game() {
    delete musicaDelJuego;
    delete sonidoPJ1;
    delete sonidoPJ2;
    delete(mPantalla);
    if (mMundo != nullptr)
        delete(mMundo);
    if(mMenuPlayers != nullptr)
        delete mMenuPlayers;
    if(mMenuGameMode != nullptr)
        delete mMenuGameMode;
    delete(mConfiguration);
    Mix_Quit();
}

void Game::setInformacionPersonajesElegidos(int jugador) {
    switch(personajesElegidos[jugador]){

        case EtipoPersonaje::SUBZERO:
            nombrePjs[jugador] = "subzero";
            rutaSprites[jugador] = "./resources/sprites/subzero";
            break;
        case EtipoPersonaje::SUBZERO_GREEN:
            nombrePjs[jugador] = "subzero";
            rutaSprites[jugador] = "./resources/sprites/subzero";
            break;
        case EtipoPersonaje::SUBZERO_RED:
            nombrePjs[jugador] = "subzero";
            rutaSprites[jugador] = "./resources/sprites/subzero";
            break;
        case EtipoPersonaje::SUBZERO_YELLOW:
            nombrePjs[jugador] = "subzero";
            rutaSprites[jugador] = "./resources/sprites/subzero";
            break;
        case EtipoPersonaje::ERMAC:
            nombrePjs[jugador] = "ermac";
            rutaSprites[jugador] = "./resources/sprites/ermac";
            break;
        case EtipoPersonaje::ERMAC_BLUE:
            nombrePjs[jugador] = "ermac";
            rutaSprites[jugador] = "./resources/sprites/ermac";
            break;
        case EtipoPersonaje::ERMAC_GREEN:
            nombrePjs[jugador] = "ermac";
            rutaSprites[jugador] = "./resources/sprites/ermac";
            break;
        case EtipoPersonaje::ERMAC_YELLOW:
            nombrePjs[jugador] = "ermac";
            rutaSprites[jugador] = "./resources/sprites/ermac";
            break;
        case EtipoPersonaje::LIUKANG:
            nombrePjs[jugador] = "liukang";
            rutaSprites[jugador] = "./resources/sprites/liukang";
            break;
        case EtipoPersonaje::LIUKANG_BLUE:
            nombrePjs[jugador] = "liukang";
            rutaSprites[jugador] = "./resources/sprites/liukang";
            break;
        case EtipoPersonaje::LIUKANG_GREEN:
            nombrePjs[jugador] = "liukang";
            rutaSprites[jugador] = "./resources/sprites/liukang";
            break;
        case EtipoPersonaje::LIUKANG_YELLOW:
            nombrePjs[jugador] = "liukang";
            rutaSprites[jugador] = "./resources/sprites/liukang";
            break;
    }
}
