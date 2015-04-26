
#include "DetectorDeColisiones.h"


//Constructor
DetectorDeColisiones::DetectorDeColisiones() {

}

bool DetectorDeColisiones::sonProximos(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto, float delta) {
    //Aqui debe ocurrir la magia de la deteccion de las proximidades entre dos objetos
    //TODO: INSERTE AQUI LA MAGIA
    float anchoRectanguloMinimo = pow((primerObjeto->ancho/2)+(segundoObjeto->ancho/2)+(delta),2);
    float distanciaPuntos = pow((primerObjeto->pos.getX() - segundoObjeto->pos.getX()),2);
    if (distanciaPuntos <= anchoRectanguloMinimo) return true;
    return false;

}



//Recibe un vector con todos los objetos proximos, segun un cierto delta.
//Devuelve un vector vacio en el caso de que no haya objetos proximos.
//En caso contrario devuelve un vector con todos los pares de objetos proximos.

vector<ObjetoColisionable*> DetectorDeColisiones::detectorDeProximidad(vector<ObjetoColisionable*> objetos, float delta ){

    //Creo el vector de pares de objetos proximos que voy a devolver
    vector<ObjetoColisionable*> obejtosProximos;

    //Caso en que no haya objetos o halla un solo objeto
    if (objetos.empty()||objetos.size() == 1) return obejtosProximos;

    int i = 0;
    //Recorro todos los objetos preguntando si uno esta mas cerca que delta de otro
    for(i;i<=(objetos.size()-2);i++){
        int j = i+1;
        //Comparo la vector en i, con el resto de las cosas en el vector
        for(j;j<=(objetos.size()- 1- i);j++){

            if(sonProximos(objetos[i],objetos[j],delta)){
                obejtosProximos.push_back(objetos[i]);
                obejtosProximos.push_back(objetos[j]);
            }
        }
    }
    return obejtosProximos;
}


DetectorDeColisiones::~DetectorDeColisiones() {

}
