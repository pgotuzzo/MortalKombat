#include "InteligenciaArtificial.h"


const float DIST_SALTO_OBLICUO=100;
const float DIST_MIN_PODER=130;
InteligenciaArtificial::InteligenciaArtificial() {
    // TODO Auto-generated constructor stub

}

InteligenciaArtificial::~InteligenciaArtificial() {
    // TODO Auto-generated destructor stub
}

Tinput InteligenciaArtificial::responderDeacuerdoa(TestadoPersonaje estadoJ,Trect rectangulo,Trect miRect){
    Tinput aux;
    srand(std::time(0));
    int r=rand()%100;
    switch (estadoJ){
        case MOV_SALTANDO_VERTICAL:{
            if((rectangulo.p.x-miRect.p.x)==rectangulo.d.w ||(miRect.p.x-rectangulo.p.x)==miRect.d.w){
                aux.accion=TinputAccion::KEY_PINIA_ALTA;
                aux.movimiento=TinputMovimiento::KEY_ABAJO;
                return aux;
            }
            case MOV_PARADO:{
                if(r<80){
                    if((rectangulo.p.x-miRect.p.x)>miRect.d.w)
                        aux.movimiento=TinputMovimiento::KEY_DERECHA;
                    else if((rectangulo.p.x-miRect.p.x)<-rectangulo.d.w)
                        aux.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                    else if(r<25){
                        aux.accion=TinputAccion::KEY_PATADA_BAJA;
                        if((miRect.p.x-rectangulo.p.x)==miRect.d.w)
                            aux.movimiento=TinputMovimiento::KEY_DERECHA;
                        else
                            aux.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                    }
                }else
                    aux.accion=TinputAccion::KEY_PODER;

                return aux;
            }
            case MOV_CAMINANDO:{
                if(r<30)
                if((rectangulo.p.x-miRect.p.x)>0 &&(rectangulo.p.x-miRect.p.x)<100 ){
                    aux.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                    aux.accion=TinputAccion::KEY_PINIA_ALTA;
                }else {
                    aux.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                    aux.accion=TinputAccion::KEY_PATADA_ALTA;
                }
                else if(r<70){
                    aux.accion=TinputAccion::KEY_PODER;
                }
                return aux;
            }
            case ACC_PINIA_ALTA:
                case ACC_PINIA_BAJA:{
                    if((rectangulo.p.x-miRect.p.x)==rectangulo.d.w ||(miRect.p.x-rectangulo.p.x)==miRect.d.w){
                        aux.accion=TinputAccion::KEY_PROTECCION;
                    }
                    return aux;
                }
            case ACC_PODER:{
                if(r<30){
                    if((rectangulo.p.x-miRect.p.x)>=DIST_MIN_PODER ||(miRect.p.x-rectangulo.p.x)>=DIST_MIN_PODER)
                        aux.movimiento=TinputMovimiento::KEY_ARRIBA;
                }else if(r<65)
                    aux.accion=TinputAccion::KEY_PODER;
                else if(r<85){
                    if((rectangulo.p.x-miRect.p.x)>miRect.d.w)
                        aux.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                    else if((rectangulo.p.x-miRect.p.x)<-rectangulo.d.w)
                        aux.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                    aux.accion=TinputAccion::KEY_PATADA_ALTA;
                }else
                    aux.accion=TinputAccion::KEY_PROTECCION;

                return aux;
            }
            case ACC_PATADA_SALTO:{
                //if(r<45){
                if((rectangulo.p.x-miRect.p.x)>0 &&(rectangulo.p.x-miRect.p.x)<100 || proteccion ){
                    aux.accion=TinputAccion::KEY_PROTECCION;


                }

                return aux;
            }

        }
        default:

            return aux;


    }


}
