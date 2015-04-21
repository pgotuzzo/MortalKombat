#ifndef JASON_DEBUGLOG_H_
#define JASON_DEBUGLOG_H_

#include "Log.h"

class DebugLog: public Log {
private:
    const char * fecha;
    static DebugLog* instance;
    DebugLog();
public:
    static DebugLog* getInstance();
    void loguear(const char*, Log::Tlog);
    virtual ~DebugLog();
    void borrar();
};

#endif //JASON_DEBUGLOG_H_
