#ifndef MORTALKOMBAT_PANTALLAPRACTICE_H
#define MORTALKOMBAT_PANTALLAPRACTICE_H


#include "PantallaFight.h"

class PantallaPractice : public PantallaFight {
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
    PantallaPractice(vector<Tcapa> capas, Tventana ventana, Tescenario escenario, vector<Tpersonaje> personajes);

    ~PantallaPractice();
};


#endif //MORTALKOMBAT_PANTALLAPRACTICE_H
