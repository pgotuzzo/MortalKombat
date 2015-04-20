#include "WarningLog.h"
#include <fstream>
#include <iostream>

WarningLog::WarningLog() {
    //TODO - Cambiar rutas relativas
	archivo = "/home/MortalKombat/logs/warning_log.txt";
	fecha = nullptr;
	FILE* fp=fopen(archivo.c_str(),"r");
	if(fp){
		fclose(fp);
		remove(archivo.c_str());
	}
}

WarningLog* WarningLog::instance = nullptr;

WarningLog* WarningLog::getInstance() {
    if (instance == nullptr) {
        instance = new WarningLog();
    }
    return instance;
}

void WarningLog::loguear(const char* mensajeError, Log::Tlog tipo) {
    const char * tipoDeLog;
    time_t t;
    struct tm * timestamp;

    time(&t);
    timestamp = localtime(&t);
    string fechaAux = asctime(timestamp);

    fecha = fechaAux.c_str();

    switch (tipo) {
        case (LOG_ERR):
            tipoDeLog = " Error - ";
            break;
        case (LOG_WAR):
            tipoDeLog = " Warning - ";
            break;
        default:
            return;
    }
    ofstream salida(archivo, std::ios::out | std::ios::app);
    if(salida.is_open()){
        std::cout<<"okkkk";
    }
    salida<<fecha << tipoDeLog << mensajeError << "\n";
    salida.close();
}

WarningLog::~WarningLog() {}


