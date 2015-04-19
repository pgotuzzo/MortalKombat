#include "DebugLog.h"
#include <fstream>

DebugLog::DebugLog() {
	// TODO - Cambiar a ruta relativa
	archivo = "/home/MortalKombat/logs/debug_log.txt";
	fecha = nullptr;
}

void DebugLog::loguear(const char* mensajeError, Log::Tlog tipo)  {
	const char * tipoDeLog;
	time_t t;
	struct tm * timestamp;

	time(&t);
	timestamp = localtime(&t);
	std::string fechaAux = asctime(timestamp);

	fecha = fechaAux.c_str();

	switch (tipo) {
	case (LOG_ERR):
		tipoDeLog = " -Error- ";
		break;
	case (LOG_DEB):
		tipoDeLog = " -Debug- ";
		break;
	case (LOG_WAR):
		tipoDeLog = " -Warning- ";
		break;
	default:
		;
	}
	ofstream salida(archivo, std::ios::out | std::ios::app);
	salida << fecha << tipoDeLog << mensajeError << "\n";
	salida.close();
}

DebugLog::~DebugLog() {}

