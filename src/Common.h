/**
 * Estructuras que se comparten entre
 *  - Configuracion
 *  - Modelo
 *  - Vista
 *  - Controlador
 */

#ifndef _MORTALKOMBAT_COMMON_H_
#define _MORTALKOMBAT_COMMON_H_

#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "parser/log/WarningLog.h"
#include "parser/log/DebugLog.h"
#include "parser/log/ErrorLog.h"

/**
 * Constantes
 */
static const string SPRITES_FORMAT = ".png";
static const float MIN_DISTANCE_FROM_BOUND = 20;
const float velocidadDelPoder = 30;

/**
 * Estas estructuras, pseudo-clases cruzan toda
 *  la aplicacion.
 */
struct Posicion{
    float x;
    float y;

    Posicion(float pos_x,float pos_y) {
        x = pos_x;
        y = pos_y;
    }

    float getX(){
        return x;
    }

    float getY(){
        return y;
    }

    Posicion(){
        x = 0;
        y = 0;
    }

    Posicion operator=(Posicion p){
        x = p.x;
        y = p.y;
        return p;
    }
    Posicion operator+(Posicion p){
        return Posicion(x + p.x, y + p.y);
    }
    Posicion operator-(Posicion p){
        return Posicion(x - p.x, y - p.y);
    }
    bool operator==(Posicion p){
        return (p.x == x) && (p.x == y);
    }

    void setX(float pos_x){
        x = pos_x;
    }

    void setY(float pos_y){
        y = pos_y;
    }

    void mostrarPar(){
        std::cout << "X: " << x << " - " << "Y: " << y << std::endl;
    }

};

struct Tdimension{
    float w;
    float h;

    Tdimension(){}

    Tdimension(float w, float h){
        this->w = w;
        this->h = h;
    }

    Tdimension(int w, int h){
        this->w = w;
        this->h = h;
    }
    Tdimension operator=(Tdimension d){
        w = d.w;
        h = d.h;
        return d;
    }
};

struct Trect {
    Tdimension d;
    Posicion p;

    Trect operator=(Trect rect){
        d = rect.d;
        p = rect.p;
        return rect;
    }
};

/**
 * Estructuras para la manipulacion de
 *  los colores.
 */
struct TcolorHSL{
    float h;
    float s;
    float l;

    static TcolorHSL fromRGB(uint8_t R, uint8_t G, uint8_t B){
        TcolorHSL color;
        float r, g, b, max, min, delta, aux;

        r = (float) R / 255;
        g = (float) G / 255;
        b = (float) B / 255;

        aux = std::fmax(r, g);
        max = fmax(aux, b);

        aux = fmin(r, g);
        min = fmin(aux, g);

        delta = max - min;

        // H
        if (delta == 0){
            color.h = 0;
        } else if (max == r){
            color.h = 60 * fmod( ( ( g - b ) / delta ), 6 );
        } else if (max == g){
            color.h = 60 * (( ( b - r ) / delta ) + 2 );
        } else if (max == b){
            color.h = 60 * (( ( r - g ) / delta ) + 4 );
        }
        color.h = (color.h >= 0) ? color.h : 360 + color.h;

        // L
        color.l = (max + min) / 2;

        // S
        color.s = (delta == 0) ? 0 : delta / ( 1 - fabs(max + min - 1) );

        return color;
    }
};

struct TcolorRGB{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    static TcolorRGB fromHSL(float H, float S, float L){
        TcolorRGB color;
        float c, x, m, R = 0, G = 0, B = 0;

        c = (1 - fabs(2*L - 1)) * S;
        x = c * ( 1 - fabs( fmod( (H/60), 2 ) - 1) );
        m = L - (c / 2);

        if ( (H >= 0) && (H < 60) ){
            R = c;
            G = x;
            B = 0;
        }else if ( (H >= 60) && (H < 120) ){
            R = x;
            G = c;
            B = 0;
        }else if ( (H >= 120) && (H < 180) ){
            R = 0;
            G = c;
            B = x;
        }else if ( (H >= 180) && (H < 240) ){
            R = 0;
            G = x;
            B = c;
        }else if ( (H >= 240) && (H < 300) ) {
            R = x;
            G = 0;
            B = c;
        }else if ( (H >= 300) && (H < 360) ){
            R = c;
            G = 0;
            B = x;
        }
        color.r = (uint8_t) ( 255 * (R + m) );
        color.g = (uint8_t) ( 255 * (G + m) );
        color.b = (uint8_t) ( 255 * (B + m) );

