#include "Accionador.h"
//CONSTANTES PARA LA CREACION DE golpe->
const float proporcionPiniaAlta = 0.25;
const float proporcionPiniaBaja = 0.35;
const float proporcionPatadaAlta = 0.31;
const float proporcionPatadaBaja = 0.42;
const float porporcionPatadaAltaAtras = 0.27;
const float proporcionPatadaBajaAtras = 0.44;
const float proporcionPiniaBajaAgachado = 0.29;
const float proporcionPiniaAltaAgachado = 0.19;
const float proporcionPiniaSalto = 0.49;
const float proporcionPatadaSV = 0.31;
const float proporcionPatadaSO = 0.37;
const float proporcionPatadaAgachado = 0.3;

//Danios golpes
const float poderFuerte = 5;
const float patadasAltas = 3;
const float patadasBajas = 2;
const float piniasAltas = 2;
const float piniasBajas = 2;

//CONSTANTES DE MOVIMIENTO
const float intervaloPaso =2;
const float intervaloSaltoVertical = 10;
const float intervaloSaltoOblicuo = 5;
const float proporcionSalto = 3;

Accionador::Accionador() {


}
void Accionador::initialize(Trect rectan, float anchoPanta, float yPiso,Poder* nuevoPoder,Golpe* nuevoGolpe) {

    rectaDelPj = rectan;
    anchoPantalla = anchoPanta;
    ydelPiso = yPiso;
    estAct = MOV_PARADO;
    estAnt = MOV_PARADO;
    golpe = nuevoGolpe;
    this->poder = nuevoPoder;
    alturaPj = rectan.d.h;
    posCongelado = rectan.p;

}

