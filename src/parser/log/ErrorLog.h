#ifndef JASON_ERRORLOG_H
#define JASON_ERRORLOG_H

#include "Log.h"

class ErrorLog: public Log {
private:
    const char* fecha;
    static ErrorLog* instance;
    ErrorLog();
public:
    static ErrorLog* getInstance();
    void loguear(const char*, Log::Tlog);
    virtual ~ErrorLog();
    void borrar();
};

#endif //JASON_ERRORLOG_H
