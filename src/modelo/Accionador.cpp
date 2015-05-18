#include "Accionador.h"
//CONSTANTES PARA LA CREACION DE GOLPES
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
const float alturaSaltoOblicuo = 50;
const float anchoSaltoOblicuo = 100;
const float proporcionSalto = 3;

Accionador::Accionador() {


}
void Accionador::initialize(Trect rectan, float anchoEscenario, float yPiso) {

    rectaDelPj = rectan;
    anchoEsc = anchoEscenario;
    ydelPiso = yPiso;
    nuevoEstado = MOV_PARADO;
    golpe = Golpe();
}

Trect Accionador::laAccion(TestadoPersonaje estadoPj, int loops, Posicion pos, Tsentido sentido, Tdireccion direccion) {


    switch (estadoPj){
        //case movimiento ---------------------------------
        case MOV_PARADO:
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
            piniaBaja(loops);
            break;
        case ACC_PINIA_BAJA_AGACHADO:
            piniaBajaAgachado(loops);
            break;
        case ACC_PINIA_ALTA:
            piniaAlta(loops);
            break;
        case ACC_PINIA_ALTA_AGACHADO:
            piniaAltaAgachado(loops);
            break;
        case ACC_PINIA_SALTO:
            piniaSalto(loops);
            break;
        case ACC_PATADA_BAJA:
            patadaBaja(loops);
            break;
        case ACC_PATADA_BAJA_ATRAS:
            patadaBajaAtras(loops);
            break;
        case ACC_PATADA_AGACHADO:
            patadaAgachado(loops);
            break;
        case ACC_PATADA_SALTO_VERTICAL:
            patadaSaltoVertical(loops);
            break;
        case ACC_PATADA_SALTO:
            patadaSalto(loops);
            break;
        case ACC_PATADA_ALTA:
            patadaAlta(loops);
            break;
        case ACC_PATADA_ALTA_ATRAS:
            patadaAltaAtras(loops);
            break;
        case ACC_PROTECCION:
            break;
        case ACC_PROTECCION_AGACHADO:
            break;
        case ACC_PODER:
            break;

            //case Reacciones ---------------------------------
        case REA_AGACHADO:
            break;
        case REA_GOLPE_ALTO:
            break;
        case REA_GOLPE_BAJO:
            break;
        case REA_GOLPE_FUERTE:
            break;
        case REA_PATADA_BARRIDA:
            break;
        case REA_PINIA_ALTA:
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
void Accionador::subirEnSaltoOblicuo(float deltaMovX,float deltaMovY,Tsentido sentido, Tdireccion direccion){
    if(direcBloqueada == DERECHA){
        if (sentido == ADELANTE) rectaDelPj.p =rectaDelPj.p+Posicion(deltaMovX,-deltaMovY);
        else rectaDelPj.p =rectaDelPj.p+Posicion(-deltaMovX,-deltaMovY);
    }else{
        if (sentido == ADELANTE) rectaDelPj.p =rectaDelPj.p+Posicion(-deltaMovX,-deltaMovY);
        else rectaDelPj.p =rectaDelPj.p+Posicion(deltaMovX,-deltaMovY);
    }
}
void Accionador::bajarEnSaltoOblicuo(float deltaMovX,float deltaMovY,Tsentido sentido, Tdireccion direccion) {
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
            if(loops <= (loopsPara(MOV_SALTANDO_OBLICUO)/4)) subirEnSaltoOblicuo(intervaloSaltoOblicuo,intervaloSaltoOblicuo*3,sentido,direccion);
            else subirEnSaltoOblicuo(intervaloSaltoOblicuo,intervaloSaltoOblicuo,sentido,direccion);
        }else{
            //en la segunda mitad de los loops baja
            //en el primer cuarto de estos baja mas lentamente que en el segundo cuarto
            if(loops <= (proporcionSalto*loopsPara(MOV_SALTANDO_OBLICUO)/4)) bajarEnSaltoOblicuo(intervaloSaltoOblicuo,intervaloSaltoOblicuo,sentido,direccion);
            else bajarEnSaltoOblicuo(intervaloSaltoOblicuo,intervaloSaltoOblicuo*proporcionSalto,sentido,direccion);
        }
    }
}
//--------------------------------------------------------------------------------------
//                  AGACHAR
void Accionador::agachar() {
    rectaDelPj.d.h = rectaDelPj.d.h/2;
    rectaDelPj.p = rectaDelPj.p + Posicion(0,rectaDelPj.d.h);
}
//--------------------------------------------------------------------------------------
//                  GOLPES
//--------------------------------------------------------------------------------------
//                  PINIA BAJA
//TODO:: FALTA AJUSTAR, EL ALTO DEL CUADRADO Y LA POSICION Y LAS REACCIONES
void Accionador::piniaBaja(int loops) {

    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * proporcionPiniaBaja;
    if(loopsPara(ACC_PINIA_BAJA)<loops){
        golpe.setGolpe(piniasBajas, loops == 2,rectan,REA_GOLPE_BAJO);
    }
}
//--------------------------------------------------------------------------------------
//                  PINIA BAJA AGACHADO
void Accionador::piniaBajaAgachado(int loops) {
    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * proporcionPiniaBaja;
    if(loopsPara(ACC_PINIA_BAJA_AGACHADO)<loops){
        golpe.setGolpe(piniasBajas, loops == 2,rectan,REA_GOLPE_BAJO);
    }
}
//--------------------------------------------------------------------------------------
//                  PINIA ALTA
void Accionador::piniaAlta(int loops) {
    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * proporcionPiniaAlta;
    if(loopsPara(ACC_PINIA_ALTA)<loops){
        golpe.setGolpe(piniasAltas, loops == 2,rectan,REA_GOLPE_BAJO);
    }
}
//--------------------------------------------------------------------------------------
//                  PINIA ALTA AGACHADO
void Accionador::piniaAltaAgachado(int loops) {
    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * proporcionPiniaAltaAgachado;
    if(loopsPara(ACC_PINIA_ALTA_AGACHADO)<loops){
        golpe.setGolpe(poderFuerte, loops == 2,rectan,REA_GOLPE_BAJO);
    }
}
//--------------------------------------------------------------------------------------
//                  PINIA SALTO
void Accionador::piniaSalto(int loops) {
    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * proporcionPiniaSalto;
    if(loopsPara(ACC_PINIA_SALTO)<loops){
        golpe.setGolpe(piniasAltas, loops == 2,rectan,REA_GOLPE_BAJO);
    }
}
//--------------------------------------------------------------------------------------
//                  PATADA BAJA
void Accionador::patadaBaja(int loops) {
    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * proporcionPatadaBaja;
    if(loopsPara(ACC_PATADA_BAJA)<loops){
        golpe.setGolpe(patadasBajas, loops == 2,rectan,REA_GOLPE_BAJO);
    }

}
//--------------------------------------------------------------------------------------
//                  PATADA BAJA ATRAS
void Accionador::patadaBajaAtras(int loops) {
    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * proporcionPatadaAlta;
    if(loopsPara(ACC_PATADA_BAJA_ATRAS)<loops){
        golpe.setGolpe(patadasBajas, loops == 2,rectan,REA_GOLPE_BAJO);
    }

}
//--------------------------------------------------------------------------------------
//                  PATADA ALTA ATRAS
void Accionador::patadaAltaAtras(int loops) {
    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * porporcionPatadaAltaAtras;
    if(loopsPara(ACC_PATADA_ALTA_ATRAS)<loops){
        golpe.setGolpe(poderFuerte, loops == 2,rectan,REA_GOLPE_BAJO);
    }

}
//--------------------------------------------------------------------------------------
//                  PATADA ALTA
void Accionador::patadaAlta(int loops) {
    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * proporcionPatadaAlta;
    if(loopsPara(ACC_PATADA_ALTA)<loops){
        golpe.setGolpe(patadasAltas, loops == 2,rectan,REA_GOLPE_BAJO);
    }

}
//--------------------------------------------------------------------------------------
//                  PATADA SALTO
void Accionador::patadaSalto(int loops) {
    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * proporcionPatadaSO;
    if(loopsPara(ACC_PATADA_SALTO)<loops){
        golpe.setGolpe(patadasAltas, loops == 2,rectan,REA_GOLPE_BAJO);
    }

}
//--------------------------------------------------------------------------------------
//                  PATADA SALTO VERTICAL
void Accionador::patadaSaltoVertical(int loops) {
    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * proporcionPatadaSV;
    if(loopsPara(ACC_PATADA_SALTO_VERTICAL)<loops){
        golpe.setGolpe(patadasAltas, loops == 2,rectan,REA_GOLPE_BAJO);
    }
}
//--------------------------------------------------------------------------------------
//                  PATADA AGACHADO
void Accionador::patadaAgachado(int loops) {
    Trect rectan = Trect();
    rectan.p = rectaDelPj.p;

    rectan.d.w = rectaDelPj.d.w * proporcionPatadaAgachado;
    if(loopsPara(ACC_PATADA_AGACHADO)<loops){
        golpe.setGolpe(patadasBajas, loops == 2,rectan,REA_GOLPE_BAJO);
    }

}