Trect Accionador::laAccion(TestadoPersonaje estadoPj, int loops, Posicion pos, Tsentido sentido, Tdireccion direccion) {

    estAnt = estAct;
    estAct = estadoPj;
    if(estAnt == MOV_AGACHADO && estAct != MOV_AGACHADO) {
        ponerseDePie();
        return rectaDelPj;
    }
    if(golpe->estado) golpe->setEstado(false);
    switch (estadoPj){
        //case movimiento ---------------------------------
        case MOV_PARADO:
            if(rectaDelPj.p.y != ydelPiso-rectaDelPj.d.h) ajustarPiso();
            break;
        case MOV_CAMINANDO:
            caminar(sentido,direccion);
            break;
        case MOV_SALTANDO_VERTICAL:
            saltarVerticualmente(loops);
            break;
        case MOV_SALTANDO_OBLICUO:
            saltarOblicuamente(loops,sentido,direccion);
            break;
        case MOV_AGACHADO:
            agachar();
            break;

            //case acciones ---------------------------------
        case ACC_PINIA_BAJA:
            piniaBaja(loops,direccion);
            break;
        case ACC_PINIA_BAJA_AGACHADO:
            piniaBajaAgachado(loops,direccion);
            break;
        case ACC_PINIA_ALTA:
            piniaAlta(loops,direccion);
            break;
        case ACC_PINIA_ALTA_AGACHADO:
            piniaAltaAgachado(loops,direccion);
            break;
        case ACC_PINIA_SALTO:
            saltarOblicuamente(loops,sentido,direccion);
            golpeSaltoOblicuo(loops,direccion);
            break;
        case ACC_PATADA_BAJA:
            patadaBaja(loops,direccion);
            break;
        case ACC_PATADA_BAJA_ATRAS:
            patadaBajaAtras(loops,direccion);
            break;
        case ACC_PATADA_AGACHADO:
            patadaAgachado(loops,direccion);
            break;
        case ACC_PATADA_SALTO_VERTICAL:
            saltarVerticualmente(loops);
            golpeSaltoVertical(loops,direccion);
            break;
        case ACC_PINIA_SALTO_VERTICAL:
            saltarVerticualmente(loops);
            golpeSaltoVertical(loops,direccion);
            break;
        case ACC_PATADA_SALTO:
            saltarOblicuamente(loops,sentido,direccion);
            golpeSaltoOblicuo(loops,direccion);
            break;
        case ACC_PATADA_ALTA:
            patadaAlta(loops,direccion);
            break;
        case ACC_PATADA_ALTA_ATRAS:
            patadaAltaAtras(loops,direccion);
            break;
        case ACC_PROTECCION:
            break;
        case ACC_PROTECCION_AGACHADO:
            break;
        case ACC_PODER:
            activarPoder(direccion);
            break;
        case ACC_PODER_SALTO:
            activarPoder(direccion);
            saltarVerticualmente(loops);
            break;
        case ACC_AGARRE:
            agarrar(loops);
            break;
        case REA_AGARRE:
            agarrado(loops,direccion,sentido);
            break;
            //case Reacciones ---------------------------------
        case REA_AGACHADO:
            break;
        case REA_GOLPE_ALTO:
            reaccionTrasPiniaAlta(loops,direccion);
            break;
        case REA_GOLPE_BAJO:
            //reaccionTrasPiniaAlta(loops,direccion);
            break;
        case REA_GOLPE_FUERTE:
            reaccionTrasGolpeFuerte(loops,direccion);
            break;
        case REA_PATADA_BARRIDA:
            reaccionBarrida(loops,direccion);
            break;
        case REA_PINIA_ALTA:
            //reaccionTrasPiniaAlta(loops,direccion);
            break;
        case REA_CONGELADO:
            if(loops == 1) {
                posCongelado = rectaDelPj.p;
                posCongelado.mostrarPar();
            }
            congelado();
            break;

    }
    return rectaDelPj;
}
Accionador::~Accionador() {
}
//--------------------------------------------------------------------------------------
//                  ACCIONES
//--------------------------------------------------------------------------------------
//                  CAMINAR
void Accionador::caminar(Tsentido sentido, Tdireccion direccion) {
    if(direccion == DERECHA){
        if(sentido == ADELANTE) rectaDelPj.p = rectaDelPj.p + Posicion(intervaloPaso,0);
        else rectaDelPj.p = rectaDelPj.p + Posicion(-intervaloPaso,0);
    }else{
        if(sentido == ADELANTE) rectaDelPj.p =rectaDelPj.p + Posicion(-intervaloPaso,0);
        else rectaDelPj.p =rectaDelPj.p + Posicion(intervaloPaso,0);
    }
}
//--------------------------------------------------------------------------------------
//                  SALTO VERTICAL
void Accionador::saltarVerticualmente(int loops) {

    if(loopsPara(MOV_SALTANDO_VERTICAL) >= loops){
        if (loops<=(loopsPara(MOV_SALTANDO_VERTICAL)/2)) {
            rectaDelPj.p =rectaDelPj.p+Posicion(0,-intervaloSaltoVertical);
        }
        else {
            rectaDelPj.p =rectaDelPj.p+Posicion(0,intervaloSaltoVertical);
        }
    }
}
//--------------------------------------------------------------------------------------
//                  SALTO OBLICUO
void Accionador::subirEnSaltoOblicuo(float deltaMovX,float deltaMovY,Tsentido sentido){
    if(direcBloqueada == DERECHA){
        if (sentido == ADELANTE) rectaDelPj.p =rectaDelPj.p+Posicion(deltaMovX,-deltaMovY);
        else {
            rectaDelPj.p =rectaDelPj.p+Posicion(-deltaMovX,-deltaMovY);
        }
    }else{
        if (sentido == ADELANTE) rectaDelPj.p =rectaDelPj.p+Posicion(-deltaMovX,-deltaMovY);
        else {
            rectaDelPj.p =rectaDelPj.p+Posicion(deltaMovX,-deltaMovY);
        }
    }
}
void Accionador::bajarEnSaltoOblicuo(float deltaMovX,float deltaMovY,Tsentido sentido) {
    if (direcBloqueada == DERECHA) {
        if (sentido == ADELANTE) rectaDelPj.p = rectaDelPj.p + Posicion(deltaMovX, deltaMovY);
        else rectaDelPj.p = rectaDelPj.p + Posicion(-deltaMovX, deltaMovY);
    } else {
        if (sentido == ADELANTE) rectaDelPj.p = rectaDelPj.p + Posicion(-deltaMovX, deltaMovY);
        else rectaDelPj.p = rectaDelPj.p + Posicion(deltaMovX, deltaMovY);
    }
}
void Accionador::saltarOblicuamente(int loops, Tsentido sentido, Tdireccion direccion) {

    if(loops == 1) direcBloqueada = direccion;

    if(loopsPara(MOV_SALTANDO_OBLICUO) >=loops){
        // en la priemra mitad de loops sube
        if(loops <= (loopsPara(MOV_SALTANDO_OBLICUO)/2)){
            //en el primer cuarto sube mas rapidamente que en el segundo
            if(loops <= (loopsPara(MOV_SALTANDO_OBLICUO)/4)) subirEnSaltoOblicuo(intervaloSaltoOblicuo,intervaloSaltoOblicuo*3,sentido);
            else subirEnSaltoOblicuo(intervaloSaltoOblicuo,intervaloSaltoOblicuo,sentido);
        }else{
            //en la segunda mitad de los loops baja
            //en el primer cuarto de estos baja mas lentamente que en el segundo cuarto
            if(loops <= (proporcionSalto*loopsPara(MOV_SALTANDO_OBLICUO)/4)) bajarEnSaltoOblicuo(intervaloSaltoOblicuo,intervaloSaltoOblicuo,sentido);
            else bajarEnSaltoOblicuo(intervaloSaltoOblicuo,intervaloSaltoOblicuo*proporcionSalto,sentido);
        }
    }
}
//--------------------------------------------------------------------------------------
//                  AGACHAR
void Accionador::agachar() {
    if(estAnt != MOV_AGACHADO){
        rectaDelPj.d.h = rectaDelPj.d.h/2;
        rectaDelPj.p = rectaDelPj.p + Posicion(0,rectaDelPj.d.h);
    }
}
void Accionador::ponerseDePie() {
    rectaDelPj.p = rectaDelPj.p + Posicion(0,-alturaPj/2);
    rectaDelPj.d.h = alturaPj;
}

