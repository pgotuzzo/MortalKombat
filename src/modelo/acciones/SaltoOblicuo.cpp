/*
 * SaltoOblicuo.cpp
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#include "../../modelo/acciones/SaltoOblicuo.h"

SaltoOblicuo::SaltoOblicuo() {

}


void SaltoOblicuo::setEstado(bool nuevoEstado, bool nuevaOrientacion) {
    estado = nuevoEstado;
    orientacion = nuevaOrientacion;
}

bool SaltoOblicuo::getEstado() {
    return estado;
}

SaltoOblicuo::~SaltoOblicuo() {
}

