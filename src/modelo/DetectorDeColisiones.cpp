

#include "DetectorDeColisiones.h"




void DetectorDeColisiones::resolverColisiones(Personaje *personaje1, Personaje *personaje2) {

    colisionar(personaje1,personaje2);
    // si personaje1 esta tirando el golpe
    // colisionar(personaje2,personaje1->llevarAcabo.golpe.estado)
    // si personaje2 esta tirando el golpe
    // colisionar(personaje1,personaje2->llevarAcabo.golpe.estado)
    if(personaje1->poder->estado == ACTIVADO && personaje2->poder->estado == ACTIVADO){
        colisionar(personaje1->poder,personaje2->poder);
        colisionar(personaje1,personaje2->poder);
        colisionar(personaje2,personaje1->poder);
    }
    else{
        if(personaje1->poder->estado == ACTIVADO){
            colisionar(personaje2,personaje1->poder);
        }
        if(personaje2->poder->estado == ACTIVADO){
            colisionar(personaje1,personaje2->poder);
        }

    }

}



// Detecta si dos objetos colisionaron (parte de uno dentro de otro)
// Si objeto1 u objeto2 son NULL devuelvo false
bool DetectorDeColisiones::detectarColision(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2) {

    if(!objeto1 || !objeto2) return false;

    float bordeDerecho1,bordeIzquierdo1,techo1,piso1;
    float bordeDerecho2,bordeIzquierdo2,techo2,piso2;

    Trect rectangulo1 = objeto1->getRectangulo();
    Trect rectangulo2 = objeto2->getRectangulo();

    bordeDerecho1 = rectangulo1.p.getX() + rectangulo1.d.w;
    bordeDerecho2 = rectangulo2.p.getX() + rectangulo2.d.w;

    bordeIzquierdo1 = rectangulo1.p.getX();
    bordeIzquierdo2 = rectangulo2.p.getX();

    techo1 = rectangulo1.p.getY();
    techo2 = rectangulo2.p.getY();

    piso1 = rectangulo1.p.getY() + rectangulo1.d.h;
    piso2 = rectangulo2.p.getY() + rectangulo2.d.h;

    if (!((bordeDerecho1 < bordeIzquierdo2) || (bordeIzquierdo1 > bordeDerecho2) || (techo1 < piso2) || (piso1 > techo2))) {
        return true;
    }
    return false;
}

// Calcula la distancia del borde derecho del primer objeto con el borde izquierdo del segundo.
// Se debe utilizar cuando se sabe que los objetos colisionaron. De esta manera se sabria que distancia en x colisionaron.
float DetectorDeColisiones::distanciaColisionadaenX(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2){

    float bordeDerecho1 = objeto1->getRectangulo().p.getX() + objeto1->getRectangulo().d.w;
    float bordeIzquierdo2 = objeto2->getRectangulo().p.getX();

    return bordeDerecho1 - bordeIzquierdo2;
}

// Verifica que se colisione en Y. No me importe en que X esten los objetos.
// Devuelve true si colisionan. False en caso contrario
bool DetectorDeColisiones::detectarColisionenY(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2) {

    if(!objeto1 || !objeto2) return false; // Si algun objeto es NULL, hacemos de cuenta que no colisionan.

    Trect rectangulo1 = objeto1->getRectangulo();
    Trect rectangulo2 = objeto2->getRectangulo();
    float techo1,piso1;
    float techo2,piso2;

    techo1 = rectangulo1.p.getY();
    techo2 = rectangulo2.p.getY();

    piso1 = rectangulo1.p.getY() + rectangulo1.d.h;
    piso2 = rectangulo2.p.getY() + rectangulo2.d.h;

    if(!((techo1 < piso2) || (piso1 > techo2))) return true;
    return false;
}


// Si colisionan los dos personajes, se resuelven sus colisiones.
// Se resuelve la colision de un personaje con respecto a otro y viceversa.
void DetectorDeColisiones::colisionar(Personaje *personaje1, Personaje *personaje2) {

    if(detectarColision(personaje1,personaje2)){
        resolverColision(personaje1,personaje2);
        resolverColision(personaje2,personaje1);
    }
}

// si estan colisionando golpe y personaje, resuelve su colision.
void DetectorDeColisiones::colisionar(Personaje *personaje1, Golpe* golpe) {

    if(detectarColision(personaje1,golpe)){
        resolverColision(personaje1,golpe);
    }
}

// Si estan colisionando el personaje con el poder se la resuelve a la misma.
// El estado del poder se setea a COLISION (se desactiva en el siguiente loop).
void DetectorDeColisiones::colisionar(Personaje *personaje1, Poder *poder) {

    if(detectarColision(personaje1,poder) || hayEfectoTunel(personaje1,poder)){
        resolverColision(personaje1,poder);
        poder->estado = COLISION;
    }
}

