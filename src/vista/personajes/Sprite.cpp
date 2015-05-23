#include <SDL2/SDL_image.h>
#include <algorithm>
#include "Sprite.h"

Sprite::Sprite(VistaUtils* utils, string dirPath, bool repeat) {
    initialize(utils, dirPath, repeat);
}

void Sprite::initialize(VistaUtils *utils, string dirPath, bool repeat) {
    mCurrent = 0;
    mRepeat = repeat;
    mFirstPass = true;
    mUtils = utils;
    mTextures = vector<SDL_Texture *>();
    mDisabled = vector<int>();

    bool end = false;
    do{
        string filePath;
        string number; // number = XX ---> dos dígitos!!!

        if(getCount() < 9){
            number = "0" + to_string(getCount() + 1);
        }else{
            number = to_string(getCount() + 1);
        }
        filePath = dirPath + number + SPRITES_FORMAT;
        SDL_Texture* t = mUtils->loadTexture(filePath);
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
    mDisabled.clear();
}

SDL_Texture* Sprite::getNext() {
    bool show = true;
    SDL_Texture *t = mTextures[mCurrent];

    for (int i = 0; i < mDisabled.size(); i++) {
        if (mDisabled[i] == mCurrent) {
            show = false;
        }
    }
    for(int i = 0; i < mToDisable.size(); i++){
        if(mToDisable[i] == mCurrent)
            mDisabled.push_back(mCurrent);
    }

    if (mCurrent < getCount() - 1) {
        mCurrent++;
    } else if (mRepeat) {
        mCurrent = 0;
    }

    return (show) ? t : getNext();
}

SDL_Texture* Sprite::getBefore() {
    bool show = true;
    SDL_Texture* t = mTextures[mCurrent];

    for (int i = 0; i < mDisabled.size(); i++) {
        if (mDisabled[i] == mCurrent) {
            show = false;
        }
    }
    for(int i = 0; i < mToDisable.size(); i++){
        if(mToDisable[i] == mCurrent)
            mDisabled.push_back(mCurrent);
    }

    if (mCurrent == 0){
        mCurrent = (int) getCount() - 1;
    } else if ( ( mCurrent > 0 ) && ( mCurrent < getCount() - 1 ) ){
        mCurrent--;
    } else if (mFirstPass){
        mCurrent--;
        mFirstPass = mRepeat;
    }

    return (show) ? t : getBefore();
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

void Sprite::disable(int index) {
    mToDisable.push_back(index);
}