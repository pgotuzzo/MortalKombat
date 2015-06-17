#ifndef MORTALKOMBAT_GAMEUTILS_H
#define MORTALKOMBAT_GAMEUTILS_H

#include <string>
#include <array>
#include "PersonajeUtils.h"

enum class EmodeSelection {
    MULTIPLAYER,
    ARCADE,
    PRACTICE
};

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

enum class EgameResult {
    CONTINUE,
    END
};

struct Tplayer{
    string name;
    EtipoPersonaje type;
};

struct TmenuPlayerChanges{
    array<Posicion, 2> positions;
    array<string, 2> names;
};

/**
 * Estructura que media entre el modelo y
 *  la vista y tiene como finalidad contener
 *  todos los cambios que se produjeron a lo
 *  largo de un gameloop.
 */
struct Tcambio{
    Posicion posicion;
    TestadoPersonaje estado;
    Tdireccion direccion;
    Tsentido sentido;
    Tdimension dPJ;
    bool hayCombo;
    string nombreCombo;

    int tiempoRound;
    float vida;

    // Para el poder
    TcambioPoder poder;
};

#endif //MORTALKOMBAT_GAMEUTILS_H
