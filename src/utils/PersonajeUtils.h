#ifndef MORTALKOMBAT_PERSONAJEUTILS_H
#define MORTALKOMBAT_PERSONAJEUTILS_H

#include "Common.h"

/**
 * Estructuras y enums propios de los
 *  Personajes
 */

static const string PODER_ACTIVADO_PATH = "pod_poder";
static const string PODER_COLISION_PATH = "pod_colision";
static const int TestadoPersonajeCount = 42;

enum class EtipoPersonaje {
    SUBZERO,
    SUBZERO_GREEN,
    SUBZERO_RED,
    SUBZERO_YELLOW,

    ERMAC,
    ERMAC_BLUE,
    ERMAC_GREEN,
    ERMAC_YELLOW,

    LIUKANG,
    LIUKANG_BLUE,
    LIUKANG_GREEN,
    LIUKANG_YELLOW
};

static EtipoPersonaje getType(Posicion p){
    if ( p == Posicion(0,0) ) return EtipoPersonaje::SUBZERO;
    else if ( p == Posicion(1,0) ) return EtipoPersonaje::SUBZERO_GREEN;
    else if ( p == Posicion(2,0) ) return EtipoPersonaje::SUBZERO_RED;
    else if ( p == Posicion(3,0) ) return EtipoPersonaje::SUBZERO_YELLOW;
    else if ( p == Posicion(0,1) ) return EtipoPersonaje::ERMAC;
    else if ( p == Posicion(1,1) ) return EtipoPersonaje::ERMAC_BLUE;
    else if ( p == Posicion(2,1) ) return EtipoPersonaje::ERMAC_GREEN;
    else if ( p == Posicion(3,1) ) return EtipoPersonaje::ERMAC_YELLOW;
    else if ( p == Posicion(0,2) ) return EtipoPersonaje::LIUKANG;
    else if ( p == Posicion(1,2) ) return EtipoPersonaje::LIUKANG_BLUE;
    else if ( p == Posicion(2,2) ) return EtipoPersonaje::LIUKANG_GREEN;
    else if ( p == Posicion(3,2) ) return EtipoPersonaje::LIUKANG_YELLOW;
    else return EtipoPersonaje::SUBZERO;
}

struct TinfoPersonaje{
    string spritesPath;
    string defaulName;
    TcolorSettings colorSettings;
    Tdimension dimension;
};

static TinfoPersonaje getInfoPersonaje(EtipoPersonaje type) {
    TinfoPersonaje info;
    info.dimension = Tdimension(25, 60);
    switch(type){
        case EtipoPersonaje::SUBZERO:
            info.defaulName = "subzero";
            info.spritesPath = "./resources/sprites/subzero";
//            info.colorSettings;
            break;
        case EtipoPersonaje::SUBZERO_GREEN:
            info.defaulName = "subzero";
            info.spritesPath = "./resources/sprites/subzero";
//            info.colorSettings;
            break;
        case EtipoPersonaje::SUBZERO_RED:
            info.defaulName = "subzero";
            info.spritesPath = "./resources/sprites/subzero";
//            info.colorSettings;
            break;
        case EtipoPersonaje::SUBZERO_YELLOW:
            info.defaulName = "subzero";
            info.spritesPath = "./resources/sprites/subzero";
//            info.colorSettings;
            break;
        case EtipoPersonaje::ERMAC:
            info.defaulName = "ermac";
            info.spritesPath = "./resources/sprites/ermac";
//            info.colorSettings;
            break;
        case EtipoPersonaje::ERMAC_BLUE:
            info.defaulName = "ermac";
            info.spritesPath = "./resources/sprites/ermac";
//            info.colorSettings;
            break;
        case EtipoPersonaje::ERMAC_GREEN:
            info.defaulName = "ermac";
            info.spritesPath = "./resources/sprites/ermac";
//            info.colorSettings;
            break;
        case EtipoPersonaje::ERMAC_YELLOW:
            info.defaulName = "ermac";
            info.spritesPath = "./resources/sprites/ermac";
//            info.colorSettings;
            break;
        case EtipoPersonaje::LIUKANG:
            info.defaulName = "liukang";
            info.spritesPath = "./resources/sprites/liukang";
//            info.colorSettings;
            break;
        case EtipoPersonaje::LIUKANG_BLUE:
            info.defaulName = "liukang";
            info.spritesPath = "./resources/sprites/liukang";
//            info.colorSettings;
            break;
        case EtipoPersonaje::LIUKANG_GREEN:
            info.defaulName = "liukang";
            info.spritesPath = "./resources/sprites/liukang";
//            info.colorSettings;
            break;
        case EtipoPersonaje::LIUKANG_YELLOW:
            info.defaulName = "liukang";
            info.spritesPath = "./resources/sprites/liukang";
//            info.colorSettings;
            break;
    }
    return info;
}


