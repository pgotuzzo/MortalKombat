#ifndef MORTALKOMBAT_MUSICA_H
#define MORTALKOMBAT_MUSICA_H


#include <SDL2/SDL_mixer.h>

#include "utils/PersonajeUtils.h"

class Musica {

private:
    //temas
    Mix_Music *musicaVersus = NULL;
    Mix_Music *musicaPractica = NULL;
    Mix_Music *seleccionPersonaje = NULL;

    // efectos
    Mix_Chunk *dizzy = NULL;//
    Mix_Chunk *congelado = NULL;//
    Mix_Chunk *gancho = NULL;//
    Mix_Chunk *ganchoRisa = NULL;//
    Mix_Chunk *agarraYtira = NULL;
    Mix_Chunk *golpe = NULL;//
    Mix_Chunk *golpeGrande = NULL;
    Mix_Chunk *golpePequenio = NULL;//
    Mix_Chunk *patada = NULL;//
    Mix_Chunk *recibioGolpe = NULL;
    Mix_Chunk *recibioGolpePatada = NULL;//
    Mix_Chunk *tiraPinia = NULL;//
    Mix_Chunk *resbalada = NULL;//
    Mix_Chunk *tiraCongela = NULL;//
    Mix_Chunk *saltaPinia = NULL;//
    Mix_Chunk *saltaPatada = NULL;//
    Mix_Chunk *salta = NULL;//

    //vector<int> contadores;

    int contadores[36];

public:

    Musica();
    virtual ~Musica();
    void musicVs();
    void musicPractica();
    void musicSeleccion();
    void playFX(TestadoPersonaje);


};



#endif //MORTALKOMBAT_MUSICA_H
