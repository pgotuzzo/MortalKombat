
#include "Combo.h"


Combo::Combo(TComboData datosDelCombo) {
    this->datosDelCombo = datosDelCombo;
    this->inicializarCombo();
    teclasAString();
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
}


bool Combo::puedoRealizarCombo() {
    if(ocurrencias == datosDelCombo.teclas.size()){
        inicializarCombo();
        return true;
    }
    return false;
}


void Combo::teclasAString() {
    cadenaParaBuffer = datosDelCombo.nombre + " ";

    for(int i=0; i<datosDelCombo.teclas.size();i++){

        Tinput input = datosDelCombo.teclas[i];
        switch(input.movimiento){

            case TinputMovimiento::KEY_ARRIBA:
                cadenaParaBuffer += "UP ";
                break;
            case TinputMovimiento::KEY_ABAJO:
                cadenaParaBuffer += "DW ";
                break;
            case TinputMovimiento::KEY_DERECHA:
                cadenaParaBuffer += "RG ";
                break;
            case TinputMovimiento::KEY_IZQUIERDA:
                cadenaParaBuffer += "LF ";
                break;
            default:
                switch(input.accion){

                    case TinputAccion::KEY_PINIA_ALTA:
                        cadenaParaBuffer += "PH ";
                        break;
                    case TinputAccion::KEY_PINIA_BAJA:
                        cadenaParaBuffer += "PL ";
                        break;
                    case TinputAccion::KEY_PATADA_ALTA:
                        cadenaParaBuffer += "KH ";
                        break;
                    case TinputAccion::KEY_PATADA_BAJA:
                        cadenaParaBuffer += "KL ";
                        break;
                    case TinputAccion::KEY_PROTECCION:
                        cadenaParaBuffer += "BK ";
                        break;
                }
        }

    }
}
