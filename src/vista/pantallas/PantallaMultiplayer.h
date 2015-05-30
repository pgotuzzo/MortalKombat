#ifndef _MORTALKOMBAT_PANTALLA_H_
#define _MORTALKOMBAT_PANTALLA_H_

#include <SDL2/SDL_render.h>
#include <vector>
#include "Pantalla.h"
#include "../capas/Capa.h"
#include "../personajes/PersonajeVista.h"
#include "../capas/CapaInfo.h"

class PantallaMultiplayer : public Pantalla{
private:
    vector<Capa> mCapas;
    vector<PersonajeVista> mPersonajes;
    int zIndex;
    CapaInfo capaInfo;

    float distTope;
    float mAnchoEscenario;
    float posEscenario;

    void InicializarPersonajes(vector<Tpersonaje> personajes);
    void InicializarCapas(vector<Tcapa> capas, string personajes[2]);

    bool vibroADerecha;

public:
    /*
     * Crea una pantalla.
     * capas : formato de cada capa.
     * ventana : formato de ventana.
     * escenario : formato del escenario.
     * personaje : formato del personaje.
     */
    PantallaMultiplayer(vector<Tcapa> capas, Tventana ventana, Tescenario escenario, vector<Tpersonaje> personajes);

    /*
     * Dibuja todos los objetos en pantalla.
     */
    void print();

    /*
     * Actualiza todos los objetos de pantalla.
     * change : contiene los cambios a realizar.
     */
    void update(vector<Tcambio> changes);

    void vibrar();

    virtual ~PantallaMultiplayer();
};


#endif //_MORTALKOMBAT_PANTALLA_H_
