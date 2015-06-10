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
                    aux.movimiento = meAcerco(rectangulo,miRect);
                    if(r<35 && pegado){
                        aux.accion=TinputAccion::KEY_PATADA_BAJA;
                        aux.movimiento = dirPatada(rectangulo , miRect);
                    } else if( 35 <= r && r < 60 && pegado ){
                        aux.accion=TinputAccion::KEY_PATADA_ALTA;
                        aux.movimiento = dirPatada(rectangulo , miRect);
                    }/*if( 60 <= r && r<80 && pegado ){
                        aux.accion=TinputAccion::KEY_PINIA_BAJA;
                        aux.movimiento = dirPatada(rectangulo , miRect);
                    }*/

                }else{
                    aux.accion = TinputAccion::KEY_PODER;
                }
                return aux;
            }
            case MOV_CAMINANDO:{
                if(r<20){
                    if((rectangulo.p.x-miRect.p.x)>0 &&(rectangulo.p.x-miRect.p.x)<120 && !acercandose ){
                        aux.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        //aux.accion=TinputAccion::KEY_PINIA_ALTA;
                    }else if((miRect.p.x-rectangulo.p.x)>0 &&(miRect.p.x-rectangulo.p.x)<120 && !acercandose ){
                        aux.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                        //aux.accion=TinputAccion::KEY_PATADA_ALTA;
                        //si no esta a su alcance de golpe seguro, se acerca saltando oblicuo
                    }else if((rectangulo.p.x-miRect.p.x)>100 ){
                        aux.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        acercandose = true;
                    }else if((miRect.p.x-rectangulo.p.x)>100 ){
                        aux.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                        acercandose = true;
                    } else
                        acercandose = false;
                }
                else if(r < 85){
                    aux.accion=TinputAccion::KEY_PODER;
                }
                return aux;
            }
            case ACC_PINIA_ALTA:
                case ACC_PINIA_BAJA:{
                    if((rectangulo.p.x-miRect.p.x)==rectangulo.d.w ||(miRect.p.x-rectangulo.p.x)==miRect.d.w){
                        if( r < 20)
                            aux.accion=TinputAccion::KEY_PROTECCION;

                        else if( 20 <= r && r < 70){
                            if((rectangulo.p.x-miRect.p.x)>=miRect.d.w)
                                aux.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;
                            else if((rectangulo.p.x-miRect.p.x)<= -rectangulo.d.w)
                                aux.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                        } else if(50 <= r && r <90){
                            aux.accion=TinputAccion::KEY_PATADA_BAJA;
                            aux.movimiento = dirPatada( rectangulo, miRect );
                        }
                    }
                    return aux;
                }
            case ACC_PODER:{
                if(r<30){
                    if((rectangulo.p.x-miRect.p.x)>=DIST_MIN_PODER ||(miRect.p.x-rectangulo.p.x)>=DIST_MIN_PODER)
                        aux.movimiento=TinputMovimiento::KEY_ARRIBA;
                }else if(r<70){

                    if((rectangulo.p.x-miRect.p.x)>miRect.d.w)
                        aux.movimiento=TinputMovimiento::KEY_ARRIBA_DERECHA;
                    else if((rectangulo.p.x-miRect.p.x)<-rectangulo.d.w)
                        aux.movimiento=TinputMovimiento::KEY_ARRIBA_IZQUIERDA;

                    aux.accion=TinputAccion::KEY_PATADA_ALTA;
                }else
                    aux.accion=TinputAccion::KEY_PROTECCION;

                return aux;
            }
            case ACC_PINIA_SALTO:
                case ACC_PATADA_SALTO:{
                    //if(r<45){
                    if( ( rectangulo.p.x - miRect.p.x ) > -20 && ( rectangulo.p.x - miRect.p.x ) < 120 ){
                        aux.accion=TinputAccion::KEY_PROTECCION;
                    }

                    return aux;
                }

            case REA_MAREADO:{
                if(r < 98 ){
                    aux.accion=TinputAccion::KEY_PODER;
                }
                return aux;
            }

            case MOV_AGACHADO: {
                aux.movimiento = meAcerco(rectangulo,miRect);
                if(r<35 && pegado){
                    aux.accion=TinputAccion::KEY_PATADA_BAJA;
                    aux.movimiento = dirPatada(rectangulo , miRect);
                } else if( 35 <= r && r < 60 && pegado ){
                    aux.accion=TinputAccion::KEY_PATADA_ALTA;
                    aux.movimiento = dirPatada(rectangulo , miRect);
                }

                return aux;
            };

            case REA_CONGELADO:{

                aux.movimiento = meAcerco(rectangulo,miRect);

                if(r<50 && pegado){
                    aux.accion=TinputAccion::KEY_PATADA_BAJA;
                    if((miRect.p.x-rectangulo.p.x)==miRect.d.w)
                        aux.movimiento=TinputMovimiento::KEY_DERECHA;
                    else
                        aux.movimiento=TinputMovimiento::KEY_IZQUIERDA;
                }else{
                    aux.accion=TinputAccion::KEY_PINIA_ALTA;
                    aux.movimiento=TinputMovimiento::KEY_ABAJO;
                }
            }

        }
        default:

            return aux;


    }


}

TinputMovimiento InteligenciaArtificial::dirPatada(Trect rectangulo, Trect miRect){

    Tinput aux;
    if((miRect.p.x-rectangulo.p.x)==miRect.d.w)
        aux.movimiento=TinputMovimiento::KEY_DERECHA;
    else
        aux.movimiento=TinputMovimiento::KEY_IZQUIERDA;

    return aux.movimiento;
}

TinputMovimiento InteligenciaArtificial::meAcerco(Trect rectangulo, Trect miRect){
    Tinput aux;
    pegado=false;

    if((rectangulo.p.x-miRect.p.x)>miRect.d.w)
        aux.movimiento=TinputMovimiento::KEY_DERECHA;
    else if((rectangulo.p.x-miRect.p.x)<-rectangulo.d.w)
        aux.movimiento=TinputMovimiento::KEY_IZQUIERDA;
    else
        pegado=true;

    return aux.movimiento;
}