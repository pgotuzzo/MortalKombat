#ifndef JASON_WARNINGLOG_H
#define JASON_WARNINGLOG_H


#include "Log.h"

class WarningLog: public Log {
private:
    const char* fecha;

public:
    WarningLog();
    void loguear(const char*, Log::Tlog) ;
    virtual ~WarningLog();
};


#endif //JASON_WARNINGLOG_H
