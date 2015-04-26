
#include "DetectorDeColisiones.h"


//Constructor
    DetectorDeColisiones::DetectorDeColisiones() {

    }

bool DetectorDeColisiones::sonProximos(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto, float delta) {
    //Aqui debe ocurrir la magia de la deteccion de las proximidades entre dos objetos
    //TODO: INSERTE AQUI LA MAGIA
    return false;
}



//Recibe un vector con todos los objetos proximos, segun un cierto delta.
//Devuelve un vector vacio en el caso de que no haya objetos proximos.
//En caso contrario devuelve un vector con todos los pares de objetos proximos.

vector<ObjetoColisionable*> DetectorDeColisiones::detectorDeProximidad(vector<ObjetoColisionable*> objetos, float delta ){
    //pair <ObjetoColisionable,ObjetoColisionable> proximos;
    //Creo el vector de pares de objetos proximos que voy a devolver
    vector<ObjetoColisionable*> obejtosProximos;
    int i = 0;
    //Recorro todos los objetos preguntando si uno esta mas cerca que delta de otro
    for(i;i<=(objetos.max_size()-1);i++){
        int j = i+1;
        //Comparo la vector en i, con el resto de las cosas en el vector
        for(j;j<=(objetos.max_size()- 1- i);j++){

            if(sonProximos(objetos[i],objetos[j],delta)){
            //Como los objetos son proximos lo guardo en el vector que devuelvo
            //proximos = make_pair(objetos[i],objetos[j]);
            //obejtosProximos.push_back(proximos);
            obejtosProximos.push_back(objetos[i]);
            obejtosProximos.push_back(objetos[j]);
            }
        }
    }
    return obejtosProximos;
}


    DetectorDeColisiones::~DetectorDeColisiones() {

    }
