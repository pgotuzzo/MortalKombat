
#include "Colisionador.h"

const float factorDeRestrocesoSinProteccion = 2;
const float factorDeRetrocesoConProteccion = 1;

//Constructor
Colisionador::Colisionador() {
}

void Colisionador::setEscenario(float ancho) {
    anchoEsc = ancho;
}


bool Colisionador::sonProximos(ObjetoColisionable* primerObjeto, ObjetoColisionable* segundoObjeto, float delta) {
    //Aqui debe ocurrir la magia de la deteccion de las proximidades entre dos objetos
    float anchoRectanguloMinimo = pow((primerObjeto->ancho/2)+(segundoObjeto->ancho/2)+(delta),2);
    float distanciaPuntos = pow((primerObjeto->pos.getX() - segundoObjeto->pos.getX()),2);



    /*float bordeIzqObjeto1 = primerObjeto->pos.getX() - primerObjeto->ancho/2;
    float bordeDerObjeto1 = primerObjeto->pos.getX() + primerObjeto->ancho/2;
    float bordeIzqObjeto2 = segundoObjeto->pos.getX() - segundoObjeto->ancho/2;
    float bordeDerObjeto2 = segundoObjeto->pos.getX() + segundoObjeto->ancho/2;*/

    float techoUno = primerObjeto->pos.getY();
    float pisoUno = techoUno + primerObjeto->getAltura();
    float techoDos = segundoObjeto->pos.getY();
    float pisoDos = techoDos + segundoObjeto->getAltura();

    //Ajusta el choque entre pj
    if ((distanciaPuntos <= anchoRectanguloMinimo)) {
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

bool Colisionador::detectarLejania(Personaje* PJ1, Personaje* PJ2, float delta) {
    //Aqui debe ocurrir la magia de la deteccion de las proximidades entre dos objetos
    float anchoRectanguloMinimo =(float) pow(delta,2);

    float distanciaPuntos = (float)pow((PJ1->pos.getX() - PJ2->pos.getX()),2);

    return distanciaPuntos <= anchoRectanguloMinimo;
}

bool Colisionador::seProdujoColision(ObjetoColisionable* rectangulo1, ObjetoColisionable* rectangulo2){
    float bordeDerecho1,bordeIzquierdo1,techo1,piso1;
    float bordeDerecho2,bordeIzquierdo2,techo2,piso2;

    bordeDerecho1 = rectangulo1->pos.getX() + rectangulo1->ancho / 2;
    bordeDerecho2 = rectangulo2->pos.getX() + rectangulo2->ancho / 2;

    bordeIzquierdo1 = rectangulo1->pos.getX() - rectangulo1->ancho / 2;
    bordeIzquierdo2 = rectangulo2->pos.getX() - rectangulo2->ancho / 2;

    techo1 = rectangulo1->pos.getY();
    techo2 = rectangulo2->pos.getY();

    piso1 = rectangulo1->pos.getY() + rectangulo1->getAltura();
    piso2 = rectangulo2->pos.getY() + rectangulo2->getAltura();

    if ((bordeDerecho1 < bordeIzquierdo2) || (bordeIzquierdo1 > bordeDerecho2) || (techo1 > piso2) || (piso1 > techo2)) return true;
    return false;

}

//Solo cuando colisionan
float Colisionador::distanciaColisionadaenX(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2){
    float bordeDerecho1 = objeto1->pos.getX() + objeto1->ancho/2;
    float bordeIzquierdo2 = objeto2->pos.getX() - objeto2->ancho/2;

    return bordeDerecho1 - bordeIzquierdo2;
}



void Colisionador::solucionarColision(Personaje* PJ1, Personaje* PJ2){

    // Choques entre los cuerpos de los pjs

    //Los dos caminando en sentido contrario
    if(PJ1->sentido == true && PJ1->estado == CAMINANDO && PJ2->sentido == true && PJ2->estado == CAMINANDO){
        cout<<"gola1"<<endl;
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0) {
            PJ1->pos.setX(PJ1->pos.getX() - 1);
            PJ2->pos.setX(PJ2->pos.getX() + 1);
        } else {
            PJ1->pos.setX(PJ1->pos.getX() + 1);
            PJ2->pos.setX(PJ2->pos.getX() - 1);
        };
    }
    else{
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0 ) {
            //Un pj empuja a otro que esta protegido. TODO: Falta que se proteja agachado
            if(PJ1->protegiendose || PJ2->protegiendose) {
                if(PJ1->estado == CAMINANDO && PJ1->sentido == true){
                    if (PJ2->estado ==PARADO) {
                        PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                        PJ2->realizarAccion(KEY_DERECHA, anchoEsc);
                        PJ2->estado = PARADO;
                        PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                        PJ2->accionesEnCurso[2]->setAnchoDePasoDefault();
                    }
                    else if (PJ2->estado ==AGACHADO) {
                        PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                        PJ2->realizarAccion(KEY_DERECHA, anchoEsc);
                        PJ2->realizarAccion(KEY_ABAJO,anchoEsc);
                        PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                        PJ2->accionesEnCurso[2]->setAnchoDePasoDefault();
                    }

                }
                else if(PJ2->estado == CAMINANDO && PJ2->sentido == true){
                    if (PJ1->estado == PARADO) {
                        PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                        PJ1->realizarAccion(KEY_IZQUIERDA, anchoEsc);
                        PJ1->estado = PARADO;
                        PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                        PJ1->accionesEnCurso[2]->setAnchoDePasoDefault();
                    }
                    else if (PJ1->estado == AGACHADO) {
                        PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                        PJ1->realizarAccion(KEY_IZQUIERDA, anchoEsc);
                        PJ1->realizarAccion(KEY_ABAJO,anchoEsc);
                        PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRetrocesoConProteccion);
                        PJ1->accionesEnCurso[2]->setAnchoDePasoDefault();
                    }
                }
            }
            // Un pj empuja a otro (sin proteccion). Vale para parado y agachado
            else{
                cout<<"gola2"<<endl;
                if(PJ1->estado == CAMINANDO && PJ1->sentido == true){
                    if(PJ2->estado == PARADO) {
                        PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                        PJ2->realizarAccion(KEY_DERECHA, anchoEsc);
                        PJ2->estado = PARADO;
                        PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                        PJ2->accionesEnCurso[2]->setAnchoDePasoDefault();
                    }
                    else if(PJ2->estado == AGACHADO) {
                        PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                        PJ2->realizarAccion(KEY_DERECHA, anchoEsc);
                        PJ2->realizarAccion(KEY_ABAJO,anchoEsc);
                        PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                        PJ2->accionesEnCurso[2]->setAnchoDePasoDefault();
                    }
                }
                else if(PJ2->estado == CAMINANDO && PJ2->sentido == true){
                    if (PJ1->estado == PARADO){
                        PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                        PJ1->realizarAccion(KEY_IZQUIERDA, anchoEsc);
                        PJ1->estado = PARADO;
                        PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                        PJ1->accionesEnCurso[2]->setAnchoDePasoDefault();
                    }
                    else if (PJ1->estado == AGACHADO){
                        PJ1->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                        PJ1->realizarAccion(KEY_IZQUIERDA, anchoEsc);
                        PJ1->realizarAccion(KEY_ABAJO,anchoEsc);
                        PJ2->accionesEnCurso[2]->setAnchoDePaso(factorDeRestrocesoSinProteccion);
                        PJ1->accionesEnCurso[2]->setAnchoDePasoDefault();
                    }
                }
            }
        }
    }

    //Colision entre un pj saltando oblicuamente y otro que esta parado (que no se superpongan luego dle salto)
    if(PJ1->estado == SALTANDO_OBLICUO && PJ1->sentido == true && (PJ2->estado == PARADO || PJ2->estado == AGACHADO) && seProdujoColision(PJ1,PJ2)){
        cout<<"gola3"<<endl;
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0) {
            PJ2->pos.setX(PJ2->pos.getX() + distanciaColisionadaenX(PJ1,PJ2));
        } else {
            PJ2->pos.setX(PJ2->pos.getX() - distanciaColisionadaenX(PJ2,PJ1));
        };
    }

    //Colision entre un pj saltando oblicuamente y otro caminando
    if(PJ1->estado == SALTANDO_OBLICUO && PJ1->sentido == true && PJ2->estado == CAMINANDO && seProdujoColision(PJ1,PJ2)){
        cout<<"gola3"<<endl;
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0) {
            PJ2->pos.setX(PJ2->pos.getX() + distanciaColisionadaenX(PJ1,PJ2));
        } else {
            PJ2->pos.setX(PJ2->pos.getX() - distanciaColisionadaenX(PJ2,PJ1));
        };
    }

    //Colision entre un pj Saltando vertical y otro caminando
    if(PJ1->estado == SALTANDO_VERTICAL && PJ2->estado == CAMINANDO && PJ2->sentido == true && seProdujoColision(PJ1,PJ2)){
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0) {
            PJ2->pos.setX(PJ2->pos.getX() + distanciaColisionadaenX(PJ1,PJ2));
        } else {
            PJ2->pos.setX(PJ2->pos.getX() - distanciaColisionadaenX(PJ2,PJ1));
        };
    }

    // Colision entre un pj saltando vertical y otro saltando oblicuamente
    if(PJ1->estado == SALTANDO_VERTICAL && PJ2->estado == SALTANDO_OBLICUO && PJ2->sentido == true && seProdujoColision(PJ1,PJ2)){
        cout<<"gola4"<<endl;
        if ((PJ1->pos.getX() - PJ2->pos.getX()) <= 0) {
            PJ2->enCaida = true;
            PJ2->pos.setX(PJ2->pos.getX() + distanciaColisionadaenX(PJ1,PJ2));
        } else {
            PJ2->enCaida = true;
            PJ2->pos.setX(PJ2->pos.getX() - distanciaColisionadaenX(PJ2,PJ1));
        };
    }
}

void Colisionador::solucionarColision(Personaje *PJ, Golpe *golpeOponente) {
    PJ->mePegaron(golpeOponente->danio);
    cout<<"SE ESTAN PEGANDO"<<endl;
}

void Colisionador::solucionarColision(Personaje *PJ, Poder *poderOponente) {

    poderOponente->estado = false;
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


    poderOponente->pos = Posicion(posX,poderOponente->pos.getY());




    //Lo congela al enemigo


}