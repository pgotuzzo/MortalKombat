#ifndef JASON_DEBUGLOG_H_
#define JASON_DEBUGLOG_H_

#include "Log.h"

class DebugLog: public Log {
private:
    const char * fecha;
public:
    DebugLog();
    void loguear(const char*, Log::Tlog);
    virtual ~DebugLog();
};

#endif //JASON_DEBUGLOG_H_
