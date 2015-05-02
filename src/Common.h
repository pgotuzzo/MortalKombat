/**
 * Estructuras que se comparten entre
 *  - Configuracion
 *  - Modelo
 *  - Vista
 *  - Controlador
 */

#ifndef _MORTALKOMBAT_COMMON_H_
#define _MORTALKOMBAT_COMMON_H_

#include <string>
#include <iostream>
#include "parser/log/WarningLog.h"
#include "parser/log/DebugLog.h"
#include "parser/log/ErrorLog.h"

/**
 * Esta estructura, pseudo-clase cruza toda
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
};

struct Trect {
    Tdimension d;
    Posicion p;
};

/**
 * Loguer
 */
static Log* loguer = DebugLog::getInstance();

/**
 * Estructuras que se utilizan para
 *  definir la pantalla (px) y el
 *  escenario
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

struct Tcapa {
    std::string dirCapa;
    float ancho;
};


/**
 * Estructuras y enums propios de los
 *  Personajes
 */
enum TestadoPersonaje {
    PARADO,
    CAMINANDO,
    SALTANDO_VERTICAL,
    SALTANDO_OBLICUO,
    AGACHADO,
    PINIA_ALTA,
    PINIA_BAJA,
    PATADA_ALTA,
    PATADA_BAJA,
    PODER,
    PROTECCION
};

static std::string TestadoPersonajeToString(TestadoPersonaje e) {
    switch (e) {
        case TestadoPersonaje::PARADO: return "parado";
        case TestadoPersonaje::CAMINANDO: return "caminando";
        case TestadoPersonaje::SALTANDO_VERTICAL: return "salto_vertical";
        case TestadoPersonaje::SALTANDO_OBLICUO: return "salto_oblicuo";
        case TestadoPersonaje::AGACHADO: return "agachado";
    }
    return NULL;
}

static const int TestadoPersonajeCount = 5;

enum Tdireccion{
    DERECHA,
    IZQUIERDA
};

enum Tsentido{
    ADELANTE,
    ATRAS
};

struct Tpersonaje {
    Tdimension d;
    int zIndex;
    Tdireccion orientacion;
    std::string sprites;
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
};

/**
 * Enum con todos los posibles inputs que el
 *  juego debe ser capaz de manejar.
 */
enum Tinput{
    // Teclas no utilizadas
            KEY_NADA,

    // Movimientos Basicos
            KEY_ARRIBA,
    KEY_ABAJO,
    KEY_DERECHA,
    KEY_IZQUIERDA,
    KEY_ARRIBA_DERECHA,
    KEY_ARRIBA_IZQUIERDA,

    // Golpes Basicos
            KEY_PINIA_ALTA,
    KEY_PINIA_BAJA,
    KEY_PATADA_ALTA,
    KEY_PATADA_BAJA,
    KEY_PROTECCION,
    KEY_PODER,

    // Cierre o reinicio del juego
            KEY_RESTART,
    KEY_EXIT
};

/**
 * Se define esta constante por si se llega a
 *  necesitar cambiar la extension de las imagenes
 *  que se utilizan para los sprites.
 */
static const std::string SPRITES_FORMAT = ".png";

static const float MIN_DISTANCE_FROM_BOUND = 20;

#endif //_MORTALKOMBAT_COMMON_H_

