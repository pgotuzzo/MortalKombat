#ifndef MORTALKOMBAT_VISTAUTILS_H
#define MORTALKOMBAT_VISTAUTILS_H

#include <SDL2/SDL_render.h>
#include <string>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "../Common.h"

struct Ttexture{
    SDL_Texture* t;
    Tdimension d;
};

class VistaUtils {
private:
    float mRatio;
    float mScales[2]; // relacion = (pixel / unidad logica)
    bool mColorChangeEnable;
    TcolorSettings mColorSettings;
    SDL_Renderer* mRenderer;
    vector<SDL_Texture*> mAuxTextures;

    SDL_Texture* createTexture(Tdimension pixelDimension);
    Uint32 getPixel(SDL_Surface* surface, int i);
    void putPixel(SDL_Surface* surface, int i, Uint32 pixel);
    void changeColor(SDL_Surface* surface);
    Tdimension getDimension(SDL_Texture* texture);

public:
    VistaUtils(SDL_Renderer* renderer, float ratio, float scales[2]);

    void enableColorChange(bool enable);
    void setColorSetting(TcolorSettings settings);
    void getScales(Ttexture texture, float scales[2]);

    Ttexture loadTexture(std::string path);
    Ttexture createTextureFromText(string fontPath, string string, int size);

    void copyTexture(SDL_Texture* src, SDL_Texture* dst);
    void copyTexture(SDL_Texture* src, SDL_Texture* dst, bool flip);

    void copyTexture(Ttexture src, Ttexture dst, Trect* srcRect, Trect* dstRect);
    void copyTexture(Ttexture src, Ttexture dst, Trect* srcRect, Trect* dstRect, bool flip);

    Tdimension getDimension(SDL_Texture* texture, float scales[2]);

    void freeTextures();
};

#endif //MORTALKOMBAT_VISTAUTILS_H