// Si dos poderes estan colisionando o se hace el efecto tunel entonces se resuelva la misma.
// Se setea a los dos poderes en COLISION (se desactiva en el siguiente loop).
void DetectorDeColisiones::colisionar(Poder *poder1, Poder *poder2) {

    if(detectarColision(poder1,poder2) || hayEfectoTunel(poder1,poder2)){
        resolverColision(poder1,poder2);
        poder1->estado = COLISION;
        poder2->estado = COLISION;
    }

}


// Resuelve las colisiones entre los dos personajes.
// Dicha resolucion se tiene que hacer ida y vuelta para los personajes, debido a que todas las comprobaciones
// se hacen una sola vez
void DetectorDeColisiones::resolverColision(Personaje *PJ1, Personaje *PJ2) {

    //Los dos caminando en sentido contrario
   /* if(PJ1->sentido == true && PJ1->estado == MOV_CAMINANDO && PJ2->sentido == true && PJ2->estado == MOV_CAMINANDO){
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0) {
            PJ1->pos.setX(PJ1->pos.getX() - 1);
            PJ2->pos.setX(PJ2->pos.getX() + 1);
        } else {
            PJ1->pos.setX(PJ1->pos.getX() + 1);
            PJ2->pos.setX(PJ2->pos.getX() - 1);
        };
    }
    else{
        Tinput inputDerecha;
        inputDerecha.movimiento = TinputMovimiento::KEY_DERECHA;
        inputDerecha.accion = TinputAccion::KEY_NADA;

        Tinput inputIzquierda;
        inputIzquierda.movimiento = TinputMovimiento::KEY_IZQUIERDA;
        inputDerecha.accion = TinputAccion::KEY_NADA;

        Tinput inputAgachado;
        inputAgachado.movimiento = TinputMovimiento::KEY_ABAJO;
        inputAgachado.accion = TinputAccion::KEY_NADA;

        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0 ) {
            if(PJ1->estado == MOV_CAMINANDO && PJ1->sentido == true){
                if(PJ2->estado == MOV_PARADO) {
                    PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                    PJ2->realizarAccion(inputDerecha,anchoEsc);
                    PJ2->estado = MOV_PARADO;
                    PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                    PJ2->accionesEnCurso[2]->setAnchoDePasoDefault();
                }
                else if(PJ2->estado == MOV_AGACHADO) {
                    PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                    PJ2->realizarAccion(inputDerecha, anchoEsc);
                    PJ2->realizarAccion(inputAgachado,anchoEsc);
                    PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                    PJ2->accionesEnCurso[2]->setAnchoDePasoDefault();
                }
                else if (PJ2->estado == ACC_PROTECCION) {
                    PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                    PJ2->realizarAccion(inputDerecha, anchoEsc);
                    PJ2->estado = ACC_PROTECCION;
                    PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                    PJ2->accionesEnCurso[2]->setAnchoDePasoDefault();
                }
                else if (PJ2->estado == ACC_PROTECCION_AGACHADO) {
                    PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                    PJ2->realizarAccion(inputDerecha, anchoEsc);
                    PJ2->estado = ACC_PROTECCION_AGACHADO;
                    PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                    PJ2->accionesEnCurso[2]->setAnchoDePasoDefault();
                }
            }
            else if(PJ2->estado == MOV_CAMINANDO && PJ2->sentido == true){
                if (PJ1->estado == MOV_PARADO){
                    PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                    PJ1->realizarAccion(inputIzquierda, anchoEsc);
                    PJ1->estado = MOV_PARADO;
                    PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                    PJ1->accionesEnCurso[2]->setAnchoDePasoDefault();
                }
                else if (PJ1->estado == MOV_AGACHADO){
                    PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                    PJ1->realizarAccion(inputIzquierda, anchoEsc);
                    PJ1->realizarAccion(inputAgachado,anchoEsc);
                    PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                    PJ1->accionesEnCurso[2]->setAnchoDePasoDefault();
                }
                else if (PJ1->estado == ACC_PROTECCION) {
                    PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                    //PJ1->realizarAccion(inputIzquierda, anchoEsc);
                    PJ1->caminar(false);
                    PJ1->estado = ACC_PROTECCION;
                    PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                    PJ1->accionesEnCurso[2]->setAnchoDePasoDefault();
                }
                else if (PJ1->estado == ACC_PROTECCION_AGACHADO) {
                    PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                    //PJ1->realizarAccion(inputIzquierda, anchoEsc);
                    PJ1->caminar(false);
                    PJ1->estado = ACC_PROTECCION_AGACHADO;
                    PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                    PJ1->accionesEnCurso[2]->setAnchoDePasoDefault();
                }
            }
        }

    }


    //Colision entre un pj saltando oblicuamente y otro que esta parado (que no se superpongan luego dle salto)
    if(PJ1->estado == MOV_SALTANDO_OBLICUO && PJ1->sentido == true && (PJ2->estado == MOV_PARADO || PJ2->estado ==
                                                                                                    MOV_AGACHADO) && seProdujoColision(PJ1,PJ2)){
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0) {
            PJ2->pos.setX(PJ2->pos.getX() + distanciaColisionadaenX(PJ1,PJ2));
        }
    }

    //Colision entre un pj saltando oblicuamente y otro caminando
    if(PJ1->estado == MOV_SALTANDO_OBLICUO && PJ1->sentido == true && PJ2->estado == MOV_CAMINANDO && seProdujoColision(PJ1,PJ2)){
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0) {
            PJ2->pos.setX(PJ2->pos.getX() + distanciaColisionadaenX(PJ1,PJ2));
        }
    }

    //Colision entre un pj Saltando vertical y otro caminando
    if(PJ1->estado == MOV_SALTANDO_VERTICAL && PJ2->estado == MOV_CAMINANDO && PJ2->sentido == true && seProdujoColision(PJ1,PJ2)){
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0) {
            PJ2->pos.setX(PJ2->pos.getX() + distanciaColisionadaenX(PJ1,PJ2));
        } else {
            PJ2->pos.setX(PJ2->pos.getX() - distanciaColisionadaenX(PJ2,PJ1));
        };
    }

    // Colision entre un pj saltando vertical y otro saltando oblicuamente
    if(PJ1->estado == MOV_SALTANDO_VERTICAL && PJ2->estado == MOV_SALTANDO_OBLICUO && PJ2->sentido == true && seProdujoColision(PJ1,PJ2)){
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0) {
            PJ2->enCaida = true;
            PJ2->pos.setX(PJ2->pos.getX() + distanciaColisionadaenX(PJ1,PJ2));
        } else {
            PJ2->enCaida = true;
            PJ2->pos.setX(PJ2->pos.getX() - distanciaColisionadaenX(PJ2,PJ1));
        };
    }

    if(seProdujoColision(PJ1,PJ2)) {
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0) {
            if(PJ2->pos.getX() >= anchoEsc - PJ2->ancho && PJ1->pos.getX() >= anchoEsc - PJ2->ancho - PJ1->ancho){
                PJ2->pos.setX(anchoEsc - PJ2->ancho);
                PJ1->pos.setX(anchoEsc - PJ2->ancho - PJ1->ancho);
            }
            else PJ2->pos.setX(PJ2->pos.getX() + distanciaColisionadaenX(PJ1, PJ2));
        }
    }*/
}

