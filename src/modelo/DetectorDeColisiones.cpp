

#include "DetectorDeColisiones.h"

DetectorDeColisiones::DetectorDeColisiones() {}

DetectorDeColisiones::DetectorDeColisiones(float anchoPantalla, float anchoEscenario){
    this->anchoPantalla = anchoPantalla;
    this->anchoEscenario = anchoEscenario;
}

void DetectorDeColisiones::resolverColisiones(Personaje *personaje1, Personaje *personaje2) {

    colisionar(personaje1,personaje2);
    if(personaje1->llevarACabo.getGolpe()->estado) colisionar(personaje2,personaje1->llevarACabo.getGolpe());
    if(personaje2->llevarACabo.getGolpe()->estado) colisionar(personaje1,personaje2->llevarACabo.getGolpe());



    if(personaje1->poder->estado == ACTIVADO && personaje2->poder->estado == ACTIVADO){
        colisionar(personaje1->poder,personaje2->poder);
        colisionar(personaje1,personaje2->poder);
        colisionar(personaje2,personaje1->poder);
    }
    else{
        if(personaje1->poder->estado == ACTIVADO) colisionar(personaje2,personaje1->poder);
        else if(personaje2->poder->estado == ACTIVADO) colisionar(personaje1,personaje2->poder);
    }

    resolverColisionconPantalla(personaje1,personaje2);
    resolverColisionconPantalla(personaje2,personaje1);
    resolverColisionconEscenario(personaje1);
    resolverColisionconEscenario(personaje2);
}



