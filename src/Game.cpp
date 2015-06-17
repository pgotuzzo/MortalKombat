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

    mPantalla = nullptr;
    mMundo = nullptr;
    mMenuGameMode = nullptr;
    mMenuPlayers = nullptr;

    mMusic = new Musica();

    initialize();
};

void Game::clean(){
    if (mPantalla != NULL){
        delete(mPantalla);
        mPantalla = NULL;
    }
    if (mMundo != NULL){
        delete(mMundo);
        mMundo = NULL;
    }
    if (mMenuGameMode != NULL) {
        delete(mMenuGameMode);
        mMenuGameMode = NULL;
    }
    if (mMenuPlayers != NULL) {
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

            mMusic->musicMenu();

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

            mMusic->pararMusica();
            mMusic->musicSeleccion();

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

            for (int i = 0; i < 2; i++){
                personajes[i].nombre = mPlayers[i].name;
                personajes[i].zIndex = 2;
                personajes[i].orientacion = (i == 0) ? DERECHA : IZQUIERDA;

                TinfoPersonaje info = getInfoPersonaje(mPlayers[i].type);
                personajes[i].d = info.dimension;
                personajes[i].sprites = info.spritesPath;
                personajes[i].colorSettings = info.colorSettings;
            }

            mPantalla = new PantallaArcade(capas, ventana, escenario, personajes);// Capas

            string names[2] = {mPlayers[0].name, mPlayers[1].name};
            mPantalla->initialize(capas, names);

            loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
            loguer->loguear("Creando el modelo...", Log::LOG_DEB);

            mMundo = new Mundo(*mConfiguration, names,mPlayers[0].type,mPlayers[1].type);
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

            for (int i = 0; i < 2; i++){
                personajes[i].nombre = mPlayers[i].name;
                personajes[i].zIndex = 2;
                personajes[i].orientacion = (i == 0) ? DERECHA : IZQUIERDA;

                TinfoPersonaje info = getInfoPersonaje(mPlayers[i].type);
                personajes[i].d = info.dimension;
                personajes[i].sprites = info.spritesPath;
                personajes[i].colorSettings = info.colorSettings;

            }

            mPantalla = new PantallaPractice(capas, ventana, escenario, personajes);

            // Capas
            string names[2] = {mPlayers[0].name, mPlayers[1].name};
            mPantalla->initialize(capas, names);

            loguer->loguear("Finaliza la creacion de la pantalla", Log::LOG_DEB);
            loguer->loguear("Creando el modelo...", Log::LOG_DEB);

            mMundo = new Mundo(*mConfiguration, names,mPlayers[0].type,mPlayers[1].type);

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
            if ( selectMode(inputs[0],coordenadasMouse) == EgameResult::END ) {
                switch (mModeSelection){
                    case EmodeSelection::MULTIPLAYER: {
                        mModeSelection = EmodeSelection::MULTIPLAYER;
                        break;
                    };
                    case EmodeSelection::ARCADE: {
                        mModeSelection = EmodeSelection::ARCADE;
                        break;
                    };
                    case EmodeSelection::PRACTICE: {
                        mModeSelection = EmodeSelection::PRACTICE;
                        break;
                    };
                }
                mState = EgameState::MENU_PLAYERS;
                initialize();
            }
            break;
        };
        case EgameState::MENU_PLAYERS:{
            bool aleatory = mModeSelection != EmodeSelection::MULTIPLAYER;
            if (selectPlayers(inputs,coordenadasMouse, aleatory) == EgameResult::END) {
                switch (mModeSelection) {
                    case EmodeSelection::MULTIPLAYER:
                        mState = EgameState::MODE_MULTIPLAYER;
                        break;
                    case EmodeSelection::ARCADE:
                        mState = EgameState::MODE_ARCADE;
                        break;
                    case EmodeSelection::PRACTICE:
                        mState = EgameState::MODE_PRACTICE;
                        break;
                }
                mMusic->pararMusica();
                mMusic->musicVs();
                initialize();
            }
            break;
        };
        case EgameState::MODE_ARCADE:
        case EgameState::MODE_MULTIPLAYER:
        case EgameState::MODE_PRACTICE:{
            if ( fight(inputs) == EgameResult::END){
                mState = EgameState::MENU_MODE;
                mMusic->pararMusica();
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

EgameResult Game::selectMode(Tinput input, Posicion coordenadasMouse) {
    vector<float> escalas = mPantalla->getEscalas();

    coordenadasMouse.x = coordenadasMouse.x / escalas[0];
    coordenadasMouse.y = coordenadasMouse.y / escalas[1];

    if(coordenadasMouse.x > 2 && coordenadasMouse.x < mConfiguration->getVentana().ancho-2) {
        mMenuGameMode->update(input, coordenadasMouse, mPantalla->getCuadradoModos());
    }
    mMenuGameMode->update(input);
    EmodeSelection selection = mMenuGameMode->getSelection();
    mPantalla->update(selection);
    mPantalla->print();

    if ( mMenuGameMode->selectionComplete() ) {
        mModeSelection = selection;
        return EgameResult::END;

    }
    return EgameResult::CONTINUE;
}

EgameResult Game::selectPlayers(vector<Tinput> inputs, Posicion coordenadasMouse, bool seleccionOponenteAleatorio) {
    PantallaMenuPlayers* pantalla = (PantallaMenuPlayers*) mPantalla;

    vector<float> escalas = mPantalla->getEscalas();

    coordenadasMouse.x = coordenadasMouse.x / escalas[0];
    coordenadasMouse.y = coordenadasMouse.y / escalas[1];

    Posicion p = pantalla->getRelativePosition(coordenadasMouse);

    TmenuPlayerChanges changes;
    if (mMenuPlayers->firstPlayerSelected() && seleccionOponenteAleatorio){
        Tinput i;
        i.game = TinputGame::CLICK_IZQ_MOUSE;
        i.movimiento = TinputMovimiento::KEY_NADA;
        changes = mMenuPlayers->update(i, Posicion(rand() % MenuPlayerSelection::COLUMNS, rand() % MenuPlayerSelection::ROWS) );
    } else {
        changes = mMenuPlayers->update(inputs.at(0), p);
    }

    pantalla->update(changes.positions, changes.names);
    pantalla->print();

    if ( mMenuPlayers->selectionComplete() ) {
        mPlayers[0].name = changes.names[0];
        mPlayers[0].type = getType(changes.positions[0]);
        mPlayers[1].name = changes.names[1];
        mPlayers[1].type = getType(changes.positions[1]);
        return EgameResult::END;
    }

    return EgameResult::CONTINUE;
}

EgameResult Game::fight(vector<Tinput> inputs) {
    switch (inputs[0].game){
        case TinputGame::KEY_ESC:
            return EgameResult::END;
        default:{
            vector<Tcambio> c = mMundo->actualizarMundo(inputs, mState);

            mMusic->soundRounds(mState, mMundo->roundsPJ1, mMundo->roundsPJ2);

            mMusic->playFX(c.at(0).estado,inputs[0]);
            mMusic->playFX(c.at(1).estado,inputs[1]);

            mPantalla->update(c,inputs[0]);
            mPantalla->print();
            return ( mMundo->huboGanador() && mModeSelection != EmodeSelection::PRACTICE ) ? EgameResult::END : EgameResult::CONTINUE;
        }
    };
}

Game::~Game() {
    clean();
    delete mMusic;
    delete(mConfiguration);
}
