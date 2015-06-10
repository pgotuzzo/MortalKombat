#include "Musica.h"

const string ruta = "/home/miguel/ClionProjects/MortalKombat/resources/musica/";
Musica::Musica() {
    for(size_t i = 0 ; i < 36 ; i++)
        contadores[i] = 0;
    if(SDL_WasInit(SDL_INIT_AUDIO)==0)SDL_InitSubSystem(SDL_INIT_AUDIO);
    //abre SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        loguer->loguear("SDL_mixer error no se pudo iniciar",Log::Tlog::LOG_ERR );
    }else {

        musicaVersus = Mix_LoadMUS( (ruta + "musicaVersus.wav").c_str() );
        if( musicaVersus == NULL )
            loguer->loguear("Error al cargar Musica Versus",Log::Tlog::LOG_WAR);

        musicaPractica = Mix_LoadMUS( (ruta + "musicaPractica.wav").c_str() );
        if( musicaPractica == NULL )
            loguer->loguear("Error al cargar Musica Practica",Log::Tlog::LOG_WAR);

        musicaMenu = Mix_LoadMUS( (ruta + "musicaMenu.wav").c_str() );
        if( musicaMenu == NULL )
            loguer->loguear("Error al cargar Musica Menu",Log::Tlog::LOG_WAR);

        seleccionPersonaje = Mix_LoadMUS( (ruta + "selecciondePersonaje.wav").c_str() );
        if( seleccionPersonaje == NULL )
            loguer->loguear("Error al cargar Musica Seleccion Personaje",Log::Tlog::LOG_WAR);

        movimientoEntreseleccion = Mix_LoadWAV( (ruta + "movimientoEntreseleccion.wav").c_str() );
        if( movimientoEntreseleccion == NULL )
            loguer->loguear("Error al cargar movimientoEntreseleccion",Log::Tlog::LOG_WAR);

        golpe = Mix_LoadWAV( (ruta + "golpe.wav").c_str() );
        if( golpe == NULL )
            loguer->loguear("Error al cargar golpe",Log::Tlog::LOG_WAR);

        apreto = Mix_LoadWAV( (ruta + "apreto.wav").c_str() );
        if( apreto == NULL )
            loguer->loguear("Error al cargar apreto",Log::Tlog::LOG_WAR);

        gancho = Mix_LoadWAV( (ruta + "Gancho.wav").c_str() );
        if( gancho == NULL )
            loguer->loguear("Error al cargar gancho",Log::Tlog::LOG_WAR);

        ganchoRisa = Mix_LoadWAV( (ruta + "ganchoRisa.wav").c_str() );
        if( ganchoRisa == NULL )
            loguer->loguear("Error al cargar gancho Risa",Log::Tlog::LOG_WAR);

        salta = Mix_LoadWAV( (ruta + "salta.wav").c_str() );
        if( salta == NULL )
            loguer->loguear("Error al cargar salta",Log::Tlog::LOG_WAR);

        saltaPinia = Mix_LoadWAV( (ruta + "saltaPinia.wav").c_str() );
        if( saltaPinia == NULL )
            loguer->loguear("Error al cargar salta Pinia",Log::Tlog::LOG_WAR);

        saltaPatada = Mix_LoadWAV( (ruta + "saltaPatada.wav").c_str() );
        if( saltaPatada == NULL )
            loguer->loguear("Error al cargar salta patada",Log::Tlog::LOG_WAR);

        tiraCongela = Mix_LoadWAV( (ruta + "tiraCongela.wav").c_str() );
        if( tiraCongela == NULL )
            loguer->loguear("Error al cargar tira Congela",Log::Tlog::LOG_WAR);

        agarraYtira = Mix_LoadWAV( (ruta + "agarraYtira.wav").c_str() );
        if( agarraYtira == NULL )
            loguer->loguear("Error al cargar agarra y tira",Log::Tlog::LOG_WAR);

        golpeGrande = Mix_LoadWAV( (ruta + "golpeGrande.wav").c_str() );
        if( golpeGrande == NULL )
            loguer->loguear("Error al cargar golpe Grande",Log::Tlog::LOG_WAR);

        golpePequenio = Mix_LoadWAV( (ruta + "golpePequenio.wav").c_str() );
        if( golpeGrande == NULL )
            loguer->loguear("Error al cargar golpe pequenio",Log::Tlog::LOG_WAR);

        patada = Mix_LoadWAV( (ruta + "patada.wav").c_str() );
        if( patada == NULL )
            loguer->loguear("Error al cargar patada",Log::Tlog::LOG_WAR);

        tiraPinia = Mix_LoadWAV( (ruta + "tiraPinia.wav").c_str() );
        if( tiraPinia == NULL )
            loguer->loguear("Error al cargar tira Pinia",Log::Tlog::LOG_WAR);

        recibioGolpe = Mix_LoadWAV( (ruta + "recibioGolpe.wav").c_str() );
        if( recibioGolpe == NULL )
            loguer->loguear("Error al cargar recibio golpe",Log::Tlog::LOG_WAR);

        recibioGolpePatada = Mix_LoadWAV( (ruta + "recibioGolpePatada.wav").c_str() );
        if( recibioGolpePatada == NULL )
            loguer->loguear("Error al cargar recibio golpe patada",Log::Tlog::LOG_WAR);

        resbalada = Mix_LoadWAV( (ruta + "resbalada.wav").c_str() );
        if( resbalada == NULL )
            loguer->loguear("Error al cargar resbalada",Log::Tlog::LOG_WAR);

        congelado = Mix_LoadWAV( (ruta + "congelado.wav").c_str() );
        if( congelado == NULL )
            loguer->loguear("Error al cargar congelado",Log::Tlog::LOG_WAR);

        dizzy = Mix_LoadWAV( (ruta + "dizzy.wav").c_str() );
        if( dizzy == NULL )
            loguer->loguear("Error al cargar dizzy",Log::Tlog::LOG_WAR);



        youNeverWin = Mix_LoadWAV( (ruta + "youNeverWinFight.wav").c_str() );
        if( youNeverWin == NULL )
            loguer->loguear("Error al cargar youNeverWin",Log::Tlog::LOG_WAR);

        round1 = Mix_LoadWAV( (ruta + "round1Fight.wav").c_str() );
        if( round1 == NULL )
            loguer->loguear("Error al cargar round1",Log::Tlog::LOG_WAR);

        round2 = Mix_LoadWAV( (ruta + "round2Fight.wav").c_str() );
        if( round2 == NULL )
            loguer->loguear("Error al cargar round2",Log::Tlog::LOG_WAR);

        round3 = Mix_LoadWAV( (ruta + "round3Fight.wav").c_str() );
        if( round3 == NULL )
            loguer->loguear("Error al cargar round3",Log::Tlog::LOG_WAR);

        fatality = Mix_LoadWAV( (ruta + "fatality.wav").c_str() );
        if( fatality == NULL )
            loguer->loguear("Error al cargar fatality",Log::Tlog::LOG_WAR);

        reacGancho = Mix_LoadWAV( (ruta + "reacGancho.wav").c_str() );
        if( reacGancho == NULL )
            loguer->loguear("Error al cargar reacGancho",Log::Tlog::LOG_WAR);

        caeAgarre = Mix_LoadWAV( (ruta + "caeAgarre.wav").c_str() );
        if( caeAgarre == NULL )
            loguer->loguear("Error al cargar caeAgarre",Log::Tlog::LOG_WAR);

        atrasBaja = Mix_LoadWAV( (ruta + "atrasBaja.wav").c_str() );
        if( atrasBaja == NULL )
            loguer->loguear("Error al cargar atrasBaja",Log::Tlog::LOG_WAR);

        atrasAlta = Mix_LoadWAV( (ruta + "atrasAlta.wav").c_str() );
        if( atrasAlta == NULL )
            loguer->loguear("Error al cargar atrasAlta",Log::Tlog::LOG_WAR);

        quema = Mix_LoadWAV( (ruta + "quema.wav").c_str() );
        if( quema == NULL )
            loguer->loguear("Error al cargar quema",Log::Tlog::LOG_WAR);

        tiraFat = Mix_LoadWAV( (ruta + "tiraFat.wav").c_str() );
        if( tiraFat == NULL )
            loguer->loguear("Error al cargar tiraFat",Log::Tlog::LOG_WAR);
    }

}

