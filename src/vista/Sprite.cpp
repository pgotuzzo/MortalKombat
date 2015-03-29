#include <SDL2/SDL_image.h>
#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* renderer, std::string dirPath) {
    mCurrent = 0;
    mRenderer = renderer;
    mTextures = std::vector<SDL_Texture *>();

    bool end = false;
    do{
        std::string filePath = dirPath + std::to_string(getCount());
        SDL_Surface* surface = IMG_Load(filePath.c_str());
        if (surface == NULL){
            end = true;
        }else {
            mTextures.at(getCount()) = SDL_CreateTextureFromSurface(mRenderer, surface);
        }
    }while(!end);
}

int Sprite::getCount() {
    return mTextures.size();
}

void Sprite::getFirst(SDL_Texture* texture) {
    SDL_Texture* originalTarget = SDL_GetRenderTarget(mRenderer);
    SDL_SetRenderTarget(mRenderer, texture);
    SDL_RenderCopy(mRenderer, mTextures[0], NULL, NULL);
    SDL_SetRenderTarget(mRenderer, originalTarget);
}

/**
* return    0 si hay un elemento siguiente
*           -1 si no hay un elemento siguiente
*/
int Sprite::getNext(SDL_Texture* texture) {
    mCurrent++;
    if (mCurrent < getCount()) {
        SDL_Texture *originalTarget = SDL_GetRenderTarget(mRenderer);
        SDL_SetRenderTarget(mRenderer, texture);
        SDL_RenderCopy(mRenderer, mTextures[mCurrent], NULL, NULL);
        SDL_SetRenderTarget(mRenderer, originalTarget);
        return 0;
    }else{
        return -1;
    }
}

