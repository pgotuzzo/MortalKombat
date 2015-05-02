#ifndef MORTALKOMBAT_VISTAUTILS_H
#define MORTALKOMBAT_VISTAUTILS_H

#include <SDL2/SDL_render.h>
#include <string>
#include <vector>
#include "../Common.h"

class VistaUtils {
public:
    enum COLORKEY{
        BLANCO,
        NEGRO
    };

private:
    float mRatio;
    float mScales[2]; // relacion = (pixel / unidad logica)
    SDL_Renderer* mRenderer;
    vector<SDL_Texture*> mAuxTextures;

    Uint32 getColorKeyValue(COLORKEY color, SDL_Surface* s);
    void getScales(SDL_Texture* texture, Tdimension* dimension, float scales[2]);

public:
    VistaUtils(SDL_Renderer* renderer, float ratio, float scales[2]);

    SDL_Texture* createTexture(Tdimension dimension);
    SDL_Texture* loadTexture(std::string path, COLORKEY);
    void copyTexture(SDL_Texture* src, SDL_Texture* dst);
    void copyTexture(SDL_Texture* src, SDL_Texture* dst, bool flip);
    void copyTexture(SDL_Texture* src, SDL_Texture* dst, Trect* srcRect, Trect* dstRect, Tdimension* srcDim, Tdimension* dstDim);
    void cleanTexture(SDL_Texture* t);

    virtual ~VistaUtils();
};

#endif //MORTALKOMBAT_VISTAUTILS_H
