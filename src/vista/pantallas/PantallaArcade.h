//
// Created by fran on 07/06/15.
//

#ifndef MORTALKOMBAT_PANTALLAARCADE_H
#define MORTALKOMBAT_PANTALLAARCADE_H


#include "PantallaFight.h"

class PantallaArcade : public PantallaFight {
public:

    /**
     * Crea las capas
     *
     * \observacion Para que se puedan inicializar las capas, previamente se tuvo que inicializar los
     *              componentes de SDL (mUtils)
     */
    void InicializarCapas(vector<Tcapa> capas, string personajes[2]);


    /*
     * Crea una pantalla.
     * capas : formato de cada capa.
     * ventana : formato de ventana.
     * escenario : formato del escenario.
     * personaje : formato del personaje.
     */
    PantallaArcade(vector<Tcapa> capas, Tventana ventana, Tescenario escenario, vector<Tpersonaje> personajes);


};


#endif //MORTALKOMBAT_PANTALLAARCADE_H
