#include <SDL2/SDL_image.h>
#include "Sprite.h"
#include "../../Constants.h"
#include "../VistaUtils.h"

Sprite::Sprite(SDL_Renderer* renderer, std::string dirPath, bool repeat) {
    mCurrent = 0;
    mRepeat = repeat;
    mRenderer = renderer;
    mTextures = std::vector<SDL_Texture *>();

    bool end = false;
    do{
        std::string filePath;
        std::string number; // number = XX ---> dos dígitos!!!

        if(getCount() < 9){
            number = "0" + std::to_string(getCount() + 1);
        }else{
            number = std::to_string(getCount() + 1);
        }
        filePath = dirPath + number + SPRITES_FORMAT;
        SDL_Texture* t = VistaUtils::loadTexture(mRenderer, filePath, VistaUtils::BLANCO);
        if (t == nullptr){
            end = true;
        }else {
            mTextures.push_back(t);
        }

    }while(!end);
}

long Sprite::getCount() {
    return mTextures.size();
}

void Sprite::getFirst(SDL_Texture* texture) {
    VistaUtils::copyTexture(mRenderer, mTextures[0], texture);
}

/**
* return    0 si hay un elemento siguiente
*           -1 si no hay un elemento siguiente
*/
int Sprite::getNext(SDL_Texture* texture) {
    if ((mCurrent == getCount() - 1) && (mRepeat)){
        mCurrent = 0;
    }else if(mCurrent < getCount() - 1){
        mCurrent++;
    }
    if (mCurrent < getCount()) {
        VistaUtils::copyTexture(mRenderer, mTextures[mCurrent], texture);
        return 0;
    }else{
        return -1;
    }
}

