
#include "DetectorDeColisiones.h"


//Constructor
DetectorDeColisiones::DetectorDeColisiones() {

}

bool DetectorDeColisiones::sonProximos(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto, float delta) {
    //Aqui debe ocurrir la magia de la deteccion de las proximidades entre dos objetos
    float anchoRectanguloMinimo = pow((primerObjeto->ancho/2)+(segundoObjeto->ancho/2)+(delta),2);
    float distanciaPuntos = pow((primerObjeto->pos.getX() - segundoObjeto->pos.getX()),2);

    float distancia1 = pow(primerObjeto->pos.getY()-segundoObjeto->pos.getY(),2);
    float distancia2 = pow((primerObjeto->pos.getY()+primerObjeto->altura)-(segundoObjeto->pos.getY()+segundoObjeto->altura),2);
    if((distancia1 <= segundoObjeto->altura)||(distancia2 <= primerObjeto->altura)){
        if (distanciaPuntos <= anchoRectanguloMinimo-10) return true;
        return false;
    }
    return  false;
}



//Recibe un vector con todos los objetos proximos, segun un cierto delta.
//Devuelve un vector vacio en el caso de que no haya objetos proximos.
//En caso contrario devuelve un vector con todos los pares de objetos proximos.

vector<ObjetoColisionable*> DetectorDeColisiones::detectorDeProximidad(vector<ObjetoColisionable*> objetos, float delta ) {

    //Creo el vector de pares de objetos proximos que voy a devolver
    vector<ObjetoColisionable *> objetosProximos;

    //Caso en que no haya objetos o halla un solo objeto
    if (objetos.empty() || objetos.size() == 1) return objetosProximos;

    int i = 0;
    //Recorro todos los objetos preguntando si uno esta mas cerca que delta
    for (i; i < objetos.size() - 1; i++) {
        for (int j = i + 1; j < objetos.size(); j++) {
            if (sonProximos(objetos[i], objetos[j], delta)) {
                objetosProximos.push_back(objetos[i]);
                objetosProximos.push_back(objetos[j]);
            }
        }
    }
    return objetosProximos;
}

//TODO:HACER QUE LA SALIDA DE LA FUNCION DE ARRIBA SEA LA DE UN VECTOR DE PAIRS DE PUNTEROS A OBJETOS COLISIONABLES
// quedaria mas lindo, tendriamos un vector de pares que estan tan proximos como un cierto delta
// habria que modificar varias cosas en otros lados

DetectorDeColisiones::~DetectorDeColisiones() {

}

bool DetectorDeColisiones::seVan(Personaje* PJ1, Personaje* PJ2, float delta) {
    //Aqui debe ocurrir la magia de la deteccion de las proximidades entre dos objetos
    float anchoRectanguloMinimo =(float) pow((PJ1->ancho/2)+(PJ2->ancho/2)+(delta),2);
    float distanciaPuntos = (float)pow((PJ1->pos.getX() - PJ2->pos.getX()),2);

    return distanciaPuntos <= anchoRectanguloMinimo;
}

bool DetectorDeColisiones::detectarLejania(Personaje* PJ1, Personaje* PJ2, float delta) {
    //Aqui debe ocurrir la magia de la deteccion de las proximidades entre dos objetos
    float anchoRectanguloMinimo =(float) pow(delta,2);

    float distanciaPuntos = (float)pow((PJ1->pos.getX() - PJ2->pos.getX()),2);

    return distanciaPuntos <= anchoRectanguloMinimo;
}
