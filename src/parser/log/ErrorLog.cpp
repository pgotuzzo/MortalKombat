#include "ErrorLog.h"
#include <fstream>

ErrorLog::ErrorLog() {
    //TODO Cambiar rutas relativas
    archivo = "/home/MortalKombat/logs/error_log.txt";
    fecha = nullptr;
}

 void ErrorLog::loguear(const char* mensajeError, Log::Tlog tipo) {
    if (tipo == LOG_ERR) {
        time_t t;
        struct tm * timestamp;

        time(&t);
        timestamp = localtime(&t);
        std::string fechaAux = asctime(timestamp);

        fecha = fechaAux.c_str();

        std::ofstream salida(archivo, std::ios::out | std::ios::app);

        salida <<fecha<< "Error- " << mensajeError << "\n";
        salida.close();
    }
}

ErrorLog::~ErrorLog() {}


