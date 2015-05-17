#ifndef MORTALKOMBAT_OBJETOCOLISIONABLE_H
#define MORTALKOMBAT_OBJETOCOLISIONABLE_H


#include <vector>
#include "../Common.h"

class ObjetoColisionable {

public:

    virtual Trect getRectangulo() = 0;

    virtual ~ObjetoColisionable() {}

};


#endif //MORTALKOMBAT_OBJETOCOLISIONABLE_H


