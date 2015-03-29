#include "PersonajeFactory.h"

array< array< Sprite, Personaje::STATE_COUNT >, PersonajeFactory::PERSONAJES_COUNT> PersonajeFactory::SPRITES =
        array< array < Sprite, Personaje::STATE_COUNT >, PersonajeFactory::PERSONAJES_COUNT >();


void PersonajeFactory::createSprites(SDL_Renderer* renderer) {
    for(int p = 0; p < PERSONAJES_COUNT; p++){

        std::string personajePath = tipoPersonajeToString(TipoPersonaje(p));

        for (int s = 0; s < Personaje::STATE_COUNT; s++){

            Personaje::State state = Personaje::State(s);
            std::string spritesPath = personajePath + "/" + Personaje::stateToString(state) + "/";

            SPRITES[p][s] = Sprite(renderer, spritesPath);
        }

    }
}

std::string PersonajeFactory::tipoPersonajeToString(PersonajeFactory::TipoPersonaje t) {
    switch (t) {
        case liu_kang: return "liu_kang";
        case zub_zero: return "zub_zero";
        case kung_lao: return "kung_lao";
        case johnny_cage: return "johnny_cage";
        case reptile: return "reptile";
        case shang_tsung: return "shang_tsung";
        case kitana: return "kitana";
        case jax: return "jax";
        case mileena: return "mileena";
        case baraka: return "baraka";
        case scorpion: return "scorpion";
        case raiden: return "raiden";
        case kintaro: return "kintaro";
        case shao_kahn: return "shao_kahn";
    }
    return NULL;
}

Personaje* PersonajeFactory::getPersonaje(SDL_Renderer* renderer, PersonajeFactory::TipoPersonaje t) {
    if (SPRITES.empty()){
        createSprites(renderer);
    }
    Personaje* personaje = new Personaje(SPRITES[t]);
    return personaje;
}


