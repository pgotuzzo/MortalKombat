#ifndef _MORTALKOMBAT_SPRITE_H_
#define _MORTALKOMBAT_SPRITE_H_

#include <string>
#include <vector>
#include "../VistaUtils.h"

using namespace std;

class Sprite {
private:
    VistaUtils* mUtils;
    vector<Ttexture> mTextures;
    vector<int> mDisabled;
    vector<int> mToDisable;
    int mCurrent;
    bool mRepeat;
    bool mFirstPass;

public:
    Sprite(){};
    Sprite(VistaUtils* utils, string dirPath, float scales[2], bool repeat);
    void initialize(VistaUtils* utils, string dirPath, float scales[2], bool repeat);

    long getCount();
    void restart();
    Ttexture getNext();
    Ttexture getBefore();
    void disable(int index);

    void freeTextures();
};


#endif //_MORTALKOMBAT_SPRITE_H_