//--------------------------------------------------------------------------------------
//                  GOLPES
//--------------------------------------------------------------------------------------
//                  PINIA BAJA
//TODO:: FALTA AJUSTAR, EL ALTO DEL CUADRADO Y LA POSICION Y LAS REACCIONES
void Accionador::piniaBaja(int loops,Tdireccion direccion) {

    Trect rectan = Trect();
    rectan.d.w = rectaDelPj.d.w * proporcionPiniaBaja;
    rectan.p = rectaDelPj.p;
    if(direccion == DERECHA) rectan.p = rectan.p + Posicion(rectaDelPj.d.w,0);
    else rectan.p = rectan.p - Posicion(rectan.d.w, 0);
    if(loopsPara(ACC_PINIA_BAJA)>loops){
        golpe->setGolpe(piniasBajas,true,rectan,REA_GOLPE_BAJO);
    }
}
//--------------------------------------------------------------------------------------
//                  PINIA BAJA AGACHADO
void Accionador::piniaBajaAgachado(int loops,Tdireccion direccion) {
    Trect rectan = Trect();
    rectan.d.w = rectaDelPj.d.w * proporcionPiniaBajaAgachado;
    rectan.p = rectaDelPj.p;
    if(direccion == DERECHA) rectan.p = rectan.p + Posicion(rectaDelPj.d.w,0);
    else rectan.p = rectan.p - Posicion(rectan.d.w, 0);
    if(loopsPara(ACC_PINIA_BAJA_AGACHADO)>loops){
        golpe->setGolpe(piniasBajas, loops == 2,rectan,REA_GOLPE_BAJO);
    }
}
//--------------------------------------------------------------------------------------
//                  PINIA ALTA
void Accionador::piniaAlta(int loops,Tdireccion direccion) {
    Trect rectan = Trect();
    rectan.d.w = rectaDelPj.d.w * proporcionPiniaAlta;
    rectan.p = rectaDelPj.p;
    if(direccion == DERECHA) rectan.p = rectan.p + Posicion(rectaDelPj.d.w,0);
    else rectan.p = rectan.p - Posicion(rectan.d.w, 0);
    if(loopsPara(ACC_PINIA_ALTA)>loops){
        golpe->setGolpe(piniasAltas, loops == 2,rectan,REA_PINIA_ALTA);
    }
}
//--------------------------------------------------------------------------------------
//                  PINIA ALTA AGACHADO
void Accionador::piniaAltaAgachado(int loops,Tdireccion direccion) {
    Trect rectan = Trect();
    rectan.d.w = rectaDelPj.d.w * proporcionPiniaAltaAgachado;
    rectan.p = rectaDelPj.p;
    if(direccion == DERECHA) rectan.p = rectan.p + Posicion(rectaDelPj.d.w,0);
    else rectan.p = rectan.p - Posicion(rectan.d.w, 0);
    if (loopsPara(ACC_PINIA_ALTA_AGACHADO) > loops) {
        golpe->setGolpe(poderFuerte, loops == 3, rectan, REA_GOLPE_FUERTE);
    }
}
//--------------------------------------------------------------------------------------
//                  PATADA BAJA
void Accionador::patadaBaja(int loops,Tdireccion direccion) {
    Trect rectan = Trect();
    rectan.d.w = rectaDelPj.d.w * proporcionPatadaBaja;
    rectan.p = rectaDelPj.p;
    if(direccion == DERECHA) rectan.p = rectan.p + Posicion(rectaDelPj.d.w,0);
    else rectan.p = rectan.p - Posicion(rectan.d.w, 0);
    if (loopsPara(ACC_PATADA_BAJA) > loops) {
        golpe->setGolpe(poderFuerte, loops == 4, rectan, REA_GOLPE_BAJO);
    }
}
//--------------------------------------------------------------------------------------
//                  PATADA BAJA ATRAS
void Accionador::patadaBajaAtras(int loops,Tdireccion direccion) {
    Trect rectan = Trect();
    rectan.d.w = rectaDelPj.d.w * proporcionPatadaBajaAtras;
    rectan.p = rectaDelPj.p;
    if(direccion == DERECHA) rectan.p = rectan.p + Posicion(rectaDelPj.d.w,0);
    else rectan.p = rectan.p - Posicion(rectan.d.w, 0);
    if (loopsPara(ACC_PATADA_ALTA_ATRAS) > loops) {
        golpe->setGolpe(poderFuerte, loops == 5, rectan, REA_PATADA_BARRIDA);
    }

}
//--------------------------------------------------------------------------------------
//                  PATADA ALTA ATRAS
void Accionador::patadaAltaAtras(int loops,Tdireccion direccion) {
    Trect rectan = Trect();
    rectan.d.w = rectaDelPj.d.w * porporcionPatadaAltaAtras;
    rectan.p = rectaDelPj.p;
    if(direccion == DERECHA) rectan.p = rectan.p + Posicion(rectaDelPj.d.w,0);
    else rectan.p = rectan.p - Posicion(rectan.d.w, 0);
    if(loopsPara(ACC_PATADA_ALTA_ATRAS)>loops){
        golpe->setGolpe(poderFuerte, loops == 5,rectan,REA_GOLPE_FUERTE);
        }
    }