// Detecta si dos objetos colisionaron (parte de uno dentro de otro)
// Si objeto1 u objeto2 son NULL devuelvo false
bool DetectorDeColisiones::detectarColision(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2) {

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

    if ( (bordeDerecho2 < bordeIzquierdo1) || (bordeIzquierdo2 > bordeDerecho1) )return false;
    else return !((techo2 > piso1) || (piso2 < techo1));
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

    return !((techo1 > piso2) || (piso1 < techo2));
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

// Si dos poderes estan colisionando o se hace el efecto tunel entonces se resuelva la misma.
// Se setea a los dos poderes en COLISION (se desactiva en el siguiente loop).
void DetectorDeColisiones::colisionar(Poder *poder1, Poder *poder2) {

    float distanciaEntrePoderes = distancia(poder1,poder2);
    if(distanciaEntrePoderes<velocidadDelPoder*2 && detectarColisionenY(poder1,poder2) && !poder1->primerLoop && !poder2->primerLoop){
        poder1->avanzar(distanciaEntrePoderes/2);
        poder2->avanzar(distanciaEntrePoderes/2);
        poder1->estado = COLISION;
        poder2->estado = COLISION;
    }

}


bool DetectorDeColisiones::verificarEstadosAnterioresAlChoque(Personaje *PJ){

    return ((PJ->estadoActual == MOV_SALTANDO_OBLICUO  && PJ->sentidoPj == ADELANTE)
            || PJ->estadoActual == MOV_CAMINANDO
            || PJ->estadoActual == MOV_PARADO
            || PJ->estadoActual == MOV_AGACHADO
            || PJ->estadoActual == MOV_SALTANDO_VERTICAL);
}

void DetectorDeColisiones::separarPersonajes(Personaje *PJ1, Personaje *PJ2) {

    float distancia;
    if ((PJ1->rectanguloPj.p.getX() - PJ2->rectanguloPj.p.getX()) <= 0)
        distancia = distanciaColisionadaenX(PJ1,PJ2);
    else distancia = distanciaColisionadaenX(PJ2,PJ1);
    PJ1->empujado(distancia/2,PJ1->direccionPj);
    PJ2->empujado(distancia/2,PJ2->direccionPj);

}
// Resuelve las colisiones entre los dos personajes.
// Dicha resolucion se tiene que hacer ida y vuelta para los personajes, debido a que todas las comprobaciones
// se hacen una sola vez
void DetectorDeColisiones::resolverColision(Personaje *PJ1, Personaje *PJ2) {
    //Los dos caminando en sentido contrario
   if(PJ1->sentidoPj == ADELANTE && PJ1->estadoActual == MOV_CAMINANDO && PJ2->sentidoPj == ADELANTE && PJ2->estadoActual == MOV_CAMINANDO){
       separarPersonajes(PJ1,PJ2);
    }
    else{
       // Empuja uno al otro
        if ((PJ1->rectanguloPj.p.getX() - PJ2->rectanguloPj.p.getX()) <= 0 ) {
            if(PJ1->estadoActual == MOV_CAMINANDO && PJ1->sentidoPj == ADELANTE) {
                if (PJ2->estadoActual == MOV_PARADO || PJ2->estadoActual == MOV_AGACHADO || PJ2->estadoActual == MOV_SALTANDO_VERTICAL) {
                    PJ2->empujado(2, PJ2->direccionPj);
                }
                if (PJ2->estadoActual == ACC_PROTECCION || PJ2->estadoActual == ACC_PROTECCION_AGACHADO) {
                    PJ2->empujado(1, PJ2->direccionPj);
                    PJ1->empujado(1, PJ1->direccionPj);
                }
            }
            else if(PJ2->estadoActual == MOV_CAMINANDO && PJ2->sentidoPj == ADELANTE){
                if (PJ1->estadoActual == MOV_PARADO || PJ1->estadoActual == MOV_AGACHADO || PJ1->estadoActual == MOV_SALTANDO_VERTICAL) {
                    PJ1->empujado(2, PJ1->direccionPj);
                }
                if (PJ1->estadoActual == ACC_PROTECCION || PJ1->estadoActual == ACC_PROTECCION_AGACHADO) {
                    PJ2->empujado(1, PJ2->direccionPj);
                    PJ1->empujado(1, PJ1->direccionPj);
                }
            }
        }
    }
    if (PJ1->estadoActual == MOV_SALTANDO_OBLICUO && PJ1->sentidoPj == ADELANTE){
        if(verificarEstadosAnterioresAlChoque(PJ2)) separarPersonajes(PJ1,PJ2);
    }
    separarPersonajes(PJ1,PJ2);
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
    if (PJ->estadoActual == ACC_PROTECCION || PJ->estadoActual ==ACC_PROTECCION_AGACHADO) PJ->reducirVida(golpe->danio/2);
    else PJ->reducirVida(golpe->danio);
    PJ->estadoAnterior = PJ->estadoActual;
    PJ->estadoActual = golpe->efectoSobreOponente;

    // Ajustar la superrectanguloPj.picion del golpe con el personaje si es necesario
}

void DetectorDeColisiones::resolverColisionconPantalla(Personaje *PJ1,Personaje* PJ2) {
    float ancho1 = PJ1->getRectangulo().d.w;
    float ancho2 = PJ2->getRectangulo().d.w;
    float distanciaMaxima = anchoPantalla - 2 * MIN_DISTANCE_FROM_BOUND - ancho1 - ancho2;

    float distanciaPasada = distancia(PJ1,PJ2) - distanciaMaxima;
    if(distanciaPasada > 0){
        PJ1->setPosicion(Posicion(PJ1->posicionAnterior.getX(),PJ1->getRectangulo().p.getY()));
        PJ2->setPosicion(Posicion(PJ2->posicionAnterior.getX(),PJ2->getRectangulo().p.getY()));
    }

}

float DetectorDeColisiones::distancia(ObjetoColisionable *objeto1, ObjetoColisionable *objeto2) {
    float distancia;
    float posicionXObjeto1 = objeto1->getRectangulo().p.getX();
    float posicionXObjeto2 = objeto2->getRectangulo().p.getX();
    float ancho1 = objeto1->getRectangulo().d.w;
    float ancho2 = objeto2->getRectangulo().d.w;

    if(posicionXObjeto1 < posicionXObjeto2) distancia = posicionXObjeto2 - posicionXObjeto1 - ancho1;
    else distancia = posicionXObjeto1 - posicionXObjeto2 - ancho2;

    return distancia;
}

void DetectorDeColisiones::resolverColisionconEscenario(Personaje *PJ) {

    float topeDerecha = anchoEscenario - PJ->getRectangulo().p.getX();
    float anchoPJ = PJ->getRectangulo().d.w;

    if(topeDerecha< anchoPJ){
        PJ->empujado(-(anchoPJ-topeDerecha),PJ->direccionPj);
    }

    float topeIzquierda = (-1)* PJ->getRectangulo().p.getX();

    if(topeIzquierda > 0){
        PJ->empujado(-topeIzquierda,PJ->direccionPj);
    }
}

void DetectorDeColisiones::colisionar(Personaje *PJ, Poder *poder) {
    float distanciaPJPoder = distancia(PJ,poder);
    if((distanciaPJPoder < velocidadDelPoder && detectarColisionenY(PJ,poder)) && !poder->primerLoop){
        poder->avanzar(distanciaPJPoder);
        poder->estado = COLISION;
        if(PJ->estadoActual == ACC_PROTECCION)PJ->reducirVida(poder->danio/2);
        else PJ->reducirVida(poder->danio);
    }
}