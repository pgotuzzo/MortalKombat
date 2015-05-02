#include "ErrorLog.h"
#include <fstream>

ErrorLog::ErrorLog() {
	archivo = "./logs/error_log.txt";
	fecha = nullptr;
	FILE* fp=fopen(archivo.c_str(),"r");
	if(fp){
		fclose(fp);
		remove(archivo.c_str());
	}
}

ErrorLog* ErrorLog::instance = nullptr;

ErrorLog* ErrorLog::getInstance() {
    if (instance == nullptr) {
        instance = new ErrorLog();
    }
    return instance;
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

void ErrorLog::borrar(){
	FILE* fp=fopen(archivo.c_str(),"r");
		if(fp){
			fclose(fp);
			remove(archivo.c_str());
		}
}


