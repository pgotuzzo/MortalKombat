#ifndef MORTALKOMBAT_MENUPLAYERSELECTION_H
#define MORTALKOMBAT_MENUPLAYERSELECTION_H

#include <array>
#include "../../utils/Common.h"
#include "../../utils/PersonajeUtils.h"
#include "../../Musica.h"

class MenuPlayerSelection {

private:
    static const int ROWS = 3;
    static const int COLUMNS = 4;
    /**
     *  Este sera el menu de selección, gráficamente.
     *  //==========================\\
     *  || SZ  || SZg || SZr || SZy ||
     *  ||=====||=====||=====||=====||
     *  || ER  || ERb || ERg || ERy ||
     *  ||=====||=====||=====||=====||
     *  || LK  || LKb || LKg || LKy ||
     *  \\==========================//
     */

    Posicion mSelection[2];
    bool seleccionandoConMouse[2];

    void updateSelection(TinputMovimiento movimiento, int jugador);

public:
    MenuPlayerSelection();
    EtipoPersonaje getType(Posicion p);

    bool mSelectionConfirmed[2];

    Musica* movimientoSelec;
    Musica* seleccion;

    ~MenuPlayerSelection();

    EtipoPersonaje personajesElegidos[2];

    vector<Posicion> update(vector<Tinput> inputs);
    vector<Posicion> update(vector<Tinput> inputs,Posicion coordenadasMouse,vector<Trect> players);

    vector<Posicion> updateConAleatorio(vector<Tinput> inputs);
    vector<Posicion> updateConAleatorio(vector<Tinput> inputs,Posicion coordenadasMouse,vector<Trect> players);


    void actualizarSeleccion(Posicion coordenadasMouse,vector<Trect> players,int jugador);

    bool dentroDeUnPlayer(Posicion posMouse,Trect player,int jugador);

    bool selectionComplete();


};


#endif //MORTALKOMBAT_MENUPLAYERSELECTION_H