        return color;
    }
};

struct TcolorSettings{
    float hmin;
    float hmax;
    float delta;

    TcolorSettings(){}

    TcolorSettings(float min, float max, float d){
        hmin = (min < 0) ? - fmod(-min, 360) + 360 : fmod(min, 360);
        hmax = (max < 0) ? - fmod(-max, 360) + 360 : fmod(max, 360);
        delta = (d < 0) ? - fmod(-d, 360) + 360 : fmod(d, 360);
    }

};


/**
 * Loguer
 */
static Log* loguer = DebugLog::getInstance();

/**
 * Estructuras que se utilizan para
 *  definir la pantalla (px),  escenario
 *  y capa
 */
struct Tventana {
    Tdimension dimPx;
    float ancho;
    float distTope;
};

struct Tescenario {
    Tdimension d;
    float yPiso;
};

enum Tdireccion{
    DERECHA,
    IZQUIERDA
};

struct Tpersonaje {
    Tdimension d;
    int zIndex;
    Tdireccion orientacion = DERECHA;
    string nombre;
    string sprites;

    // para el personaje alternativo
    TcolorSettings colorSettings;
};

struct Tpelea {
    string player1;
    string player2;

    void valida(vector<Tpersonaje> personajes){
        string igual;
        int cont=0;
        for(unsigned int i=0;i<personajes.size();i++)
            if(!strcmp(player1.c_str(),personajes.at(i).nombre.c_str())||!strcmp(player2.c_str(),personajes.at(i).nombre.c_str())){
                igual=personajes.at(i).nombre;
                cont++;
            }
        if(cont==1){
            if(player1==igual)
                this->player2=igual;
            else
                player1=igual;
        }
        if(cont==0){
            player1=personajes.at(0).nombre;
            player2=personajes.at(0).nombre;
        }



    }
};

struct Tbotones{
    int highPunch;
    int lowPunch;
    int lowKick;
    int highKick;
    int poder;
    int proteccion;

    bool valorCorrecto(int num){
        if(num>=10&&num<=15)
            return true;
        else
            return false;
    }

    bool seRepiten(){
        bool repite;
        repite=(highPunch==lowPunch||highPunch==lowKick||highPunch==highKick||lowPunch==lowKick||lowPunch==highKick||lowKick==highKick);
        return repite;
    }

    void valida(){
        bool correcto=valorCorrecto(highPunch)&&valorCorrecto(lowPunch)
                      &&valorCorrecto(lowKick)&&valorCorrecto(highKick)
                      &&!seRepiten();

        if(!correcto){
            string mensajeError="Error de configuración de botones. Se cargan por defecto";
            loguer->loguear(mensajeError.c_str(),Log::Tlog::LOG_WAR);
            highKick=12; 		lowPunch=15;
            highPunch=13;		poder=11;
            lowKick=14;			proteccion=10;

        }
    }
};

struct Tcapa {
    std::string dirCapa;
    float ancho;
};


/**
 * Estructuras y enums propios de los
 *  Personajes
 */
static const int TestadoPersonajeCount = 26;

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

    ACC_PATADA_AGACHADO,
    ACC_PATADA_SALTO_VERTICAL,
    ACC_PATADA_SALTO, //oblicuo

    ACC_PATADA_ALTA,
    ACC_PATADA_ALTA_ATRAS,

    ACC_PROTECCION,
    ACC_PROTECCION_AGACHADO,

    ACC_PODER,

    // Reaccion
            REA_AGACHADO,
    REA_GOLPE_ALTO, // patada alta y pinia en salto
    REA_GOLPE_BAJO,
    REA_GOLPE_FUERTE, // gancho y patada alta (+ atras)
    REA_PATADA_BARRIDA, // patada baja (+ atras)
    REA_PINIA_ALTA
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

        case TestadoPersonaje::REA_AGACHADO: return "rea_agachado";
        case TestadoPersonaje::REA_GOLPE_ALTO: return "rea_golpe_alto";
        case TestadoPersonaje::REA_GOLPE_BAJO: return "rea_golpe_bajo";
        case TestadoPersonaje::REA_GOLPE_FUERTE: return "rea_golpe_fuerte";
        case TestadoPersonaje::REA_PATADA_BARRIDA: return "rea_patada_barrida";
        case TestadoPersonaje::REA_PINIA_ALTA: return "rea_pinia_alta";

    }
    return NULL;
}

