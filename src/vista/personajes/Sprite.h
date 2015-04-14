#ifndef _MORTALKOMBAT_SPRITE_H_
#define _MORTALKOMBAT_SPRITE_H_

#include <string>
#include <SDL2/SDL_render.h>
#include <vector>

class Sprite {
private:
    SDL_Renderer* mRenderer;
    std::vector<SDL_Texture *> mTextures;
    int mCurrent;
    bool mRepeat;
    bool mFirstPass;

public:
    Sprite(){};
    Sprite(SDL_Renderer* renderer, std::string dirPath, bool repeat);
    long getCount();
    void getFirst(SDL_Texture* texture, bool flip);
    void getNext(SDL_Texture* texture, bool flip);
    void getBefore(SDL_Texture* texture, bool flip);

    void freeTextures();
    virtual ~Sprite();
};


#endif //_MORTALKOMBAT_SPRITE_H_