enum TestadoPersonaje {
    // Movimient
    MOV_PARADO,
    MOV_CAMINANDO,
    MOV_SALTANDO_VERTICAL,
    MOV_SALTANDO_OBLICUO,
    MOV_AGACHADO,

    // Accion
    ACC_PINIA_BAJA,
    ACC_PINIA_BAJA_AGACHADO,
    ACC_PINIA_ALTA,
    ACC_PINIA_ALTA_AGACHADO, //gancho
    ACC_PINIA_SALTO,
    ACC_PATADA_BAJA,
    ACC_PATADA_BAJA_ATRAS,
    ACC_PINIA_SALTO_VERTICAL,
    ACC_PATADA_AGACHADO,
    ACC_PATADA_SALTO_VERTICAL,
    ACC_PATADA_SALTO, //oblicuo
    ACC_PATADA_ALTA,
    ACC_PATADA_ALTA_ATRAS,
    ACC_AGARRE,
    ACC_PROTECCION,
    ACC_PROTECCION_AGACHADO,
    ACC_PODER,
    ACC_PODER_SALTO,

    // Reaccion
    REA_AGACHADO,
    REA_GOLPE_ALTO, // patada alta y pinia en salto
    REA_GOLPE_BAJO,
    REA_GOLPE_FUERTE, // gancho y patada alta (+ atras)
    REA_PATADA_BARRIDA, // patada baja (+ atras)
    REA_PINIA_ALTA,
    REA_CAIDA,
    REA_AGARRE,
    REA_CONGELADO,
    REA_MALDITO,
    REA_DERROTA,
    REA_VICTORIA,
    REA_MAREADO,

    REA_FAT_FUEGO,
    REA_FAT_LEVANTA,
    REA_FAT_ARCADE,

    FAT_FUEGO,
    FAT_LEVANTA,
    FAT_ARCADE

};

static string TestadoPersonajeToString(TestadoPersonaje e){
    switch (e) {
        case TestadoPersonaje::MOV_PARADO: return "mov_parado";
        case TestadoPersonaje::MOV_CAMINANDO: return "mov_caminando";

        case TestadoPersonaje::MOV_SALTANDO_VERTICAL: return "mov_salto_vertical";
        case TestadoPersonaje::MOV_SALTANDO_OBLICUO: return "mov_salto_oblicuo";
        case TestadoPersonaje::MOV_AGACHADO: return "mov_agachado";

        case TestadoPersonaje::ACC_PINIA_BAJA: return "acc_pinia_baja";
        case TestadoPersonaje::ACC_PINIA_BAJA_AGACHADO: return "acc_pinia_baja_agachado";
        case TestadoPersonaje::ACC_PINIA_ALTA: return "acc_pinia_alta";
        case TestadoPersonaje::ACC_PINIA_ALTA_AGACHADO: return "acc_pinia_alta_agachado";
        case TestadoPersonaje::ACC_PINIA_SALTO: return "acc_pinia_salto";
        case TestadoPersonaje::ACC_PINIA_SALTO_VERTICAL: return "acc_pinia_salto";
        case TestadoPersonaje::ACC_PATADA_BAJA: return "acc_patada_baja";
        case TestadoPersonaje::ACC_PATADA_BAJA_ATRAS: return "acc_patada_baja_atras";
        case TestadoPersonaje::ACC_PATADA_AGACHADO: return "acc_patada_agachado";
        case TestadoPersonaje::ACC_PATADA_SALTO_VERTICAL: return "acc_patada_salto_vertical";
        case TestadoPersonaje::ACC_PATADA_SALTO: return "acc_patada_salto";
        case TestadoPersonaje::ACC_PATADA_ALTA: return "acc_patada_alta";
        case TestadoPersonaje::ACC_PATADA_ALTA_ATRAS: return "acc_patada_alta_atras";
        case TestadoPersonaje::ACC_PROTECCION: return "acc_proteccion";
        case TestadoPersonaje::ACC_PROTECCION_AGACHADO: return "acc_proteccion_agachado";
        case TestadoPersonaje::ACC_PODER: return "acc_poder";
        case TestadoPersonaje::ACC_PODER_SALTO: return "acc_poder";
        case TestadoPersonaje::ACC_AGARRE: return "acc_agarre";

        case TestadoPersonaje::REA_AGACHADO: return "rea_agachado";
        case TestadoPersonaje::REA_GOLPE_ALTO: return "rea_golpe_alto";
        case TestadoPersonaje::REA_GOLPE_BAJO: return "rea_golpe_bajo";
        case TestadoPersonaje::REA_GOLPE_FUERTE: return "rea_golpe_fuerte";
        case TestadoPersonaje::REA_CAIDA: return "rea_golpe_fuerte";
        case TestadoPersonaje::REA_PATADA_BARRIDA: return "rea_patada_barrida";
        case TestadoPersonaje::REA_PINIA_ALTA: return "rea_pinia_alta";
        case TestadoPersonaje::REA_AGARRE: return "rea_agarre";
        case TestadoPersonaje::REA_CONGELADO: return "rea_congelado";
        case TestadoPersonaje::REA_MALDITO: return"rea_poder_ermac";
        case TestadoPersonaje::REA_DERROTA: return"rea_derrota";
        case TestadoPersonaje::REA_MAREADO: return"rea_mareado";
        case TestadoPersonaje::REA_VICTORIA: return"rea_victoria";

        case TestadoPersonaje::REA_FAT_FUEGO: return"rea_fat_fuego";
        case TestadoPersonaje::FAT_FUEGO: return"fat_fuego";

        case TestadoPersonaje::REA_FAT_LEVANTA: return"rea_fat_levanta";
        case TestadoPersonaje::FAT_LEVANTA: return"fat_levanta";

        case TestadoPersonaje::REA_FAT_ARCADE: return"rea_fat_arcade";
        case TestadoPersonaje::FAT_ARCADE: return"fat_arcade";

    }
    return NULL;
}

