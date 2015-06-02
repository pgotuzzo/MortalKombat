#ifndef MORTALKOMBAT_GAMEUTILS_H
#define MORTALKOMBAT_GAMEUTILS_H

#include <string>

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

#endif //MORTALKOMBAT_GAMEUTILS_H
