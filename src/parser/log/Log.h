#ifndef JASON_LOG_H
#define JASON_LOG_H
#include <string>
using namespace std;

class Log {
protected:
	string archivo;
public:
	enum Tlog {LOG_ERR, LOG_WAR, LOG_DEB};

	virtual  void loguear(const char* mensaje, Tlog tipo){};
	virtual ~Log(){} ;
};
#endif //JASON_LOG_H
