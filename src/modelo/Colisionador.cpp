
#include "Colisionador.h"

const float factorDeRestrocesoSinProteccion = 2;
const float factorDeRetrocesoConProteccion = 1;

//Constructor
Colisionador::Colisionador() {
    loopsReaccion = 0;
}

void Colisionador::setEscenario(float ancho) {
    anchoEsc = ancho;
}


bool Colisionador::sonProximos(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto, float delta) {
    //Aqui debe ocurrir la magia de la deteccion de las proximidades entre dos objetos
    //float anchoRectanguloMinimo = pow((primerObjeto->ancho/2)+(segundoObjeto->ancho/2)+(delta),2);
    //float distanciaPuntos = pow((primerObjeto->pos.getX() - segundoObjeto->pos.getX()),2);

    float distanciaEntrePjs;

    if(primerObjeto->pos.getX() <= segundoObjeto->pos.getX())distanciaEntrePjs = segundoObjeto->pos.getX() - primerObjeto->pos.getX() - primerObjeto->ancho;
    else distanciaEntrePjs = primerObjeto->pos.getX() - segundoObjeto->pos.getX() - segundoObjeto->ancho;

    // cout<<"Distancia entre pjs: "<<distanciaEntrePjs<<endl;

    /*float bordeIzqObjeto1 = primerObjeto->pos.getX() - primerObjeto->ancho/2;
    float bordeDerObjeto1 = primerObjeto->pos.getX() + primerObjeto->ancho/2;
    float bordeIzqObjeto2 = segundoObjeto->pos.getX() - segundoObjeto->ancho/2;
    float bordeDerObjeto2 = segundoObjeto->pos.getX() + segundoObjeto->ancho/2;*/

    float techoUno = primerObjeto->pos.getY();
    float pisoUno = techoUno + primerObjeto->getAltura();
    float techoDos = segundoObjeto->pos.getY();
    float pisoDos = techoDos + segundoObjeto->getAltura();

    //Ajusta el choque entre pj
    if ((distanciaEntrePjs <= delta)) {
        if(techoUno > pisoDos || techoDos > pisoUno )    return false;
        return true;
    }
    return  false;
}



//Recibe un vector con todos los objetos proximos, segun un cierto delta.
//Devuelve un vector vacio en el caso de que no haya objetos proximos.
//En caso contrario devuelve un vector con todos los pares de objetos proximos.

