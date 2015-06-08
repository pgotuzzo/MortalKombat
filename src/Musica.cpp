#include "Musica.h"

const string ruta = "/home/miguel/ClionProjects/MortalKombat/resources/musica/";
Musica::Musica() {
    for(size_t i = 0 ; i < 36 ; i++)
        contadores[i] = 0;

    SDL_Init(SDL_INIT_AUDIO);
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

        seleccionPersonaje = Mix_LoadMUS( (ruta + "selecciondePersonaje.wav").c_str() );
        if( seleccionPersonaje == NULL )
            loguer->loguear("Error al cargar Musica Seleccion Personaje",Log::Tlog::LOG_WAR);

        golpe = Mix_LoadWAV( (ruta + "golpe.wav").c_str() );
        if( golpe == NULL )
            loguer->loguear("Error al cargar golpe",Log::Tlog::LOG_WAR);

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

    }

}

Musica::~Musica() {

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
    Mix_FreeChunk( resbalada );
    Mix_FreeChunk( tiraPinia );
    Mix_FreeChunk( congelado );
    Mix_FreeChunk( dizzy );
    congelado = NULL;
    dizzy = NULL;
    gancho = NULL;
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
    musicaVersus = NULL;
    musicaPractica = NULL;
    seleccionPersonaje = NULL;
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

void Musica::playFX(TestadoPersonaje estado){
    contadores[estado]++;

    mostrarEstado(estado);
    if ( contadores[estado] == 1 )

        switch( estado ){

            case REA_CONGELADO: Mix_PlayChannel( -1, congelado, 0 );break;

            case REA_PINIA_ALTA: Mix_PlayChannel( -1, golpe, 0 );break;

            case REA_MAREADO: Mix_PlayChannel( -1, dizzy, 0 );break;

                //case REA_GOLPE_FUERTE:Mix_PlayChannel( -1, ganchoRisa, 0 );break;

            case ACC_PINIA_ALTA_AGACHADO:Mix_PlayChannel( -1, gancho, 0 );break;

            case ACC_PINIA_BAJA:
            case ACC_PINIA_ALTA: Mix_PlayChannel( -1, tiraPinia, 0 );break;

            case REA_AGACHADO:Mix_PlayChannel( -1, golpePequenio, 0 );break;

            case REA_GOLPE_ALTO:Mix_PlayChannel( -1, resbalada, 0 );break;

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

            case REA_PATADA_BARRIDA:Mix_PlayChannel( -1, recibioGolpePatada, 0 );break;
        }

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