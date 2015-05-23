#ifndef MORTALKOMBAT_VISTAUTILS_H
#define MORTALKOMBAT_VISTAUTILS_H

#include <SDL2/SDL_render.h>
#include <string>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "../Common.h"

class VistaUtils {
private:
    float mRatio;
    float mScales[2]; // relacion = (pixel / unidad logica)
    TcolorSettings mColorSettings = TcolorSettings(0, 0, 0);
    SDL_Renderer* mRenderer;
    vector<SDL_Texture*> mAuxTextures;


    void changeColor(SDL_Surface* surface);
    Uint32 getPixel(SDL_Surface* surface, int i);
    void putPixel(SDL_Surface* surface, int i, Uint32 pixel);

public:
    VistaUtils(SDL_Renderer* renderer, float ratio, float scales[2]);

    void setColorSetting(TcolorSettings settings);
    SDL_Texture* createTexture(Tdimension dimension);
    SDL_Texture* loadTexture(std::string path);
    void copyTexture(SDL_Texture* src, SDL_Texture* dst);
    void copyTexture(SDL_Texture* src, SDL_Texture* dst, bool flip);
    void copyTexture(SDL_Texture* src, SDL_Texture* dst, Trect* srcRect, Trect* dstRect, Tdimension* srcDim, Tdimension* dstDim);
    void copyTexture(SDL_Texture* src, SDL_Texture* dst, Trect* srcRect, Trect* dstRect, Tdimension* srcDim, Tdimension* dstDim, bool flip);
    Tdimension getDimension(SDL_Texture *texture);
    Tdimension getDimension(SDL_Texture* tIndex, Tdimension* dIndex, SDL_Texture *texture);
    void getScales(SDL_Texture* texture, Tdimension* dimension, float scales[2]);
    Tdimension getDimension(SDL_Texture* texture, float scales[2]);
    void cleanTexture(SDL_Texture* t);
    SDL_Texture* createTexture(string fontPath, string string, int size);

    virtual ~VistaUtils();
};

#endif //MORTALKOMBAT_VISTAUTILS_H