enum Tsentido{
    ADELANTE,
    ATRAS
};

enum TestadoPoder{
    ACTIVADO,
    DESACTIVADO,
    COLISION
};

struct TcambioPoder{
    TestadoPoder e;
    Posicion p;
    Tdimension d;
};

enum Tresultado{
    NADA,
    GANO,
    PERDIO,
    EMPATO,
};

static int mostrarResultado(Tresultado resultado){
    switch (resultado) {
        case (NADA):cout<<"NADA"<<endl;
                    break;
        case (GANO):cout<<"GANO"<<endl;
                    break;
        case (PERDIO):cout<<"PERDIO"<<endl;
                    break;
    }
}
//funcion que devuelve la cantidad de loops que se hacen para cada accion
static int loopsPara(TestadoPersonaje accion){

    switch (accion){
        case MOV_PARADO:return 1;
        case MOV_CAMINANDO:return 1;
        case MOV_SALTANDO_VERTICAL:return 14;
        case MOV_SALTANDO_OBLICUO:return 20;
        case MOV_AGACHADO:return 3;

        case ACC_PINIA_BAJA:return 4;
        case ACC_PINIA_BAJA_AGACHADO:return 4;
        case ACC_PINIA_ALTA:return 4;
        case ACC_PINIA_ALTA_AGACHADO:return 5;
        case ACC_PINIA_SALTO:return 20;
        case ACC_PATADA_BAJA:return 9;
        case ACC_PATADA_BAJA_ATRAS:return 8;
        case ACC_PATADA_AGACHADO:return 4;
        case ACC_PATADA_SALTO_VERTICAL:return 14;
        case ACC_PINIA_SALTO_VERTICAL:return 14;
        case ACC_PATADA_SALTO:return 20;
        case ACC_PATADA_ALTA:return 8;
        case ACC_PATADA_ALTA_ATRAS:return 8;
        case ACC_PROTECCION:return 3;
        case ACC_PROTECCION_AGACHADO:return 3;
        case ACC_PODER:return 3;
        case ACC_PODER_SALTO:return 10;
        case ACC_AGARRE:return 9;

        case REA_AGACHADO:return 1;
        case REA_GOLPE_ALTO:return 8;
        case REA_GOLPE_BAJO:return 3;
        case REA_GOLPE_FUERTE:return 8;
        case REA_PATADA_BARRIDA:return 12;
        case REA_PINIA_ALTA:return 3;
        case REA_CAIDA:return 8;
        case REA_AGARRE:return 13;
        case REA_CONGELADO:return 40;
        case REA_MALDITO:return 6;
        case REA_DERROTA:return 15;
        case REA_VICTORIA:return 15;
        case REA_MAREADO:return 1000;

        case REA_FAT_FUEGO: return 30;
        case FAT_FUEGO: return 20;

        case REA_FAT_LEVANTA: return 24;
        case FAT_LEVANTA: return 24;

        case REA_FAT_ARCADE: return 30;
        case FAT_ARCADE: return 25;
    }
}

