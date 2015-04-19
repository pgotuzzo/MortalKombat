#ifndef JASON_ERRORLOG_H
#define JASON_ERRORLOG_H

#include "Log.h"

class ErrorLog: public Log {
private:
    const char* fecha;
public:
    ErrorLog();
    void loguear(const char*, Log::Tlog);
    virtual ~ErrorLog();
};

#endif //JASON_ERRORLOG_H