//--------------------------------------------------------------------------------------
//                  PATADA ALTA
void Accionador::patadaAlta(int loops,Tdireccion direccion) {
    Trect rectan = Trect();
    rectan.d.w = rectaDelPj.d.w * proporcionPatadaAlta;
    rectan.p = rectaDelPj.p;
    if(direccion == DERECHA) rectan.p = rectan.p + Posicion(rectaDelPj.d.w,0);
    else rectan.p = rectan.p - Posicion(rectan.d.w, 0);
    if(loopsPara(ACC_PATADA_ALTA)>loops){
        golpe->setGolpe(patadasAltas, loops == 4,rectan,REA_GOLPE_ALTO);
    }

}
//--------------------------------------------------------------------------------------
//                  GOLPE DURANTE EL SALTO Vertical
void Accionador::golpeSaltoVertical(int loops,Tdireccion direccion) {
    Trect rectan = Trect();
    rectan.d.w = rectaDelPj.d.w * proporcionPatadaSV;
    rectan.p = rectaDelPj.p;
    if(direccion == DERECHA) rectan.p = rectan.p + Posicion(rectaDelPj.d.w,rectaDelPj.d.h-rectan.d.h);
    else rectan.p = rectan.p + Posicion(-rectan.d.w,rectaDelPj.d.h-rectan.d.h);
    if(loopsPara(ACC_PATADA_SALTO_VERTICAL)>loops){
        golpe->setGolpe(patadasAltas,true,rectan,REA_GOLPE_FUERTE);
    }
}
//--------------------------------------------------------------------------------------
//                  GOLPE DURANTE EL SALTO OBLICUO
void Accionador::golpeSaltoOblicuo(int loops,Tdireccion direccion) {
    Trect rectan = Trect();
    rectan.d.w = rectaDelPj.d.w * proporcionPatadaSV;
    rectan.p = rectaDelPj.p;
    if(direccion == DERECHA) rectan.p = rectan.p + Posicion(rectaDelPj.d.w,rectaDelPj.d.h-rectan.d.h);
    else rectan.p = rectan.p + Posicion(-rectan.d.w,rectaDelPj.d.h-rectan.d.h);
    if(loopsPara(ACC_PATADA_SALTO)>loops){
        golpe->setGolpe(patadasAltas,true,rectan,REA_GOLPE_FUERTE);
    }
}
//--------------------------------------------------------------------------------------
//                  PATADA AGACHADO
void Accionador::patadaAgachado(int loops,Tdireccion direccion) {
    Trect rectan = Trect();
    rectan.d.w = rectaDelPj.d.w * proporcionPatadaAgachado;
    rectan.p = rectaDelPj.p;
    if(direccion == DERECHA) rectan.p = rectan.p + Posicion(rectaDelPj.d.w,0);
    else rectan.p = rectan.p - Posicion(rectan.d.w, 0);
    if(loopsPara(ACC_PATADA_AGACHADO)>loops){
        golpe->setGolpe(patadasBajas, loops == 2,rectan,REA_GOLPE_BAJO);
    }

}
//--------------------------------------------------------------------------------------
//                  PODER
void Accionador::activarPoder(Tdireccion direccion) {
    if(poder->estado == DESACTIVADO) {
        poder->activar(rectaDelPj, direccion, anchoPantalla);
    }
}
//--------------------------------------------------------------------------------------
//                  REACCIONES
//--------------------------------------------------------------------------------------
//                  REACCION TRAS LA PINIA
void Accionador::reaccionTrasPiniaAlta(int loops, Tdireccion direccion) {

    if (direccion == DERECHA){
        rectaDelPj.p = rectaDelPj.p + Posicion(-2,0);
    }else{
        rectaDelPj.p = rectaDelPj.p + Posicion(2,0);
    }
}
//--------------------------------------------------------------------------------------
//                  REACCION TRAS EL GOLPE FUERTE
void Accionador::reaccionTrasGolpeFuerte(int loops, Tdireccion direccion) {
    if(loops<=loopsPara(REA_GOLPE_FUERTE)/2){
        if(direccion == DERECHA)rectaDelPj.p =rectaDelPj.p+Posicion(-intervaloSaltoOblicuo,-3*intervaloSaltoOblicuo);
        else rectaDelPj.p =rectaDelPj.p+Posicion(intervaloSaltoOblicuo,-3*intervaloSaltoOblicuo);
    }else{
        if (direccion == DERECHA) rectaDelPj.p = rectaDelPj.p + Posicion(-intervaloSaltoOblicuo, 3*intervaloSaltoOblicuo);
        else rectaDelPj.p = rectaDelPj.p + Posicion(intervaloSaltoOblicuo, 3*intervaloSaltoOblicuo);
    }
}
//--------------------------------------------------------------------------------------
//                  REACCION BARRIDA
void Accionador::reaccionBarrida(int loops, Tdireccion direccion) {

}