Musica::~Musica() {

    Mix_FreeChunk( atrasBaja );
    Mix_FreeChunk( atrasAlta );
    Mix_FreeChunk( gancho );
    Mix_FreeChunk( ganchoRisa );
    Mix_FreeChunk( tiraCongela );
    Mix_FreeChunk( saltaPinia );
    Mix_FreeChunk( saltaPatada );
    Mix_FreeChunk( salta );
    Mix_FreeChunk( agarraYtira );
    Mix_FreeChunk( golpe );
    Mix_FreeChunk( golpeGrande );
    Mix_FreeChunk( golpePequenio );
    Mix_FreeChunk( patada );
    Mix_FreeChunk( recibioGolpe );
    Mix_FreeChunk( recibioGolpePatada );
    Mix_FreeChunk( tiraPinia );
    Mix_FreeChunk( congelado );
    Mix_FreeChunk( dizzy );
    Mix_FreeChunk( apreto );
    Mix_FreeChunk( fatality );
    Mix_FreeChunk( round1 );
    Mix_FreeChunk( round2 );
    Mix_FreeChunk( round3 );
    Mix_FreeChunk( youNeverWin );
    Mix_FreeChunk( reacGancho );
    Mix_FreeChunk( caeAgarre );
    Mix_FreeChunk( resbalada );
    Mix_FreeChunk( quema );
    Mix_FreeChunk( tiraFat );
    tiraFat=NULL;
    quema= NULL;
    caeAgarre = NULL;
    reacGancho = NULL;;
    atrasBaja = NULL;
    atrasAlta = NULL;
    round3 = NULL;
    round2 = NULL;
    round1 = NULL;
    fatality = NULL;
    congelado = NULL;
    dizzy = NULL;
    apreto=NULL;
    gancho = NULL;
    youNeverWin = NULL;
    tiraPinia=NULL;
    agarraYtira = NULL;
    golpe = NULL;
    golpeGrande = NULL;
    golpePequenio = NULL;
    patada = NULL;
    recibioGolpe = NULL;
    recibioGolpePatada = NULL;
    resbalada = NULL;
    salta = NULL;
    saltaPatada = NULL;
    saltaPinia = NULL;
    ganchoRisa = NULL;

    Mix_FreeMusic( musicaVersus );
    Mix_FreeMusic( musicaPractica );
    Mix_FreeMusic( seleccionPersonaje );
    Mix_FreeMusic( musicaMenu );
    musicaVersus = NULL;
    resbalada=NULL;
    musicaPractica = NULL;
    seleccionPersonaje = NULL;
    musicaMenu = NULL;
    Mix_CloseAudio();
    Mix_Quit();
}

