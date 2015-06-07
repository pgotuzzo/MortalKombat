//
// Created by fran on 07/06/15.
//

#include "PantallaArcade.h"
#include "../capas/CapaInfoArcade.h"


/*
 * Crea una pantalla.
 * capas : formato de cada capa.
 * ventana : formato de ventana.
 * escenario : formato del escenario.
 * personaje : formato del personaje.
 */
PantallaArcade::PantallaArcade(vector<Tcapa> capas, Tventana ventana,
                               Tescenario escenario, vector<Tpersonaje> personajes)
        : PantallaFight(capas, ventana, escenario, personajes) { };

/**
 * Crea las capas
 *
 * \observacion Para que se puedan inicializar las capas, previamente se tuvo que inicializar los
 *              componentes de SDL (mUtils)
 */
void PantallaArcade::InicializarCapas(vector<Tcapa> capas, string personajes[2]) {
    if (mUtils == nullptr) {
        loguer->loguear("No se pueden crear las vistas de las capas sin antes inicializar SDL", Log::LOG_ERR);
        throw new exception;
    }

    for (int i = 0; i < capas.size(); i++) {
        Trect rect;
        rect.d = mDimension;
        rect.p.x = (capas[i].ancho - mDimension.w) / 2;
        rect.p.y = 0;
        Capa capa = Capa(mUtils, capas[i].dirCapa, rect, capas[i].ancho, mAnchoEscenario);
        mCapas.push_back(capa);
    }

    capaInfo = new CapaInfoArcade(mUtils, mDimension, personajes);
}

PantallaArcade::~PantallaArcade() {
    delete capaInfo;
}