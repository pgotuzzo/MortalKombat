/**
* Este header contiene
*   constantes
*   enums
*   structs
*  que se utilizarán a lo largo
*  del juego, la idea es que tenerlas acá, ayuda a resetearlas sin tener que
*  revisar mucho código buscando donde se declaraban.
*/
#ifndef _MORTALKOMBAT_CONSTANTS_H_
#define _MORTALKOMBAT_CONSTANTS_H_

#include <string>

/**
* Posicion (type)
*/
struct Pos {
    int x;
    int y;

    Pos operator=(Pos p){
        x = p.x;
        y = p.y;
        return p;
    }

    Pos operator+(Pos p){
        return {x + p.x, y + p.y};

    }

    Pos operator-(Pos p){
        return {x - p.x, y - p.y};
    }

    bool operator==(Pos p){
        if ( (p.x == x) && (p.y == y) )
            return true;
        return false;
    }
};

//rutas generales
static const std::string IMAGES_PATH =  "../resources/img/";
static const std::string SPRITES_PATH =  "../resources/sprites/";

//tamaño de la pantalla en pixeles
static const int SCREEN_PX_WIDHT = 1024;
static const int SCREEN_PX_HEIGHT = 768;

//tamaño de la pantalla en unidades logicas
static const int SCREEN_WIDHT = 1000;
static const int SCREEN_HEIGHT = 500;

//Personaje

//Escenario (z != 0)
//capa
static const std::string WALLPAPER = IMAGES_PATH + "test_wallpaper.jpeg";

//elementos del fondo de pantalla
static const std::string TREE = IMAGES_PATH + "tree.png";

#endif //_MORTALKOMBAT_CONSTANTS_H_
