#ifndef _MORTALKOMBAT_SPRITE_H_
#define _MORTALKOMBAT_SPRITE_H_

#include <string>
#include <SDL2/SDL_render.h>
#include <vector>
#include "../VistaUtils.h"

using namespace std;

class Sprite {
private:
    VistaUtils* mUtils;
    vector<SDL_Texture *> mTextures;
    int mCurrent;
    bool mRepeat;
    bool mFirstPass;

public:
    Sprite(){};
    Sprite(VistaUtils* utils, string dirPath, bool repeat);
    Tdimension getDimension();
    long getCount();
    void restart();
    void getNext(SDL_Texture* texture, bool flip);
    void getBefore(SDL_Texture* texture, bool flip);

    void freeTextures();
};


#endif //_MORTALKOMBAT_SPRITE_H_
