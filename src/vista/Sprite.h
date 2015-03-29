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

public:
    Sprite(){};
    Sprite(SDL_Renderer* renderer, std::string dirPath);
    int getCount();
    void getFirst(SDL_Texture* texture);
    int getNext(SDL_Texture* texture);
};


#endif //_MORTALKOMBAT_SPRITE_H_
