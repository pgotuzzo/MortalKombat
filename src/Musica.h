#ifndef MORTALKOMBAT_MUSICA_H
#define MORTALKOMBAT_MUSICA_H


#include <SDL2/SDL_mixer.h>

#include "utils/PersonajeUtils.h"
#include "utils/GameUtils.h"
class Musica {

private:
    //temas
    Mix_Music *musicaVersus = NULL;
    Mix_Music *musicaPractica = NULL;
    Mix_Music *seleccionPersonaje = NULL;
    Mix_Music *musicaMenu = NULL;


    Mix_Chunk * movimientoEntreseleccion= NULL;
    Mix_Chunk * apreto= NULL;
    Mix_Chunk * youNeverWin= NULL;
    Mix_Chunk * round1= NULL;
    Mix_Chunk * round2= NULL;
    Mix_Chunk * round3= NULL;
    Mix_Chunk * fatality= NULL;



    // efectos
    Mix_Chunk *resbalada = NULL;//
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
    Mix_Chunk *tiraCongela = NULL;//
    Mix_Chunk *saltaPinia = NULL;//
    Mix_Chunk *saltaPatada = NULL;//
    Mix_Chunk *salta = NULL;//
    Mix_Chunk *reacGancho = NULL;//
    Mix_Chunk *caeAgarre = NULL;//
    Mix_Chunk *atrasAlta = NULL;//
    Mix_Chunk *atrasBaja = NULL;//
    Mix_Chunk *quema = NULL;//
    Mix_Chunk *tiraFat = NULL;//

    //vector<int> contadores;
    int anteriorRound=0;

    int contadores[36];

public:

    Musica();
    virtual ~Musica();
    void musicVs();
    void musicPractica();
    void musicSeleccion();
    void musicMenu();

    void selecciona();
    void click();

    void sFatality();
    void sYouNeverWin();
    void sRound1();
    void sRound2();
    void sRound3();

    void soundRounds(EgameState,int,int);

    void playFX(TestadoPersonaje, Tinput);


};



#endif //MORTALKOMBAT_MUSICA_H