enum Tsentido{
    ADELANTE,
    ATRAS
};


static const int TestadoPoderCount = 3;

enum TestadoPoder{
    ACTIVADO,
    DESACTIVADO,
    COLISION
};

static const string PODER_ACTIVADO_PATH = "pod_poder";
static const string PODER_COLISION_PATH = "pod_colision";

struct TcambioPoder{
    TestadoPoder e;
    Posicion p;
    Tdimension d;
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

    float vida;

    // Para el poder
    TcambioPoder poder;
};

/**
 * Enum con todos los posibles inputs que el
 *  juego debe ser capaz de manejar.
 */

enum class TinputMovimiento{
    KEY_NADA,

    KEY_ARRIBA,
    KEY_ABAJO,
    KEY_DERECHA,
    KEY_IZQUIERDA,
    KEY_ARRIBA_DERECHA,
    KEY_ARRIBA_IZQUIERDA
};

enum class TinputAccion{
    KEY_NADA,

    KEY_PINIA_ALTA,
    KEY_PINIA_BAJA,
    KEY_PATADA_ALTA,
    KEY_PATADA_BAJA,
    KEY_PROTECCION,
    KEY_PODER
};

enum class TinputGame{
    KEY_NADA,

    KEY_RESTART,
    KEY_EXIT
};

/**
 * Struct con todos los posibles inputs que el
 *  juego debe ser capaz de manejar.
 */
struct Tinput{
    TinputMovimiento movimiento=TinputMovimiento::KEY_NADA;
    TinputAccion accion=TinputAccion::KEY_NADA;
    TinputGame game= TinputGame::KEY_NADA;
};


//PERSONAJE ------------------------------

//funcion que devuelve la cantidad de loops que se hacen para cada accion

static int loopsPara(TestadoPersonaje accion){

    switch (accion){

        case MOV_PARADO:
            // infinito (?
            return 1;
        case MOV_CAMINANDO:
            return 1;
        case MOV_SALTANDO_VERTICAL:
            return 10;
        case MOV_SALTANDO_OBLICUO:
            return 20;
        case MOV_AGACHADO:
            return 1;
        case ACC_PINIA_BAJA:
            // OJO VER COMO SOLUCIONAR VARIOS ESTADOS
            return 4;
        case ACC_PINIA_BAJA_AGACHADO:
            return 4;
        case ACC_PINIA_ALTA:
            //pensar lo mismo que pinia baja
            return 4;
        case ACC_PINIA_ALTA_AGACHADO:
            return 5;
        case ACC_PINIA_SALTO:
            return 20;
        case ACC_PATADA_BAJA:
            return 12;
        case ACC_PATADA_BAJA_ATRAS:
            return 8;
        case ACC_PATADA_AGACHADO:
            return 4;
        case ACC_PATADA_SALTO_VERTICAL:
            return 10;
        case ACC_PATADA_SALTO:
            return 20;
        case ACC_PATADA_ALTA:
            return 12;
        case ACC_PATADA_ALTA_ATRAS:
            return 8;
        case ACC_PROTECCION:
            return 1;
        case ACC_PROTECCION_AGACHADO:
            return 1;
        case ACC_PODER:
            return 3;
        case REA_AGACHADO:
            return 1;
//        case REA_GOLPE_ALTO:
//            break;
//        case REA_GOLPE_BAJO:
//            break;
//        case REA_GOLPE_FUERTE:
//            break;
//        case REA_PATADA_BARRIDA:
//            break;
//        case REA_PINIA_ALTA:
//            break;
    }
}


#endif //_MORTALKOMBAT_COMMON_H_