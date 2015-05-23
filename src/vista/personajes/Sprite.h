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
    vector<int> mDisabled;
    vector<int> mToDisable;
    int mCurrent;
    bool mRepeat;
    bool mFirstPass;

public:
    Sprite(){};
    Sprite(VistaUtils* utils, string dirPath, bool repeat);
    void initialize(VistaUtils* utils, string dirPath, bool repeat);
    long getCount();
    void restart();
    SDL_Texture* getNext();
    SDL_Texture* getBefore();
    void disable(int index);

    void freeTextures();
};


#endif //_MORTALKOMBAT_SPRITE_H_
