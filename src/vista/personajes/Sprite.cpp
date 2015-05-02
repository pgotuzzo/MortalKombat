#include <SDL2/SDL_image.h>
#include "Sprite.h"
#include "../VistaUtils.h"

Sprite::Sprite(VistaUtils* utils, std::string dirPath, bool repeat) {
    mCurrent = 0;
    mRepeat = repeat;
    mFirstPass = true;
    mUtils = utils;
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
        SDL_Texture* t = mUtils->loadTexture(filePath, VistaUtils::BLANCO);
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

void Sprite::restart() {
    mCurrent = 0;
    mFirstPass = true;
}

void Sprite::getNext(SDL_Texture* texture, bool flip) {
    mUtils->copyTexture(mTextures[mCurrent], texture, flip);
    if (mCurrent < getCount() - 1) {
        mCurrent++;
    } else if (mRepeat){
        mCurrent = 0;
    }
}

void Sprite::getBefore(SDL_Texture *texture, bool flip) {
    mUtils->copyTexture(mTextures[mCurrent], texture, flip);
    if (mCurrent == 0){
        mCurrent = (int) getCount() - 1;
    } else if ( ( mCurrent > 0 ) && ( mCurrent < getCount() - 1 ) ){
        mCurrent--;
    } else if (mFirstPass){
        mCurrent--;
        mFirstPass = mRepeat;
    }
}

void Sprite::freeTextures() {
    loguer->loguear("Comienza a eliminarse un vector de Sprites", Log::LOG_DEB);
    for(int i = 0; i < mTextures.size(); i++) {
        string message = "Elimina textura " + to_string(i + 1);
        loguer->loguear(message.c_str(), Log::LOG_DEB);
        SDL_DestroyTexture(mTextures[i]);
    }
    loguer->loguear("Finaliza la eliminacion del vector de Sprites", Log::LOG_DEB);
}

Tdimension Sprite::getDimension() {
    int w, h;
    SDL_QueryTexture(mTextures[0], NULL, NULL, &w, &h);
    return {w,h};
}
