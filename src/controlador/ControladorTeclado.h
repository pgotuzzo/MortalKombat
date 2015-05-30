#ifndef MORTALKOMBAT_CONTROLADORTECLADO_H
#define MORTALKOMBAT_CONTROLADORTECLADO_H

#include <vector>
#include "../Common.h"

using namespace std;

class ControladorTeclado {
private:
    Tinput esAnterior1(const unsigned char *state);
    Tinput esAnterior2(const unsigned char *state);
public:
    Tinput inputAnterior1;
    Tinput inputAnterior2;
    ControladorTeclado();
    vector<Tinput> getInputs();
};


#endif //MORTALKOMBAT_CONTROLADORTECLADO_H