// Se resuelve la colision entre el personaje y el poder.
// Se coloca al poder en el costado del personaje.
void DetectorDeColisiones::resolverColision(Personaje* PJ, Poder* poder) {
    Trect rectanguloPJ = PJ->rectanguloPj;
    Trect rectanguloPoder = poder->rectanguloPoder;
    // Sacar danio
    if(rectanguloPJ.p.getX() < poder->rectanguloPoder.p.getX()) poder->rectanguloPoder.p.setX(rectanguloPJ.p.getX() + rectanguloPJ.d.w);
    else rectanguloPoder.p.setX(rectanguloPJ.p.getX() - rectanguloPoder.d.w);

}

// Se resuelve la colision entre dos poderes.
// Se coloca al poder1 en el costado del poder2.
void DetectorDeColisiones::resolverColision(Poder *poder1, Poder *poder2) {
    Trect rectanguloPoder1 = poder1->rectanguloPoder;
    Trect rectanguloPoder2 = poder2->rectanguloPoder;
    if(rectanguloPoder1.p.getX() < rectanguloPoder2.p.getX()) rectanguloPoder2.p.setX(rectanguloPoder1.p.getX() + rectanguloPoder1.d.w);
    else rectanguloPoder1.p.setX(rectanguloPoder1.p.getX() - rectanguloPoder2.d.w);
}

// Se verifica si hay efecto tunel. Para esto verifica si estan a la misma altura los objetos
// y verifica que se hayan pasado
bool DetectorDeColisiones::hayEfectoTunel(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2) {
    if(detectarColisionenY(objeto1,objeto2)) {
        switch(objeto1->getRectangulo().p.getX() < objeto2->getRectangulo().p.getX()){
            case(true):
                if (0<distanciaColisionadaenX(objeto2, objeto1)<=velocidadDelPoder) {
                    return true;
                }
                break;
            default:
                if ( 0<distanciaColisionadaenX(objeto1, objeto2)<=velocidadDelPoder) {
                    return true;
                }
                break;
        }
    }
    return false;
}


// resuelve la colision entre golpe y personaje
void DetectorDeColisiones::resolverColision(Personaje *PJ,Golpe *golpe) {
    // PJ->reducirVida(golpe->danio);
    // PJ->estado = golpe->efectoSobreOponente;
    // Ajustar la superposicion del golpe con el personaje si es necesario
}