void Musica::musicVs(){
    if( Mix_PlayingMusic() == 0 ){
        Mix_PlayMusic( musicaVersus, -1 );

    }else if( Mix_PausedMusic() == 1 ){
        Mix_ResumeMusic();

    }else
        Mix_PauseMusic();
}

void Musica::musicMenu(){
    if( Mix_PlayingMusic() == 0 ){
        Mix_PlayMusic( musicaMenu, -1 );

    }else if( Mix_PausedMusic() == 1 ){
        Mix_ResumeMusic();

    }else
        Mix_PauseMusic();
}

void Musica::musicPractica(){

    if( Mix_PlayingMusic() == 0 ){
        Mix_PlayMusic( musicaPractica, -1 );

    }else if( Mix_PausedMusic() == 1 ){
        Mix_ResumeMusic();

    }else
        Mix_PauseMusic();
}

void Musica::musicSeleccion(){

    if( Mix_PlayingMusic() == 0 ){
        Mix_PlayMusic( seleccionPersonaje, -1 );

    }else if( Mix_PausedMusic() == 1 ){
        Mix_ResumeMusic();

    }else
        Mix_PauseMusic();
}

void Musica::selecciona(){
    Mix_PlayChannel( -1, movimientoEntreseleccion, 0 );
}

void Musica::click(){
    Mix_PlayChannel( -1, apreto, 0 );
}


void Musica::sRound1(){
    Mix_PlayChannel( -1, round1, 0 );
}

void Musica::sRound2(){
    Mix_PlayChannel( -1, round2, 0 );
}

void Musica::sRound3(){
    Mix_PlayChannel( -1, round3, 0 );
}

void Musica::sYouNeverWin(){
    Mix_PlayChannel( -1, youNeverWin, 0 );
}

void Musica::sFatality(){
    Mix_PlayChannel( -1, fatality, 0 );
}

void Musica::soundRounds(EgameState mState, int roundP1 , int roundP2){
    int rounds = roundP1 + roundP2 + 1 ;

    if(rounds != anteriorRound && (mState == EgameState::MODE_ARCADE
                                   || mState == EgameState::MODE_MULTIPLAYER )){

        if ( mState == EgameState:: MODE_ARCADE && rounds == 1 )
            sYouNeverWin();

        else if( rounds == 1 && mState != EgameState:: MODE_ARCADE ){
            sRound1();

        }else if( rounds == 2 ){
            sRound2();

        } else if( rounds == 3 && roundP1 == 1 && roundP2 == 1){
            sRound3();
        }

    }
    anteriorRound = rounds;

}