static int mostrarEstado(TestadoPersonaje accion){

    switch (accion){
        case(REA_MALDITO):cout<<"REA_MALDITO"<<endl;
            break;
        case REA_CONGELADO:cout<<"REA_CONGELADO"<<endl;
            break;
        case MOV_PARADO:cout<<"MOV_PARADO"<<endl;
            break;
        case MOV_CAMINANDO:cout<<"MOV_CAMINANDO"<<endl;
            break;
        case MOV_SALTANDO_VERTICAL:cout<<"MOV_SALTANDO_VERTICAL"<<endl;
            break;
        case MOV_SALTANDO_OBLICUO:cout<<"MOV_SALTANDO_OBLICUO"<<endl;
            break;
        case MOV_AGACHADO:cout<<"MOV_AGACHADO"<<endl;
            break;
        case ACC_PINIA_BAJA:cout<<"ACC_PINIA_BAJA"<<endl;
            break;
        case ACC_PINIA_BAJA_AGACHADO:cout<<"ACC_PINIA_BAJA_AGACHADO"<<endl;
            break;
        case ACC_PINIA_ALTA:cout<<"ACC_PINIA_ALTA"<<endl;
            break;
        case ACC_PINIA_ALTA_AGACHADO: cout<<"ACC_PINIA_ALTA_AGACHADO"<<endl;
            break;
        case ACC_PINIA_SALTO:cout<<"ACC_PINIA_SALTO"<<endl;
            break;
        case ACC_PATADA_BAJA:cout<<"ACC_PATADA_BAJA"<<endl;
            break;
        case ACC_PATADA_BAJA_ATRAS:cout<<"ACC_PATADA_BAJA_ATRAS"<<endl;
            break;
        case ACC_PATADA_AGACHADO:cout<<"ACC_PATADA_AGACHADO"<<endl;
            break;
        case ACC_PATADA_SALTO_VERTICAL:cout<<"ACC_PATADA_SALTO_VERTICAL"<<endl;
            break;
        case ACC_PATADA_SALTO:cout<<"ACC_PATADA_SALTO"<<endl;
            break;
        case ACC_PATADA_ALTA:cout<<"ACC_PATADA_ALTA"<<endl;
            break;
        case ACC_PATADA_ALTA_ATRAS:cout<<"ACC_PATADA_ALTA_ATRAS"<<endl;
            break;
        case ACC_PROTECCION:cout<<"ACC_PROTECCION"<<endl;
            break;
        case ACC_PROTECCION_AGACHADO:cout<<"ACC_PROTECCION_AGACHADO"<<endl;
            break;
        case ACC_PODER:cout<<"ACC_PODER"<<endl;
            break;
        case REA_AGACHADO:cout<<"REA_AGACHADO"<<endl;
            break;
        case REA_GOLPE_ALTO:cout<<"REA_GOLPE_ALTO"<<endl;
            break;
        case REA_GOLPE_BAJO:cout<<"REA_GOLPE_BAJO"<<endl;
            break;
        case REA_GOLPE_FUERTE:cout<<"REA_GOLPE_FUERTE"<<endl;
            break;
        case REA_PATADA_BARRIDA:cout<<"REA_PATADA_BARRIDA"<<endl;
            break;
        case REA_PINIA_ALTA:cout<<"REA_PINIA_ALTA"<<endl;
            break;
        case ACC_PINIA_SALTO_VERTICAL:cout<<"ACC_PATADA_SALTO_VERTICAL"<<endl;
            break;
        case ACC_PODER_SALTO:cout<<"ACC_PODER_SALTO";
            break;
        case REA_CAIDA:cout<<"REA_CAIDA"<<endl;
            break;
        case REA_AGARRE:cout<<"REA_AGARRE"<<endl;
            break;
        case ACC_AGARRE:cout<<"ACC_AGARRE"<<endl;
            break;
        case REA_DERROTA:cout<<"REA_DERROTA"<<endl;
            break;
        case REA_VICTORIA:cout<<"REA_VICTORIA"<<endl;
            break;
        case REA_MAREADO:cout<<"REA_MAREADO"<<endl;
            break;
        case REA_FAT_FUEGO:cout<<"REA_FAT_FUEGO"<<endl;
            break;
        case FAT_FUEGO:cout<<"FAT_FUEGO"<<endl;
            break;
        case REA_FAT_LEVANTA:cout<<"REA_FAT_LEVANTA"<<endl;
            break;
        case FAT_LEVANTA:cout<<"FAT_LEVANTA"<<endl;
            break;
    }
}

#endif //MORTALKOMBAT_PERSONAJEUTILS_H