Posicion Accionador::desplazado(float deltaDesplazo,Tdireccion direccion){

    if(direccion == DERECHA) rectaDelPj.p = rectaDelPj.p + Posicion(-deltaDesplazo,0);
    else rectaDelPj.p =rectaDelPj.p + Posicion(deltaDesplazo,0);
    return rectaDelPj.p;
}

Golpe *Accionador::getGolpe() {
    return golpe;
}

Trect Accionador::setPosicionPersonaje(Posicion posicion) {
    rectaDelPj.p = posicion;
    return rectaDelPj;
}

void Accionador::ajustarPiso() {
    rectaDelPj.p.y = ydelPiso - rectaDelPj.d.h;

}

void Accionador::agarrado(int loops, Tdireccion direccion, Tsentido sentido) {

    if(loops == 6){
        rectaDelPj.d.h = (rectaDelPj.d.h/2) - 5;
        direcBloqueada = direccion;
        if(direccion == DERECHA) rectaDelPj.p = rectaDelPj.p + Posicion(rectaDelPj.d.w/2,0);
        else rectaDelPj.p = rectaDelPj.p + Posicion(-rectaDelPj.d.w/2,0);
    }else if(loops == 7){
        if(direccion == DERECHA) rectaDelPj.p = rectaDelPj.p + Posicion(rectaDelPj.d.w/2,0);
        else rectaDelPj.p = rectaDelPj.p + Posicion(-rectaDelPj.d.w/2,0);
    }else if(loops >7){
        if(loops <= ((loopsPara(MOV_SALTANDO_OBLICUO)/2)-2)){
            subirEnSaltoOblicuo(intervaloSaltoOblicuo*3,intervaloSaltoOblicuo,sentido);
        }else{
            bajarEnSaltoOblicuo(intervaloSaltoOblicuo*3,intervaloSaltoOblicuo,sentido);
        }
    }
    if(loops == 10) ponerseDePie();
}

void Accionador::agarrar(int loops) {
    if(loops == 2){
        rectaDelPj.d.h = (rectaDelPj.d.h/2) - 5;
        rectaDelPj.p = rectaDelPj.p + Posicion(0,rectaDelPj.d.h+10);
    }
    if(loops == 9) ponerseDePie();

}

void Accionador::congelado() {
    rectaDelPj.p = posCongelado;

}