vector<ObjetoColisionable*> Colisionador::detectorDeProximidad(vector<ObjetoColisionable*> objetos, float delta ) {

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

Colisionador::~Colisionador() {

}

bool Colisionador::seVan(Personaje* PJ1, Personaje* PJ2, float delta) {
    //Aqui debe ocurrir la magia de la deteccion de las proximidades entre dos objetos
    float anchoRectanguloMinimo =(float) pow((PJ1->ancho/2)+(PJ2->ancho/2)+(delta),2);
    float distanciaPuntos = (float)pow((PJ1->pos.getX() - PJ2->pos.getX()),2);

    return distanciaPuntos <= anchoRectanguloMinimo;
}

/*
 * Devuelve true si la distancia entre los personajes es menor o igual al delta.
 * En caso contrario False.
 */
bool Colisionador::sonCercanos(Personaje *PJ1, Personaje *PJ2, float delta) {
    //Aqui debe ocurrir la magia de la deteccion de las proximidades entre dos objetos

    float distanciaEntrePjs;

    if(PJ1->pos.getX() <= PJ2->pos.getX())distanciaEntrePjs = PJ2->pos.getX() - PJ1->pos.getX() - PJ1->ancho;
    else distanciaEntrePjs = PJ1->pos.getX() - PJ2->pos.getX() - PJ2->ancho;

    return distanciaEntrePjs <= delta;
}

bool Colisionador::seProdujoColision(ObjetoColisionable* rectangulo1, ObjetoColisionable* rectangulo2){
    float bordeDerecho1,bordeIzquierdo1,techo1,piso1;
    float bordeDerecho2,bordeIzquierdo2,techo2,piso2;

    bordeDerecho1 = rectangulo1->pos.getX() + rectangulo1->ancho;
    bordeDerecho2 = rectangulo2->pos.getX() + rectangulo2->ancho;

    bordeIzquierdo1 = rectangulo1->pos.getX();
    bordeIzquierdo2 = rectangulo2->pos.getX();

    techo1 = rectangulo1->pos.getY();
    techo2 = rectangulo2->pos.getY();

    piso1 = rectangulo1->pos.getY() + rectangulo1->getAltura();
    piso2 = rectangulo2->pos.getY() + rectangulo2->getAltura();

    if ((bordeDerecho1 <= bordeIzquierdo2) || (bordeIzquierdo1 >= bordeDerecho2) || (techo1 >= piso2) || (piso1 >= techo2)) return true;
    return false;

}

//Solo cuando colisionan
float Colisionador::distanciaColisionadaenX(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2){
    float bordeDerecho1 = objeto1->pos.getX() + objeto1->ancho;
    float bordeIzquierdo2 = objeto2->pos.getX();

    return bordeDerecho1 - bordeIzquierdo2;
}



void Colisionador::solucionarColision(Personaje* PJ1, Personaje* PJ2){

    // Choques entre los cuerpos de los pjs

    //Los dos caminando en sentido contrario
    if(PJ1->sentido == true && PJ1->estado == MOV_CAMINANDO && PJ2->sentido == true && PJ2->estado == MOV_CAMINANDO){
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
    }
}

void Colisionador::solucionarColision(Personaje *PJ, TestadoPersonaje estadoViolento,Golpe *golpeOponente) {
    PJ->mePegaron(golpeOponente->danio);
    if(loopsReaccion > 0){
        estadoViolento = ACC_PINIA_ALTA_AGACHADO;
    }
    switch (estadoViolento){
        case (ACC_PINIA_ALTA):
            PJ->estado = REA_PINIA_ALTA;
            break;
        case (ACC_PINIA_BAJA):
            PJ->estado = REA_GOLPE_BAJO;
            break;
        case (ACC_PINIA_BAJA_AGACHADO):
            PJ->estado = REA_GOLPE_BAJO;
            if(PJ->direccion){
                PJ->accionesEnCurso[2]->setEstado(true,false);
            }
            else PJ->accionesEnCurso[2]->setEstado(true,true);
            // Ver logica de si se tiene que mover o algo hacia atras
            break;
        case (ACC_PINIA_ALTA_AGACHADO): // Gancho
            if(loopsReaccion == 0) loopsReaccion = 13;
            if(loopsReaccion > 7) {
                PJ->accionesEnCurso[3]->setConfiguracion(30, 60, 10);
                if (PJ->direccion) {
                    cout << "gola" << endl;
                    if (!PJ->accionesEnCurso[3]->getEstado()) {
                        PJ->accionesEnCurso[3]->setEstado(true, PJ->pos, false);
                    }
                }
                else {
                    if (!PJ->accionesEnCurso[3]->getEstado()) {
                        PJ->accionesEnCurso[3]->setEstado(true, PJ->pos, true);
                    }
                }
            }
            PJ->estado = REA_GOLPE_FUERTE;

            // Salto oblicuo hacia atras con cosas seteadas
            // Aca podria vibrar la pantalla (cuando cae)
            break;
        case (ACC_PINIA_SALTO):
            PJ->estado = REA_GOLPE_ALTO;
            // Se mueve un poco para atras
            break;
        case (ACC_PATADA_ALTA):
            PJ->estado = REA_GOLPE_ALTO;
            // Se mueve un poco para atras
            break;
        case (ACC_PATADA_BAJA):
            PJ->estado = REA_GOLPE_BAJO;
            // Se mueve un poco para atras
            break;
        case (ACC_PATADA_ALTA_ATRAS):
            PJ->estado = REA_GOLPE_FUERTE;
            // Lo tira para atras y se levanta solo. Luego estado parado
            // Aca podria vibrar la pantalla
            break;
        case (ACC_PATADA_BAJA_ATRAS):
            PJ->estado = REA_PATADA_BARRIDA;
            // Se cae pero en el lugar, se ve al chabon de frente
            // Aca podria vibrar la pantalla
            break;
        case (ACC_PATADA_AGACHADO):
            PJ->estado = REA_GOLPE_BAJO;
            // Se mueve un poco para atras
            break;
        case (ACC_PATADA_SALTO_VERTICAL):
            PJ->estado = REA_GOLPE_ALTO;
            // No estoy seguro de cual sea la reaccion
            break;
        case (ACC_PATADA_SALTO):
            PJ->estado = REA_GOLPE_FUERTE;
            // Se mueve un poco para atras
            break;

        default:
            break;
    }
    if(loopsReaccion > 0) loopsReaccion--;
    if(loopsReaccion == 0){
        PJ->estado = MOV_PARADO;
    }

    cout<<"SE ESTAN PEGANDO"<<endl;
}

void Colisionador::solucionarColision(Personaje *PJ, Poder *poderOponente) {
    if(sonProximos(PJ,poderOponente,0)){
        PJ->mePegaron(poderOponente->danio);
        cout<<"Personaje que recibio el poder"<<endl;
        PJ->pos.mostrarPar();
        cout<<"Costado Derecho del PODER: "<<poderOponente->pos.getX() + poderOponente->ancho<<endl;
        poderOponente->estadoPoder = COLISION;
        poderOponente->estado = false;
    }
//    else {
//        poderOponente->estado = true;
//        poderOponente->estadoPoder = ACTIVADO;
//    }



    /*if (PJ->direccion){
        if (distanciaColisionadaenX(PJ,poderOponente) > 0){

        }
    }
    cout<<"PODERRRR"<<endl;
    float posX;
    cout<<"COSTADOO: "<<poderOponente->pos.getX() + poderOponente->ancho/2<<endl;
    if(poderOponente->direccion){
        posX = PJ->pos.getX() - PJ->ancho/2 - poderOponente->ancho/2;
        cout<<"COSTADOO DERECHO PODER: "<<posX + poderOponente->ancho/2<<endl;
    }
    else{
        posX = PJ->pos.getX() + PJ->ancho/2 + poderOponente->ancho/2;
        cout<<"COSTADOO IZQUIERDO PODER: "<<posX - poderOponente->ancho/2<<endl;
    }


    poderOponente->pos = Posicion(posX,poderOponente->pos.getY());*/




    //Lo congela al enemigo


}