
#include "Combo.h"


Combo::Combo(TComboData datosDelCombo) {
    this->datosDelCombo = datosDelCombo;
    this->inicializarCombo();
}

void Combo::inicializarCombo() {
    ocurrencias = 0;
    errores = 0;
    tiempoInicial = 0;
    tiempoFinal = 0;
}

bool Combo::teclaPresionada(Tinput input) {
    return (input.accion != TinputAccion::KEY_NADA || input.movimiento != TinputMovimiento::KEY_NADA);
}

void Combo::actualizar(Tinput input) {

//    cout<<errores<<endl;
    // El tiempo se comienza a contar luego de la primer tecla correcta
    if(ocurrencias > 0) tiempoFinal = input.tiempo;

    // Se paso el tiempo maximo
    if(SDL_TICKS_PASSED(tiempoFinal-tiempoInicial,datosDelCombo.tiempoMaximo)){
        //cout<<tiempoFinal-tiempoInicial<<endl;
        inicializarCombo();
    }
    // Se pasaron los errores
    if(errores >= datosDelCombo.tolerancia){
        inicializarCombo();
    }

    // Cuando la tecla presionada coincide con la tecla del combo
    if(datosDelCombo.teclas[ocurrencias] == input){
        if(ocurrencias == 0){
            tiempoInicial = input.tiempo;
            tiempoFinal = input.tiempo;
        }
        ocurrencias++;
    }

    // Cuando la tecla presionada no coincide con la tecla del combo
    if((!(datosDelCombo.teclas[ocurrencias] == input) && teclaPresionada(input))){
        errores++;
    }




    /*if(SDL_TICKS_PASSED(tiempoFinal-tiempoInicial,datosDelCombo.tiempoMaximo) || errores == datosDelCombo.tolerancia){
        ocurrencias = 0;
        errores = 0;
        cout<<tiempoFinal-tiempoInicial<<endl;
        activado = false;
        tiempoInicial = 0;
        tiempoFinal = 0;
    }
    else if(ocurrencias == datosDelCombo.teclas.size()){
        ocurrencias = 0;
        errores = 0;
        activado = true;
        tiempoInicial = 0;
        tiempoFinal = 0;
    }
    else{
        tiempoFinal = input.tiempo;
        if(ocurrencias == 0)tiempoInicial = input.tiempo;
        if(datosDelCombo.teclas[ocurrencias] == input){
            ocurrencias++;
        }
        else errores++;
    }*/
}


bool Combo::puedoRealizarCombo() {
    if(ocurrencias == datosDelCombo.teclas.size()){
        inicializarCombo();
        return true;
    }
    return false;
}



