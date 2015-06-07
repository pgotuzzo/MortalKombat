#ifndef MORTALKOMBAT_GAMEUTILS_H
#define MORTALKOMBAT_GAMEUTILS_H

#include <string>
#include "PersonajeUtils.h"

enum class EmodeSelection {
    MULTIPLAYER,
    ARCADE,
    PRACTICE
};

enum class EgameResult {
    CONTINUE,
    END
};

enum class EcharacterType {
    SUBZERO,
    ERMAC
};

// TODO - Hay que editar los structs que venimos manejado hasta ahora!!
struct Tpersonaje2{
    std::string name;
    EcharacterType type;
};

struct TmenuPersonajeChange{
    Tpersonaje2 p1;
    Tpersonaje2 p2;
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

    int tiempoRound;
    float vida;

    // Para el poder
    TcambioPoder poder;
};

#endif //MORTALKOMBAT_GAMEUTILS_H