void Musica::playFX(TestadoPersonaje estado, Tinput input){
    contadores[estado]++;

    //mostrarEstado(estado);
    if ( ( contadores[estado] == 1 && estado != REA_FAT_FUEGO  && estado != REA_AGARRE && estado != FAT_FUEGO  ) ||
         ( estado == REA_FAT_FUEGO && contadores[REA_FAT_FUEGO] == loopsPara(REA_FAT_FUEGO) )
         || ( estado == REA_AGARRE && contadores[REA_AGARRE] == loopsPara(REA_AGARRE) )
         || ( estado == FAT_FUEGO && contadores[FAT_FUEGO] == 8 ))

        switch( estado ){

            case REA_AGARRE: Mix_PlayChannel( -1, caeAgarre, 0 );break;

            case FAT_FUEGO:Mix_PlayChannel( -1, tiraFat, 0 );break;

            case REA_FAT_FUEGO:
                Mix_PlayChannel( -1, fatality, 0 );
                Mix_PlayChannel( -1, quema, 0 );
                break;

            case REA_CONGELADO: Mix_PlayChannel( -1, congelado, 0 );break;

            case REA_GOLPE_ALTO:
            case REA_GOLPE_BAJO:
            case REA_PINIA_ALTA: Mix_PlayChannel( -1, golpe, 0 );break;

            case REA_MAREADO: Mix_PlayChannel( -1, dizzy, 0 );break;

            case REA_GOLPE_FUERTE:{
                Mix_PlayChannel( -1, reacGancho, 0 );
                if(input.accion == TinputAccion::KEY_PINIA_ALTA)
                    Mix_PlayChannel( -1, ganchoRisa, 0 );break;

            }

            case ACC_AGARRE: Mix_PlayChannel( -1, agarraYtira, 0 );break;

            case ACC_PINIA_ALTA_AGACHADO:Mix_PlayChannel( -1, gancho, 0 );break;

            case ACC_PINIA_BAJA:
            case ACC_PINIA_ALTA: Mix_PlayChannel( -1, tiraPinia, 0 );break;

            case REA_AGACHADO:Mix_PlayChannel( -1, golpePequenio, 0 );break;

            case MOV_SALTANDO_OBLICUO:
            case MOV_SALTANDO_VERTICAL:{
                Mix_PlayChannel( -1, salta, 0 );break;
            }

            case ACC_PODER_SALTO:
            case ACC_PODER:Mix_PlayChannel( -1, tiraCongela, 0 );break;

            case ACC_PATADA_SALTO:
            case ACC_PATADA_SALTO_VERTICAL:Mix_PlayChannel( -1, saltaPatada, 0 );break;

            case ACC_PINIA_SALTO:Mix_PlayChannel( -1, saltaPinia, 0 );break;

            case ACC_PATADA_ALTA:
            case ACC_PATADA_BAJA:Mix_PlayChannel( -1, patada, 0 );break;

            case ACC_PATADA_ALTA_ATRAS:Mix_PlayChannel( -1, atrasAlta, 0 );break;

            case ACC_PATADA_BAJA_ATRAS: Mix_PlayChannel( -1, atrasBaja, 0 );break;

            case REA_PATADA_BARRIDA:Mix_PlayChannel( -1, recibioGolpePatada, 0 );break;
        }

    if( ( estado == REA_GOLPE_FUERTE && contadores[REA_GOLPE_FUERTE] == loopsPara(REA_GOLPE_FUERTE) ) )
        Mix_PlayChannel( -1, caeAgarre, 0 );

    int loopTotal1 = contadores[MOV_SALTANDO_VERTICAL] + contadores[ACC_PINIA_SALTO_VERTICAL];
    int loopTotal2=  contadores[MOV_SALTANDO_VERTICAL] + contadores[ACC_PATADA_SALTO_VERTICAL ];
    int loopTotal3 = contadores[MOV_SALTANDO_VERTICAL] + contadores[ACC_PODER_SALTO];
    int loopTotal4 = contadores[MOV_SALTANDO_OBLICUO ] + contadores[ACC_PINIA_SALTO ];
    int loopTotal5 = contadores[MOV_SALTANDO_OBLICUO ] + contadores[ACC_PATADA_SALTO];

    if( loopTotal5 == loopsPara(ACC_PATADA_SALTO) ){
        contadores[MOV_SALTANDO_OBLICUO] = 0;
        contadores[ACC_PATADA_SALTO] = 0;
    }

    if( loopTotal4 == loopsPara(ACC_PINIA_SALTO) ){
        contadores[MOV_SALTANDO_OBLICUO] = 0;
        contadores[ACC_PINIA_SALTO ] = 0;
    }

    if( loopTotal3 == loopsPara(ACC_PODER_SALTO) ){
        contadores[MOV_SALTANDO_VERTICAL] = 0;
        contadores[ACC_PODER_SALTO ] = 0;
    }

    if( loopTotal2 == loopsPara(ACC_PATADA_SALTO_VERTICAL) ){
        contadores[MOV_SALTANDO_VERTICAL] = 0;
        contadores[ACC_PATADA_SALTO_VERTICAL] = 0;
    }

    if( loopTotal1 == loopsPara(ACC_PINIA_SALTO_VERTICAL) ){
        contadores[MOV_SALTANDO_VERTICAL] = 0;
        contadores[ACC_PINIA_SALTO_VERTICAL ] = 0;
    }

    if ( contadores[estado] == loopsPara ( estado ) )
        contadores[estado]=0;

}