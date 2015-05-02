#ifndef _MORTALKOMBAT_SPRITE_H_
#define _MORTALKOMBAT_SPRITE_H_

#include <string>
#include <SDL2/SDL_render.h>
#include <vector>
#include "../VistaUtils.h"

class Sprite {
private:
    VistaUtils* mUtils;
    std::vector<SDL_Texture *> mTextures;
    int mCurrent;
    bool mRepeat;
    bool mFirstPass;

public:
    Sprite(){};
    Sprite(VistaUtils* utils, std::string dirPath, bool repeat);
    Tdimension getDimension();
    long getCount();
    void restart();
    void getNext(SDL_Texture* texture, bool flip);
    void getBefore(SDL_Texture* texture, bool flip);

    void freeTextures();
};


#endif //_MORTALKOMBAT_SPRITE_H_
