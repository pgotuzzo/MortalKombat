#ifndef JASON_WARNINGLOG_H
#define JASON_WARNINGLOG_H


#include "Log.h"

class WarningLog: public Log {
private:
    const char* fecha;
    static WarningLog* instance;
    WarningLog();
public:

    static WarningLog* getInstance();
    void loguear(const char*, Log::Tlog) ;
    virtual ~WarningLog();
};


#endif //JASON_WARNINGLOG_H
